/* **************************************Copyright ©*************************************************************
 * Based on original code provided in the Computer Architectures course
 * at Politecnico di Torino.
 * Modified and extended by Gabriele Arcidiacono

 **---------------------------------------File Info--------------------------------------------------------------
** File name:           lib_timer.c
** Last modified Date:  2025-02-19
** Last Version:        V1.00
** Descriptions:        atomic functions to be used by higher sw levels
** Correlated files:    lib_timer.c, funct_timer.c, IRQ_timer.c
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include "LPC17xx.h"
#include "timer.h"

/******************************************************************************
** Function name:		enable_timer
**
** Descriptions:		Enable timer
**
** parameters:			timer number: 0 or 1
** Returned value:		None
**
******************************************************************************/
void enable_timer( uint8_t timer_num )
{
  if ( timer_num == 0 )
  {
	LPC_TIM0->TCR = 1;
  }
  else if ( timer_num == 1)
  {
	LPC_TIM1->TCR = 1;
  }
	else if (timer_num == 2)
	{
	LPC_TIM2->TCR = 1;
	}
	else if (timer_num == 3)
	{
	LPC_TIM3->TCR = 1;
	}
  return;
}

/******************************************************************************
** Function name:		disable_timer
**
** Descriptions:		Disable timer
**
** parameters:			timer number: 0 or 1
** Returned value:		None
**
******************************************************************************/
void disable_timer( uint8_t timer_num )
{
  if ( timer_num == 0 )
  {
	LPC_TIM0->TCR = 0;
  }
  else if ( timer_num == 1) 
  {
	LPC_TIM1->TCR = 0;
  }
  else if (timer_num == 2)
	{
	LPC_TIM2->TCR = 0;
	}
	else if (timer_num == 3)
	{
	LPC_TIM3->TCR = 0;
	}
}


/******************************************************************************
** Function name:		reset_timer
**
** Descriptions:		Reset timer
**
** parameters:			timer number: 0 or 1
** Returned value:		None
**
******************************************************************************/
void reset_timer( uint8_t timer_num )
{
  uint32_t regVal;

  if ( timer_num == 0 )
  {
	regVal = LPC_TIM0->TCR;
	regVal |= 0x02;
	LPC_TIM0->TCR = regVal;
  }
  else if (timer_num == 1)
  {
	regVal = LPC_TIM1->TCR;
	regVal |= 0x02;
	LPC_TIM1->TCR = regVal;
  }
	else if (timer_num == 2)
  {
	regVal = LPC_TIM2->TCR;
	regVal |= 0x02;
	LPC_TIM2->TCR = regVal;
  }
	else if (timer_num == 3)
  {
	regVal = LPC_TIM3->TCR;
	regVal |= 0x02;
	LPC_TIM3->TCR = regVal;
  }
	
  return;
}

uint32_t init_timer ( uint8_t timer_num, uint8_t match_reg_num, uint32_t TimerInterval )
{
	
	switch (timer_num) {
		
		case 0:
			switch (match_reg_num) {
				case 0:
					LPC_TIM0->MR0 = TimerInterval;
					LPC_TIM0->MCR = 3;  //issue an interrupt and reset TC when TC matches MR0
					break;
				case 1:
					LPC_TIM0->MR1 = TimerInterval;
					break;
				case 2:
					LPC_TIM0->MR2 = TimerInterval;
					break;
				case 3:
					LPC_TIM0->MR3 = TimerInterval;
					break;
				default:
					break;
			}
			NVIC_EnableIRQ(TIMER0_IRQn);
			NVIC_SetPriority(TIMER0_IRQn, 1);
			break;
			
		case 1:
			switch (match_reg_num) {
				case 0:
					LPC_TIM1->MR0 = TimerInterval;
					LPC_TIM1->MCR |= 3;   //  MCR <- xxxxx...xxx11 / issue interrupt and reset TC when TC matches MR0
					break;
				case 1:
					LPC_TIM1->MR1 = TimerInterval;
					break;
				case 2:
					LPC_TIM1->MR2 = TimerInterval;
					break;
				case 3:
					LPC_TIM1->MR3 = TimerInterval;
					break;
				default:
					break;
			}
			NVIC_EnableIRQ(TIMER1_IRQn);
			NVIC_SetPriority(TIMER1_IRQn, 1);
			break;
		
		case 2:
			LPC_SC->PCONP |= ( 1 << 22 );  //power on timer 2
			switch (match_reg_num) {
				case 0:
					LPC_TIM2->MR0 = TimerInterval;
				  LPC_TIM2->MCR |= 3;    //  MCR <- xxxxx...xx11 / issue interrupt and reset when TC matches MR0
					break;
				case 1:
					LPC_TIM2->MR1 = TimerInterval;
				  LPC_TIM2->MCR |= (1 << 3 );  // MCR <- xxxx..xx1xxx  / issue interrupt when TC matches MR1
					break;
				case 2:
					LPC_TIM2->MR2 = TimerInterval;
					LPC_TIM2->MCR |= (1 << 6 );  // MCR <- xxxx..xx1xxxxxx  / issue interrupt when TC matches MR1
					break;
				case 3:
					LPC_TIM2->MR3 = TimerInterval;
					break;
				default:
					break;
			}
			NVIC_EnableIRQ(TIMER2_IRQn);
			NVIC_SetPriority(TIMER2_IRQn, 2);
			break;
			
		case 3:
			LPC_SC->PCONP |= ( 1 << 23 );  //power on timer 3
			switch (match_reg_num) {
				case 0:
					LPC_TIM3->MR0 = TimerInterval;
					LPC_TIM3->MCR = 7;				 	//  MCR <- xxxxx...xx11 / issue interrupt and reset and stop when TC matches MR0
					break;
				case 1:
					LPC_TIM3->MR1 = TimerInterval;
					LPC_TIM3->MCR |= (1 << 3 );  
					break;
				case 2:
					LPC_TIM3->MR2 = TimerInterval;
					LPC_TIM3->MCR |= (1 << 6 );
					break;
				case 3:
					LPC_TIM3->MR3 = TimerInterval;
					break;
				default:
					break;
			}
			NVIC_EnableIRQ(TIMER3_IRQn);
			NVIC_SetPriority(TIMER3_IRQn, 2);
			break;
			
		default:
			break;
	}
			
	return (0);
}

/******************************************************************************
**                            End Of File
******************************************************************************/
