/* **************************************Copyright ©*************************************************************
 * Based on original code provided in the Computer Architectures course
 * at Politecnico di Torino.
 * Modified and extended by Gabriele Arcidiacono
 * **************************************************************************************************************/
#include "button.h"
#include "LPC17xx.h"
#include "GLCD/GLCD.h" 
#include "RIT/RIT.h"
#include "Pacman/game.h"

void EINT0_IRQHandler (void)	  	/* KEY0														 */
{		
	
	reset_RIT();  /*reset RIT to count to 25 ms */
	NVIC_DisableIRQ(EINT1_IRQn);
	LPC_PINCON->PINSEL4    &= ~(1 << 20);     /* GPIO pin selection */
	LPC_SC->EXTINT &= (1 << 0);     /* clear pending interrupt         */
}


void EINT1_IRQHandler (void)	  	/* KEY1														 */
{
	NVIC_DisableIRQ(EINT1_IRQn);		/* disable Button interrupts			 */
	LPC_PINCON->PINSEL4    &= ~(1 << 22);     /* GPIO pin selection */
	LPC_SC->EXTINT &= (1 << 1);     /* clear pending interrupt         */
}

void EINT2_IRQHandler (void)	  	/* KEY2														 */
{
	
  LPC_SC->EXTINT &= (1 << 2);     /* clear pending interrupt         */    
}


