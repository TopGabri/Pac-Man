/* **************************************Copyright ©*************************************************************
 * Based on original code provided in the Computer Architectures course
 * at Politecnico di Torino.
 * Modified and extended by Gabriele Arcidiacono

 **---------------------------------------File Info--------------------------------------------------------------
** File name:           IRQ_timer.c
** Last modified Date:  2025-02-19
** Last Version:        V1.00
** Descriptions:        functions to manage T0, T1 and T2 interrupts 
** Correlated files:    timer.h, Pacman/
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include <string.h>
#include "LPC17xx.h"
#include "timer.h"
#include "RIT/RIT.h"
#include "../GLCD/GLCD.h" 
#include "../TouchPanel/TouchPanel.h"
#include <stdio.h> /*for sprintf*/
#include "Pacman/game.h"
#include "Pacman/mapping.h"
#include "Pacman/labyrinth.h"
#include "Pacman/ghost.h"
#include "Pacman/pills.h"
#include <stdlib.h>
#include <time.h>

/******************************************************************************
** Function name:		Timer0_IRQHandler
**
** Descriptions:		Timer/Counter 0 interrupt handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/


static uint16_t SinTable[45] =
{
    410, 467, 523, 576, 627, 673, 714, 749, 778,
    799, 813, 819, 817, 807, 789, 764, 732, 694, 
    650, 602, 550, 495, 438, 381, 324, 270, 217,
    169, 125, 87 , 55 , 30 , 12 , 2  , 0  , 6  ,   
    20 , 41 , 70 , 105, 146, 193, 243, 297, 353
};


volatile int currPathIndex;
volatile uint8_t time_frightned;
volatile uint8_t n_chase = 0;
volatile Bool fallback;

extern uint16_t score;
extern uint8_t game_time;
extern uint8_t respawn_time;
extern uint8_t frightened_time;
extern Difficulty difficulty;
extern Object_TypeDef labyrinth_mat[ROWS][COLS];
extern int rnd_time_pwr_pills[6];
extern uint8_t n_rnd_pills;
extern int tot_pills;
extern int ended;
extern CHR_TypeDef *PCMN;
extern CHR_TypeDef *GHOST;
extern Direction_TypeDef path[MAX_PATH_LENGTH];
extern int pathLength;
extern Bool hit;
extern Bool game_over;
extern Bool event;
extern Bool computePath;
//extern Bool modified_parameters;
extern Bool modified_score;
extern Bool modified_time;
extern Bool is_note_playing;

void TIMER0_IRQHandler (void)
{
	
	//disable_RIT();
	static int i;
	static int rnd_row;
	static int rnd_col;
	static Bool valid = FALSE;
	static int seed;
	
	
	if (!hit){
		game_time--;
		modified_time=TRUE;
		//display_cntdown_timer(game_time);
		
		/* game OVER */
		if(game_time==0){
			game_over = TRUE;
			enable_RIT();
			LPC_TIM0->IR = 1;
			return;
		}
		/* increase difficulty */
		else if(game_time==GAME_TIME/2){
			difficulty.chase++;
			n_chase=0;
		}
		else if (game_time==GAME_TIME/4){
			difficulty.chase++;
			n_chase=0;
		}
		
		/* FRIGHTENED mode */
		if (GHOST->mode == FRIGHTENED){
			frightened_time--;
			if(frightened_time==0)
			{
				GHOST->mode = CHASE;
				GHOST->Color = Red;
				computePath=TRUE;
				/*
				ghost_movement(PCMN->row, PCMN->col);
				currPathIndex=0;		
				*/
			}
		}
		else {
			if (tot_pills > 0 && n_rnd_pills > 0){
				seed = LPC_RIT->RICOUNTER ^ PCMN->col ^ PCMN->row;
				srand(seed);
				for(i=0;i<POWER_PILLS;i++){
					if(game_time==rnd_time_pwr_pills[i]){
							while(!valid){
								rnd_row = rand() % ROWS;
								rnd_col = rand() % COLS;
								if (labyrinth_mat[rnd_row][rnd_col] == STD_PILL){
									valid=1;
								}
							}
							labyrinth_mat[rnd_row][rnd_col] = PWR_PILL;
							n_rnd_pills--;
							display_pill(rnd_row,rnd_col,PWR_PILL);
							valid = 0;
					}
				}
			}
		}
	}
	else 
	{	
		respawn_time--;
	}

	//enable_RIT();
	
  LPC_TIM0->IR = 1;			/* clear interrupt flag */
  return;
}


