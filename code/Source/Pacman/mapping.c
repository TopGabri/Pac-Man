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
*********************************************************************************************************************/

#include "mapping.h"
#include "labyrinth.h"

extern Object_TypeDef labyrinth_mat[ROWS][COLS];
extern int tot_pills;

/* 
		mapping functions from display to matrix: 
		(display) x -> column (matrix)
		(display) y -> row (matrix)
*/
	
int get_row_from_y_coordinate(int y){
	
	y-=38;
	
	//if y is outside the boundaries of the labyrinth, return -1
	
	if (y <= 0 || y > 273) return -1;
	
	return (y-1)/3;
}


int get_col_from_x_coordinate(int x){
	
	//if x is outside the boundaries of the labyrinth, return -1
	
	if (x <= 0 || x > 237) return -1;
	
	return (x-1)/3;
}

/*
	mapping functions from matrix to display:
	(matrix) column -> x (display)
	(matrix) row -> y (display)
*/

int get_y_coordinate_from_row(int row){
	
	if (row < 0 || row >= ROWS) return -1;
	
	return row*3+2+Y_START;	
}

int get_x_coordinate_from_col(int col){
	
	if (col < 0 || col >= COLS) return -1;
	
	return col*3+2;	
}


void map_horizontal_line_to_matrix(int x1, int x2, int y, Object_TypeDef el, Object_TypeDef mat[ROWS][COLS]){
	
	int row, col,i;
	
	row = get_row_from_y_coordinate(y);
	if (row == -1) return;
	
	if (x1 <= x2){
		
		for (i=x1;i<=x2;i++){
			col = get_col_from_x_coordinate(i);
			if (col != -1) mat[row][col]=el;
		}		
	}
	else {
		
		for (i=x2;i<=x1;i++){
			col = get_col_from_x_coordinate(i);
			if (col != -1) mat[row][col]=el;
		}			
	}
	
}


void map_vertical_line_to_matrix(int y1, int y2, int x, Object_TypeDef el, Object_TypeDef mat[ROWS][COLS]){
	
	int row, col, i;
	
	col = get_col_from_x_coordinate(x);
	if (col == -1) return;
	
	if (y1 <= y2){
		
		for (i=y1;i<=y2;i++){
			row = get_row_from_y_coordinate(i);
			if (row != -1) mat[row][col]=el;
		}		
	}
	else {
		
		for (i=y2;i<=y1;i++){
			row = get_row_from_y_coordinate(i);
			if (row != -1) mat[row][col]=el;
		}			
	}	

}


void map_std_pill_to_matrix(int x, int y, Object_TypeDef mat[ROWS][COLS]){
	
	int row, col,i;
	
	row = get_row_from_y_coordinate(y);
	col = get_col_from_x_coordinate(x);
	
	mat[row][col] = STD_PILL;		
	
	
}

void map_mat_to_display(Object_TypeDef mat[ROWS][COLS]){
	
	int i,j,x,y;
	
	for (i=0;i<ROWS;i++){
		for (j=0;j<COLS;j++){
			
			switch (mat[i][j]){
				
				case STD_PILL:
					display_pill(i,j,STD_PILL);
					break;
					
				default:
					break;
			}			
		}
	}
	
	
	
	
	
}


