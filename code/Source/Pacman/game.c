/***************************************Copyright ©******************************************************************
 * 
 * Copyright © 2025 Gabriele Arcidiacono
 *
 * This work is licensed under the Creative Commons
 * Attribution–NonCommercial 4.0 International License.
 * 
 * You may not use this file for commercial purposes.
 * You must give appropriate credit and indicate if changes were made.
 * 
 * License details: https://creativecommons.org/licenses/by-nc/4.0/
 * 
*********************************************************************************************************************/

#include "LPC17xx.h"
#include "game.h"
#include "pacman.h"
#include "mapping.h"
#include "labyrinth.h"
#include "pills.h"
#include "ghost.h"
#include "GLCD/GLCD.h" 
#include "CAN/CAN.h"
#include "music/music.h"
#include <stdio.h>
#include <stdlib.h>



CHR_TypeDef PCMN_Instance;
CHR_TypeDef *PCMN = &PCMN_Instance;

CHR_TypeDef GHOST_Instance;
CHR_TypeDef *GHOST = &GHOST_Instance;

NOTE *currSound;

uint16_t score;
uint8_t num_lives;
uint8_t game_time;
uint8_t respawn_time;
uint8_t frightened_time;
Difficulty difficulty;
int rnd_time_pwr_pills[POWER_PILLS];
uint8_t n_rnd_pills;
volatile Bool victory;
volatile Bool hit;
volatile Bool ended;
volatile Bool pause_game;
volatile Bool event;
volatile Bool game_over;
volatile Bool go;
volatile Bool computePath;
volatile Bool modified_time;
volatile Bool modified_score;
volatile Bool modified_lives;
volatile Bool playSound;
volatile Bool openingSong;
volatile Bool powerPillSound;
volatile Bool winSong;

extern Object_TypeDef labyrinth_mat[ROWS][COLS];
extern int tot_pills;
extern uint8_t n_interrupt_pcmn;
extern uint8_t n_interrupt_pill;
extern Direction_TypeDef path[MAX_PATH_LENGTH];
extern int currPathIndex;
extern CAN_msg CAN_TxMsg;


void pacman(){
	
	init_RIT(0x002625A0);					/* RIT Initialization 25 msec: used for joystick sampling and button debouncing*/
	//init_RIT(0x107EF);						/* 1 ms (for SW emulator) */
	//init_RIT(0x004C4B40);						/* 50 ms */	
	//init_RIT(0x0007A120);   /* 5 ms */
	//init_RIT(0x1E8480);   /* RIT initialization 20 msec */
	
	
	init_timer(0,0,0x17D7840);			/* 1s * 25 MHz = 25 * 10^6 : used for coutdown timer*/
	//init_timer(1,0,0x98968);		/* 25 ms * 25 MHz = 625.000: used for ghost movement */
	//init_timer(1,0,0x1312D0);		/* 50 ms */
	
	init_timer(1,0,0x5B8D8);  /* 15 ms : used to control ghost */ 
	
	LCD_Clear(Black);
	
	reset_timer(0);
	reset_timer(1);
	
	/* initialize game parameters */ 
	
	game_time = GAME_TIME;
	respawn_time = RESPAWN_TIME;
	score = 0;
	num_lives = 1;
	tot_pills = NUM_PILLS;
	difficulty.chase = 1;
	difficulty.frightened = 1;
	n_rnd_pills = POWER_PILLS;
	pause_game = TRUE;
	victory = FALSE;
	ended = FALSE;
	event = TRUE;
	game_over = FALSE;
	hit = FALSE;
	go = FALSE;
	computePath=TRUE;
	playSound = FALSE;
	openingSong = FALSE;
	powerPillSound = FALSE;
	modified_lives = TRUE;
	modified_time = TRUE;
	modified_score = TRUE;
	winSong = FALSE;
	
	
	/* initialize PACMAN */
	
	initialize_PCMN();
	
	/* initialize GHOST */
	
	initialize_GHOST();	
	
	/* generate random times for power pills appearance */
	static int i;
	
	srand(LPC_RIT->RICOUNTER);
	for (i=0;i<POWER_PILLS;i++){
			rnd_time_pwr_pills[i] = (GAME_TIME-1) - (rand() % 40);
	}
	
	/* display labyrinth */
	generate_labyrinth();
	
	/* display countdown timer (initialized to 60 s) */
	//display_cntdown_timer(game_time);
	
	/* display score (initialized to 0) */
	//display_score(score);
	
	/* display remaining lives (initialized to 1) */
	//display_lives(num_lives);
	
	/* generate and display pills (240) */
	generate_pills();
	map_mat_to_display(labyrinth_mat);
		 
	/*display pacman */
	display_pacman(PCMN->row, PCMN->col, PCMN->row_old, PCMN->col_old);
	
	/*display ghost */
	display_ghost(GHOST->row, GHOST->col, GHOST->row_old, GHOST->col_old,GHOST->Color);
	
	
	/*enable RIT for sampling joystick and button debouncing */
	enable_RIT();
	
}


