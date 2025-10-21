/* **************************************Copyright ©*************************************************************
 * Based on original code provided in the Computer Architectures course
 * at Politecnico di Torino.
 * Modified and extended by Gabriele Arcidiacono
 **--------------------------------------File Info--------------------------------------------------------------------
** File name:           timer.h
** Last modified Date:  
** Last modified Date:  02/29/2025
** Last Version:        V1.00
** Descriptions:        Prototypes of functions included in lib_timer.c and IRQ_timer.c files, which manage the timer peripheral
** Correlated files:    lib_timer.c, IRQ_timer.c
**-------------------------------------------------------------------------------------------------------------------
********************************************************************************************************************/

#ifndef __TIMER_H
#define __TIMER_H

#include <stdint.h>

/* init_timer.c */
extern uint32_t init_timer( uint8_t timer_num, uint8_t match_reg_num, uint32_t timerInterval );
extern void enable_timer( uint8_t timer_num );
extern void disable_timer( uint8_t timer_num );
extern void reset_timer( uint8_t timer_num );
/* IRQ_timer.c */
extern void TIMER0_IRQHandler (void);
extern void TIMER1_IRQHandler (void);

#endif /* end __TIMER_H */
/*****************************************************************************
**                            End Of File
******************************************************************************/
