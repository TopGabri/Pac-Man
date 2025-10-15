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
** File name:           labyrinth.h
** Last modified Date:  
** Last Version:        V1.00
** Descriptions:        Prototypes of functions and constants included in labyrinth.c file
** Correlated files:    labyrinth.c
**-------------------------------------------------------------------------------------------------------------------
********************************************************************************************************************/

#ifndef __LABYRINTH_H
#define __LABYRINTH_H


#define INTERLINE_WIDTH 2
#define RECTANGLE_HEIGHT 19
#define TUBE_WIDTH 10
#define CORRIDOR_WIDTH 15
#define RECESS_HEIGHT 31
#define NARROW_RECT_WIDTH 28
#define WIDE_RECT_WIDTH 37
#define CENTER_HEIGHT 2*RECESS_HEIGHT+CORRIDOR_WIDTH+4*(INTERLINE_WIDTH+2)-2*(CORRIDOR_WIDTH+1)-2*(TUBE_WIDTH+2)
#define SMALL_RECESS_WIDTH 17
#define GATE_SIZE 15

#define X_START_LEFT 0
#define X_START_RIGHT MAX_X-2
#define Y_START 38
#define Y_END 312
#define X_HALF MAX_X/2-1

void generate_labyrinth();



#endif