void display_score(uint16_t score){
	
	char score_str[10];
	int x,y;

	if(score < 10){
		sprintf(score_str,"000%d",score);
	}
	else if(score < 100) {
		sprintf(score_str,"00%d",score);
	}
	else if(score < 1000) {
		sprintf(score_str,"0%d",score);
	}
	else{
		sprintf(score_str,"%d",score);
	}
	GUI_Text(23*8,0, (uint8_t *) "SCORE", White, Black);
	GUI_Text(23*8+4,16, (uint8_t *) score_str, White, Black);
	
}

void display_cntdown_timer(uint8_t timer){
	
	char timer_str[10];
	
	sprintf(timer_str,"%ds ",timer);
	
	GUI_Text(1*8,0, (uint8_t *) "Game Over in", White, Black);
	GUI_Text(5*8,16, (uint8_t *) timer_str, White, Black);
	
}

void display_lives(uint8_t lives){
	
	int x,y,i;
	
	x = 104;
	y = 29;
	
	for (i=0;i<3;i++){
		if(i<num_lives-1)
			draw_pacman(x,y,RIGHT);
		else
			clear_pacman(x,y);
	
		x+=PCMN_SIZE_PX+1;
	}
}


int move(Direction_TypeDef direction){

	static Bool has_moved;
	static Object_TypeDef obj;
	static Bool incremented_lives = FALSE;
	
	has_moved=FALSE;
	
	switch (direction){
		
		case UP:
			if (!hit_wall(UP)){
				PCMN->row-=1;
				has_moved = TRUE;
				
			}
			break;
		case DOWN:
			if(!hit_wall(DOWN)){			
				PCMN->row+=1;
				has_moved= TRUE;
			}
			break;
		case LEFT:
			if(!hit_wall(LEFT)){			
				PCMN->col-=1;
				has_moved= TRUE;
			}
			else if(hit_wall(LEFT) == 2){
				PCMN->col=COLS-1;
				has_moved= TRUE;
			}
			break;
		case RIGHT:
			if(!hit_wall(RIGHT)){			
				PCMN->col+=1;
				has_moved= TRUE;
			}
			else if(hit_wall(RIGHT) == 2){
				PCMN->col=0;
				has_moved= TRUE;
			}
			break;
		default:
			break;	
	}	
	
	if (has_moved){
		obj = hit_pill(direction);
		
		if (obj==STD_PILL){
				tot_pills--;
				score+=10;
				modified_score = TRUE;
		}
		else if (obj==PWR_PILL){
				tot_pills--;
				score+=50;
				modified_score=TRUE;
				playSound=TRUE;
				powerPillSound=TRUE;
				display_pill(PCMN->row,PCMN->col,NOT_PWR_PILL);
				GHOST->mode = FRIGHTENED;
				GHOST->Color = Blue2;
				GHOST->direction = opposite_direction(GHOST->direction);
				frightened_time = 10;
				
		}
		
		if(tot_pills == 0) {
			victory = TRUE;
			return FALSE;
		}
		
		if (score % 1000 == 0)
		{
			if (!incremented_lives){ 
				incremented_lives = TRUE;
				num_lives++;
				modified_lives=TRUE;
				//display_lives(num_lives);
			} 
		} 
		else 
		{
			incremented_lives = FALSE;
		}
			
		//display_score(score);	
		return 1;		
	}
	
	return FALSE;
}

