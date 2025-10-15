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
** File name:           mapping.h
** Last modified Date:  
** Last Version:        V1.00
** Descriptions:        Prototypes of functions and constants included in mapping.c file
** Correlated files:    mapping.c
**-------------------------------------------------------------------------------------------------------------------
********************************************************************************************************************/

#ifndef __MAPPING_H
#define __MAPPING_H

#include "game.h"


#define ROWS 91
#define COLS 79


int get_row_from_y_coordinate(int y);
int get_col_from_x_coordinate(int x);
int get_y_coordinate_from_row(int row);
int get_x_coordinate_from_col(int col);
void map_horizontal_line_to_matrix(int x1, int x2, int y, Object_TypeDef el, Object_TypeDef mat[ROWS][COLS]);
void map_vertical_line_to_matrix(int y1, int y2, int x, Object_TypeDef el, Object_TypeDef mat[ROWS][COLS]);
void map_std_pill_to_matrix(int x, int y, Object_TypeDef mat[ROWS][COLS]);
void map_mat_to_display(Object_TypeDef mat[ROWS][COLS]);

#endif