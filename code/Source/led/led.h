/* **************************************Copyright ©*************************************************************
 * Based on original code provided in the Computer Architectures course
 * at Politecnico di Torino.
 **--------------------------------------File Info--------------------------------------------------------------------
** File name:           led.h
** Last modified Date:  
** Last modified Date:  02/29/2025
** Last Version:        V1.00
** Descriptions:        Prototypes of functions included in lib_led.c and funct_led.c files, which manage the LED peripheral
** Correlated files:    lib_led.c, funct_led.c
**-------------------------------------------------------------------------------------------------------------------
********************************************************************************************************************/

#ifndef __LED_H
#define __LED_H

/* lib_led */
void LED_init(void);
void LED_deinit(void);

/* funct_led */
void LED_On (unsigned int num);
void LED_Off (unsigned int num);
void LED_Out(unsigned int value);

#endif