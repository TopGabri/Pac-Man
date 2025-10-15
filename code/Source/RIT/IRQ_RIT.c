/* **************************************Copyright ©*************************************************************
 * Based on original code provided in the Computer Architectures course
 * at Politecnico di Torino.
 * Modified and extended by Gabriele Arcidiacono
**---------------------------------------File Info---------------------------------------------------------------
** File name:           IRQ_RIT.c
** Last modified Date:  2025-02-19
** Last Version:        V1.00
** Descriptions:        functions to manage RIT interrupts. 
**						Responsible for joystick driven movement of Pac-man, game start, pause and end, countdown, pills
** Correlated files:    RIT.h, Pacman/ 
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include "LPC17xx.h"
#include "RIT.h"
#include "../led/led.h"
#include "GLCD/GLCD.h"
#include "Pacman/pacman.h"
#include "Pacman/mapping.h"
#include "timer/timer.h"
#include "music/music.h"
#include "Pacman/sounds.h"

/******************************************************************************
** Function name:		RIT_IRQHandler
**
** Descriptions:		REPETITIVE INTERRUPT TIMER handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/

#define UPTICKS 2


Object_TypeDef object;

extern CHR_TypeDef * PCMN;

extern NOTE *currSound;

extern int tot_pills;
extern uint16_t score;
extern uint8_t game_time;

extern Bool pause_game;
extern Bool ended;
extern Bool victory;
extern Bool hit;
extern Bool event;
extern Bool game_over;
extern Bool go;
extern Bool computePath;
extern Bool modified_lives;
extern Bool modified_time;
extern Bool modified_score;
extern Bool playSound;
extern Bool openingSong;
extern Bool powerPillSound;
extern Bool winSong;

extern uint8_t num_lives;
extern uint8_t respawn_time;

extern uint32_t msg;

uint8_t n_interrupt_pcmn = 0;
uint8_t n_interrupt_pill = 0;
uint8_t n_interrupt_param = 0;

void RIT_IRQHandler (void)
{				
	
	static int pressed=0;	
	pressed++;
	
	static uint8_t n_movements = 0;
	static uint8_t no_movement = 0;
	static int up = 0, down = 0, left = 0, right = 0;
	
	static int currentNote = 0;
	static int ticks = 0;
		
	
	/* button debouncing of KEY1 */
	if((LPC_GPIO2->FIOPIN & (1<<10)) == 0){  /* KEY0 pressed */
		reset_RIT();
		switch(pressed){
			case 2:  //50 ms: debouce button KEY0	
				event = TRUE;
				/* if game ended and KEY0 is pressed, restart */
				if(ended){
					disable_RIT();
					pacman();
				}
				/*toggle game pause */
				else{
					pause_game = !pause_game;
					go = !go;
				}
				break;
		}
	}
	else {	/* button released */
		pressed=0;
		NVIC_EnableIRQ(EINT1_IRQn);							 /* disable Button interrupts			*/
		LPC_PINCON->PINSEL4    |= (1 << 22);     /* External interrupt 0 pin selection */
	}
	
	
	/* SOUND EFFECTS */
	if (playSound)
	{
		/* opening up song: "Francesco Totti - Bello Figo" */
		if (openingSong)
		{
			if(!isNotePlaying())
			{
				++ticks;
				if(ticks == UPTICKS)
				{
					ticks = 0;
					playNote(francesco_totti[currentNote++]);
				}
			}
			if(currentNote == (sizeof(francesco_totti) / sizeof(francesco_totti[0])))
			{
				currentNote=0;
				ticks=0;
			}
		}	

		/* power pill sound effect (to fix) */
		
		/*
		else if (powerPillSound)
		{
		
			if(!isNotePlaying())
			{
				++ticks;
				if(ticks == UPTICKS)
				{
					ticks = 0;
					playNote(power_up[currentNote++]);
				}
			}
			if(currentNote == (sizeof(power_up) / sizeof(power_up[0])))
			{
				powerPillSound = FALSE;
				playSound=FALSE;
				currentNote=0;
			}
		}
		*/
		
		/* winnning song */
		else if (winSong)
		{
		
			if(!isNotePlaying())
			{
				++ticks;
				if(ticks == UPTICKS)
				{
					ticks = 0;
					playNote(blue[currentNote++]);
				}
			}
			if(currentNote == (sizeof(blue) / sizeof(blue[0])))
			{
				powerPillSound = FALSE;
				playSound=FALSE;
				currentNote=0;
			}
		}
		
	}
		
	/* game logic */
 	
	if (!ended){
	/* VICTORY */
		if(victory){
			disable_timer(0);
			disable_timer(1);
			ended = 1;
			LCD_Clear(Black);
			GUI_Text(88,162, (uint8_t *) "VICTORY!", Green, Black);
			playSound = TRUE;
			winSong=TRUE;
		}
		/* GAME OVER */
		else if (game_over){
			disable_timer(0);
			disable_timer(1);
			LCD_Clear(Black);
			GUI_Text(84,162,(uint8_t *) "GAME OVER", Red, Black);
			ended = 1;
		}
		/*GAME PAUSED*/
		else if (pause_game && event){
			disable_timer(0);
			disable_timer(1);
			event = FALSE;
			GUI_Text(11*9+2,38+3+16*9+1,(uint8_t *) "PAUSE",Red,Black);
			playSound=TRUE;
			openingSong=TRUE;
		}
		/* GAME NOT IN PAUSE MODE */
		else if (hit)
		{	
		/* HIT BY GHOST */
			if (event){
				disable_timer(1);
				reset_timer(1);
				go = FALSE;
				event = FALSE;
				num_lives--;
				modified_lives=TRUE;
				if (num_lives == 0)
					game_over = TRUE;
			}
			if (respawn_time == 0) {
				restart_after_hit();		
			}
		}
		/* GAME ONGOING */
		else if (go)
		{
				/* GAME RESUMED */
				if(event){
					event = FALSE;
					playSound=FALSE;
					openingSong=FALSE;
					/*
					ghost_movement(PCMN->row, PCMN->col);
					currPathIndex = 0;
					*/
					computePath=TRUE;
					enable_timer(0); //countdown timer
					enable_timer(1); //ghost
					GUI_Text(11*9+2,38+3+16*9+1,(uint8_t *) "     ",Red,Black);
				}
				

				if (modified_lives || modified_score || modified_time)
				{	
					n_interrupt_param++;
					/* send SCORE, REMAINING LIVES and COUNTDOWN TIMER to CAN */
					send_parameters_CAN(score, num_lives, game_time); 
					if(n_interrupt_param==1){
						n_interrupt_param=0;
						if (modified_time){
							display_cntdown_timer((msg & 0xFF000000) >> 24);
							modified_time=FALSE;
						}
						if (modified_lives){
							display_lives((msg & 0x00FF0000) >> 16);
							modified_lives=FALSE;
						}
						if (modified_score){
							display_score(msg & 0x0000FFFF);
							modified_score=FALSE;
						}
					}
				}
				
				n_interrupt_pcmn++;
				n_interrupt_pill++;
			
				if((LPC_GPIO1->FIOPIN & (1<<29)) == 0){	
						/* Joytick UP pressed */
						up++;
						if (up == 1) {
							down = left = right = 0;
							PCMN->old_direction = PCMN->direction;
							PCMN->direction = UP;
						}
				}
				else if ((LPC_GPIO1->FIOPIN & (1<<28)) == 0) {			
						/* Joystick RIGHT pressed */
						right++;
						if (right == 1) {
							down = left = up = 0;
							PCMN->old_direction = PCMN->direction;
							PCMN->direction = RIGHT;
						}
				}
				else if ((LPC_GPIO1->FIOPIN & (1<<27)) == 0) {
						/* Joystick LEFT pressed */
						left++;
						if (left == 1) {
							down = up = right = 0;
							PCMN->old_direction = PCMN->direction;
							PCMN->direction = LEFT;
						}
				}
				else if ((LPC_GPIO1->FIOPIN & (1<<26)) == 0) {
						/* Joystick DOWN pressed */
						down++;
						if (down == 1) {
							up = left = right = 0;
							PCMN->old_direction = PCMN->direction;
							PCMN->direction = DOWN;
						}
				}

				pacman_dynamics(PCMN->direction);
			}
		}

		
	
  LPC_RIT->RICTRL |= 0x1;	/* clear interrupt flag */
	
  return;
}

/******************************************************************************
**                            End Of File
******************************************************************************/
