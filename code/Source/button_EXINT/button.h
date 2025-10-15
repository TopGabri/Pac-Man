/* **************************************Copyright ©*************************************************************
 * Based on original code provided in the Computer Architectures course
 * at Politecnico di Torino.
 * Modified and extended by Gabriele Arcidiacono
 **--------------------------------------File Info--------------------------------------------------------------------
** File name:           button.h
** Last modified Date:  
** Last Version:        V1.00
** Descriptions:        Prototypes of functions included in lib_button.c and IRQ_button.c files
** Correlated files:    lib_button.c, IRQ_button.c
**-------------------------------------------------------------------------------------------------------------------
********************************************************************************************************************/


void BUTTON_init(void);

void EINT1_IRQHandler(void);
void EINT2_IRQHandler(void);
void EINT3_IRQHandler(void);

