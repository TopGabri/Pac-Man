/* **************************************Copyright ©*************************************************************
 * Based on original code provided in the Computer Architectures course
 * at Politecnico di Torino.
 * Modified and extended by Gabriele Arcidiacono
 **--------------------------------------File Info--------------------------------------------------------------------
** File name:           RIT.h
** Last modified Date:  
** Last Version:        V1.00
** Descriptions:        Prototypes of functions included in lib_RIT.c and IRQ_RIT.c files, which manage the RIT (Repetitive Interrupt Timer) peripheral
** Correlated files:    lib_RIT.c, IRQ_RIT.c
**-------------------------------------------------------------------------------------------------------------------
********************************************************************************************************************/
#ifndef __RIT_H
#define __RIT_H

/* init_RIT.c */
extern uint32_t init_RIT( uint32_t RITInterval );
extern void enable_RIT( void );
extern void disable_RIT( void );
extern void reset_RIT( void );
/* IRQ_RIT.c */
extern void RIT_IRQHandler (void);

#endif /* end __RIT_H */
/*****************************************************************************
**                            End Of File
******************************************************************************/