int hit_wall(Direction_TypeDef direction){
	
	int x,y,row,col,i;
	
	row = PCMN->row;
	col = PCMN->col;
	
	
	switch (direction){
		
		case UP:
			for (i=col-PCMN_SIZE_MAT/2;i<=col+PCMN_SIZE_MAT/2;i++)
				if (labyrinth_mat[row-(PCMN_SIZE_MAT/2+1)][i]==WALL) return 1;
			return 0;
		case DOWN:
			for (i=col-PCMN_SIZE_MAT/2;i<=col+PCMN_SIZE_MAT/2;i++)
				if (labyrinth_mat[row+(PCMN_SIZE_MAT/2+1)][i]==WALL 
					|| labyrinth_mat[row+(PCMN_SIZE_MAT/2+1)][i]==GATE) return 1;
			return 0;
		case LEFT:
			if (row == 42 && col == 3)
				return 2;
			for (i=row-PCMN_SIZE_MAT/2;i<=row+PCMN_SIZE_MAT/2;i++)
				if (labyrinth_mat[i][col-(PCMN_SIZE_MAT/2+1)]==WALL) return 1;
			return 0;
		case RIGHT:
			if (row == 42 && col == COLS-4)
				return 2;
			for (i=row-PCMN_SIZE_MAT/2;i<=row+PCMN_SIZE_MAT/2;i++)
				if (labyrinth_mat[i][col+(PCMN_SIZE_MAT/2+1)]==WALL) return 1;
			return 0;
		default:
			return 0;
	}
	
}

void pacman_dynamics(Direction_TypeDef direction)
{
	
	static Bool has_moved;
	static int no_movement=0;
	
	switch (PCMN->direction) {
				
				case UP:
					has_moved = move(UP);
					if(!has_moved) has_moved = move(PCMN->old_direction);
					else PCMN->old_direction = NONE;
					break;
					
				case DOWN:
					has_moved = move(DOWN);
					if (!has_moved) has_moved = move(PCMN->old_direction);
					else PCMN->old_direction = NONE;
					break;
					
				case LEFT:
					has_moved = move(LEFT);
					if (!has_moved) has_moved = move(PCMN->old_direction);
					else PCMN->old_direction = NONE;   
					break;
					
				case RIGHT:
					has_moved = move(RIGHT);
					if (!has_moved) has_moved = move(PCMN->old_direction);
					else PCMN->old_direction = NONE;
					break;
				
				case NONE:
					break;
				
				default:
					break;
				
			}
		
			if (!has_moved){
				no_movement++;
				PCMN->direction=NONE;
			}
				else{
				no_movement=0;
			}
			if(n_interrupt_pcmn == 3){
					n_interrupt_pcmn=0;
					if(no_movement < 5)
						display_pacman(PCMN->row, PCMN->col, PCMN->row_old, PCMN->col_old);
			}
			
			if(n_interrupt_pill == 4)
			{
				n_interrupt_pill=0;
				display_pills(PWR_PILL);		
			}

}

