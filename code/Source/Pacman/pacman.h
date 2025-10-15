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
** File name:           pacman.h
** Last modified Date:  
** Last Version:        V1.00
** Descriptions:        Prototypes of functions included in pacman.c file
** Correlated files:    pacman.c
**-------------------------------------------------------------------------------------------------------------------
********************************************************************************************************************/
#ifndef __PACMAN_H 
#define __PACMAN_H

#include <stdint.h>

#include "game.h"

#define PCMN_START_X 119
#define PCMN_START_Y 247
#define PCMN_START_COL 39
#define PCMN_START_ROW 69
#define PCMN_SIZE_PX 15
#define PCMN_SIZE_MAT 5

void display_pacman(int row, int col, int row_old, int col_old);
void draw_pacman(int x, int y,Direction_TypeDef direction);
void draw_mouth(int x, int y, Direction_TypeDef direction);
void clear_pacman(int row, int col);



#endif

/*********************************************************************************************************
      END FILE
*********************************************************************************************************/

