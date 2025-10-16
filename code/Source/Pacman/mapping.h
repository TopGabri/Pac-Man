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