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
**--------------------------------------File Info--------------------------------------------------------------------
** File name:           pills.h
** Last modified Date:  
** Last Version:        V1.00
** Descriptions:        Prototypes of functions included in pills.c file
** Correlated files:    pills.c
**-------------------------------------------------------------------------------------------------------------------
********************************************************************************************************************/

#ifndef __PILLS_H
#define __PILLS_H

#include "game.h"

typedef enum {
	HORIZONTAL,
	VERTICAL
} Orientation_TypeDef;

#define PILLS_DISTANCE 6
#define PILLS_SIZE 3

void generate_pills();
void display_pill(int row, int col, Object_TypeDef type);
void generate_set_pills(int x, int y, int k, int n_pills, Orientation_TypeDef orientation);
void display_pills(Object_TypeDef type);


#endif