/******************************************************************************
** Function name:		Timer1_IRQHandler
**
** Descriptions:		Timer/Counter 1 interrupt handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/
void TIMER1_IRQHandler (void)
{
	
	//disable_RIT();
	static int n_frightened = 0;
	static int n_disp=0;
	static int n_path=0;
	static int n_disp_pill=0;
	static Object_TypeDef pillType;
	static Direction_TypeDef dir;

	/* CHASE MODE */
	
	if (GHOST->mode == CHASE){
		
		n_frightened=0;
		n_chase++;
		if (n_chase==4-difficulty.chase){
			n_chase=0;
			n_disp++;
			n_path++;
			
			/* how often is path recomputed */
			if (n_path == 10 || computePath){
				n_path = 0;
				computePath = FALSE;
				ghost_movement(PCMN->row, PCMN->col);
				currPathIndex=0;
			}
			
			/* move ghost by 1 cell */
			if (currPathIndex<pathLength){
				GHOST->direction = path[currPathIndex];
				GHOST->row = new_row(GHOST->row,GHOST->direction);
				GHOST->col = new_col(GHOST->col,GHOST->direction);
				currPathIndex++;
				n_disp_pill++;
				if (hit_pacman()){
					hit = TRUE;
					event = TRUE;
					display_ghost(GHOST->row, GHOST->col, GHOST->row_old, GHOST->col_old, GHOST->Color);
				}
			}
			
			/* display ghost every 3 movements */
			if(n_disp==3){
				n_disp=0;
				display_ghost(GHOST->row, GHOST->col, GHOST->row_old, GHOST->col_old, GHOST->Color);
			}
			
			/* display pill 3 ghost movements after previous pill was stepped on */
			if(n_disp_pill==3){
				pillType = labyrinth_mat[GHOST->old_pill.row][GHOST->old_pill.col];
				if(pillType==STD_PILL){
					display_pill(GHOST->old_pill.row, GHOST->old_pill.col,pillType);	
				}
			}

			/*check if ghost stepped on pill */
			if (labyrinth_mat[GHOST->row][GHOST->col]==STD_PILL){
				GHOST->old_pill=(Point){GHOST->row,GHOST->col};
				n_disp_pill=0;
				n_disp=0;
			}
		}
			
	}
	
	/* FRIGHTENED MODE */
	
	else if (GHOST->mode == FRIGHTENED){
		n_chase=0;
		n_frightened++;
		
		
		if (n_frightened==4-difficulty.frightened){
			n_frightened=0;
			n_disp++;
			n_disp_pill++;
			
			if (!fallback){

				dir = GHOST->direction;
				srand(GHOST->row ^ GHOST->col ^ PCMN->row ^ PCMN->col);
				while(!is_valid_direction(GHOST->row, GHOST->col, dir) || dir == opposite_direction(GHOST->direction))
					dir = rand() % 4;
				
				GHOST->direction = dir;
				GHOST->row = new_row(GHOST->row,dir);
				GHOST->col = new_col(GHOST->col,dir);
				
				if (hit_pacman()){
					score+=100;
					//modified_parameters = TRUE;
					modified_score=TRUE;
					//display_score(score);
					difficulty.frightened=3;
					fallback = TRUE;
					computePath = TRUE;					
				}
				
			}
			else {
				if (computePath){
					computePath = FALSE;
					ghost_movement(GHOST_START_ROW,GHOST_START_COL);
					currPathIndex=0;					
				}

				if (currPathIndex<pathLength){
					GHOST->direction = path[currPathIndex];
					GHOST->row = new_row(GHOST->row,GHOST->direction);
					GHOST->col = new_col(GHOST->col,GHOST->direction);
					currPathIndex++;
					n_disp_pill++;
				}
				
				if (GHOST->row == GHOST_START_ROW && GHOST->col == GHOST_START_COL){
					fallback = FALSE;
					GHOST->mode = CHASE;
					GHOST->Color=Red;
					computePath=TRUE;
					difficulty.frightened=1;
				}
			
			}
				
			/* display ghost every 3 movements */
			if(n_disp==3){
				n_disp=0;
				display_ghost(GHOST->row, GHOST->col, GHOST->row_old, GHOST->col_old, GHOST->Color);
			}
			
			/* display pill 3 ghost movements after previous pill was stepped on */
			if(n_disp_pill==3){
				pillType = labyrinth_mat[GHOST->old_pill.row][GHOST->old_pill.col];
				if(pillType==STD_PILL){
					display_pill(GHOST->old_pill.row, GHOST->old_pill.col,pillType);	
				}
			}

			/*check if ghost stepped on pill */
			if (labyrinth_mat[GHOST->row][GHOST->col]==STD_PILL){
				GHOST->old_pill=(Point){GHOST->row,GHOST->col};
				n_disp_pill=0;
				n_disp=0;
			}
			
		}
	}
	
	
	//enable_RIT();
  LPC_TIM1->IR = 1;			/* clear interrupt flag */
  return;
}



/******************************************************************************
** Function name:		Timer2_IRQHandler
**
** Descriptions:		Timer/Counter 2 interrupt handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/


void TIMER2_IRQHandler (void) 
{
	
	static int sineticks=0;
	/* DAC management */	
	static int currentValue; 
	currentValue = SinTable[sineticks];
	currentValue -= 410;
	currentValue /= 1;
	currentValue += 410;
	LPC_DAC->DACR = currentValue <<6;
	sineticks++;
	if(sineticks==45) sineticks=0;

	
	LPC_TIM2->IR = 1;			/* clear interrupt flag */
	return;
}


/******************************************************************************
** Function name:		Timer3_IRQHandler
**
** Descriptions:		Timer/Counter 3 interrupt handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/

void TIMER3_IRQHandler (void)
{
	disable_timer(2);
	is_note_playing = FALSE;
	LPC_TIM3->IR = 1;			/* clear interrupt flag */
	return;
}


/******************************************************************************
**                            End Of File
******************************************************************************/