Object_TypeDef hit_pill(Direction_TypeDef direction){
	
	int x,y,row,col;
	
	row = PCMN->row;
	col = PCMN->col;

	switch (direction){
		
		case UP:
			if (labyrinth_mat[row-PCMN_SIZE_MAT/2][col] == STD_PILL){
				labyrinth_mat[row-PCMN_SIZE_MAT/2][col] = NOT_PILL;
				return STD_PILL;
			}
			else if (labyrinth_mat[row-PCMN_SIZE_MAT/2][col] == PWR_PILL){
				labyrinth_mat[row-PCMN_SIZE_MAT/2][col] = NOT_PWR_PILL;
				display_pill(row-PCMN_SIZE_MAT/2,col,NOT_PWR_PILL);
				return PWR_PILL;
			}
			break;
		case DOWN:
			if (labyrinth_mat[row+PCMN_SIZE_MAT/2][col] == STD_PILL){
				labyrinth_mat[row+PCMN_SIZE_MAT/2][col] = NOT_PILL;
				return STD_PILL;
			}
			else if (labyrinth_mat[row+PCMN_SIZE_MAT/2][col] == PWR_PILL){
				labyrinth_mat[row+PCMN_SIZE_MAT/2][col] = NOT_PWR_PILL;
				display_pill(row+PCMN_SIZE_MAT/2,col,NOT_PWR_PILL);
				return PWR_PILL;
			}
			break;
		case LEFT:
			if (labyrinth_mat[row][col-PCMN_SIZE_MAT/2] == STD_PILL){
				labyrinth_mat[row][col-PCMN_SIZE_MAT/2] = NOT_PILL;
				return STD_PILL;
			}
			else if (labyrinth_mat[row][col-PCMN_SIZE_MAT/2] == PWR_PILL){
				labyrinth_mat[row][col-PCMN_SIZE_MAT/2] = NOT_PWR_PILL;
				display_pill(row,col-PCMN_SIZE_MAT/2,NOT_PWR_PILL);
				return PWR_PILL;
			}
			break;
		case RIGHT:
			if (labyrinth_mat[row][col+PCMN_SIZE_MAT/2] == STD_PILL){
				labyrinth_mat[row][col+PCMN_SIZE_MAT/2] = NOT_PILL;
				return STD_PILL;
			}
			else if (labyrinth_mat[row][col+PCMN_SIZE_MAT/2] == PWR_PILL){
				labyrinth_mat[row][col+PCMN_SIZE_MAT/2] = NOT_PWR_PILL;
				display_pill(row,col+PCMN_SIZE_MAT/2,NOT_PWR_PILL);
				return PWR_PILL;
			}
			break;
		default:
			break;
	}

	return SPACE;
}


void restart_after_hit(){
	
	PCMN->col = PCMN_START_COL;
	PCMN->row = PCMN_START_ROW;
	PCMN->direction=NONE;
	
	GHOST->row = GHOST_START_ROW;
	GHOST->col = GHOST_START_COL;
	GHOST->direction=NONE;
	GHOST->old_direction=NONE;
	GHOST->Color=Red;		 	

	hit = FALSE;
	display_ghost(GHOST->row, GHOST->col, GHOST->row_old, GHOST->col_old, GHOST->Color);
	display_pacman(PCMN->row, PCMN->col, PCMN->row_old, PCMN->col_old);
	
	computePath=TRUE;
	//display_lives(num_lives);
	
	enable_timer(1);
	respawn_time = 3;
	
	go = TRUE;
}

void initialize_PCMN(){
	
	PCMN->col = PCMN_START_COL;
	PCMN->row = PCMN_START_ROW;
	PCMN->col_old = -1;
	PCMN->row_old = -1;
	
	PCMN->direction=NONE;
	
}
void initialize_GHOST(){
	
	GHOST->row = GHOST_START_ROW;
	GHOST->col = GHOST_START_COL;
	GHOST->row_old = -1;
	GHOST->col_old = -1;
	GHOST->direction=NONE;
	GHOST->old_direction = NONE;
	GHOST->Color=Red;		 	
}

Direction_TypeDef opposite_direction(Direction_TypeDef dir){
	
	switch (dir){
		
		case UP:
			return DOWN;
		case DOWN:
			return UP;
		case LEFT:
			return RIGHT;
		case RIGHT:
			return LEFT;
		default:
			return NONE;
	}
	
}

void send_parameters_CAN(uint16_t score, uint8_t num_lives, uint8_t game_time){
	
	static uint32_t msg;
	
	msg = score | (num_lives << 16) | (game_time << 24);
	
	/* score */
	CAN_TxMsg.data[0] = msg & 0x000000FF;
	CAN_TxMsg.data[1] = (msg & 0x0000FF00) >> 8;
	
	/* remaining lives */
	CAN_TxMsg.data[2] = (msg & 0x00FF0000) >> 16;
	
	/* countdown timer */
	CAN_TxMsg.data[3] = (msg & 0xFF000000) >> 24;
	
	CAN_TxMsg.len = 4;
	CAN_TxMsg.id = 1;
	CAN_TxMsg.format = STANDARD_FORMAT;
	CAN_TxMsg.type = DATA_FRAME;
	CAN_wrMsg (1, &CAN_TxMsg);               /* transmit message */
		
}

