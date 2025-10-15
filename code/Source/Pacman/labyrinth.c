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

#include "GLCD/GLCD.h" 
#include "labyrinth.h"
#include "mapping.h"
#include "game.h"
#include "pills.h"



Object_TypeDef labyrinth_mat[ROWS][COLS] = {SPACE};



void generate_labyrinth(){
		
	int x,x1,x2;
	int y = Y_START,y1,y2;
		
	int i,j,k;
	
	int row, col;
	
	//each iteration displays 1 vertical half of the labyrinth 
	for (i=0;i<2;i++){
		
		if (i==0){
			x=0;
			k=1;
		} else {
			x=X_START_RIGHT;
			k=-1;
		}
		
		/* HORIZONTAL lines */
		
		//UPPER SIDE
		
		//HORIZONTAL line [0]
			
		x1=x;
		x2=X_HALF;
			
		LCD_DrawLine(x1,y,x2,y,Blue);
		map_horizontal_line_to_matrix(x1,x2,y,WALL,labyrinth_mat);
		
		
		
		//HORIZONTAL line [1]
		
		y+=INTERLINE_WIDTH+1;
		x1=x+k*(INTERLINE_WIDTH + 1);
		x2=X_HALF-k*1;
		LCD_DrawLine(x1,y,x2,y,Blue);
		map_horizontal_line_to_matrix(x1,x2,y,WALL,labyrinth_mat);

		//HORIZONTAL line [2]
		
		y+=CORRIDOR_WIDTH+1;
		
		x1=x+k*(INTERLINE_WIDTH+1+CORRIDOR_WIDTH+1);
		x2=x1+k*(NARROW_RECT_WIDTH+1);
		LCD_DrawLine(x1,y,x2,y,Blue);
		map_horizontal_line_to_matrix(x1,x2,y,WALL,labyrinth_mat);
		
		x1=x2+k*(CORRIDOR_WIDTH+1);
		x2=x1+k*(WIDE_RECT_WIDTH+1);
		LCD_DrawLine(x1,y,x2,y,Blue);
		map_horizontal_line_to_matrix(x1,x2,y,WALL,labyrinth_mat);
		
		//HORIZONTAL line [3]
		
		y+=RECTANGLE_HEIGHT+1;	
		
		x1=x+k*(INTERLINE_WIDTH+1+CORRIDOR_WIDTH+1);
		x2=x1+k*(NARROW_RECT_WIDTH+1);
		LCD_DrawLine(x1,y,x2,y,Blue);
		map_horizontal_line_to_matrix(x1,x2,y,WALL,labyrinth_mat);
		
		x1=x2+k*(CORRIDOR_WIDTH+1);
		x2=x1+k*(WIDE_RECT_WIDTH+1);
		LCD_DrawLine(x1,y,x2,y,Blue);
		map_horizontal_line_to_matrix(x1,x2,y,WALL,labyrinth_mat);
		
		x1=x2+k*(CORRIDOR_WIDTH+1);
		x2=X_HALF;
		LCD_DrawLine(x1,y,x2,y,Blue);	
		map_horizontal_line_to_matrix(x1,x2,y,WALL,labyrinth_mat);
		
		//HORIZONTAL line [4]
		
		y+=CORRIDOR_WIDTH+1;
		
		x1=x+k*(INTERLINE_WIDTH+1+CORRIDOR_WIDTH+1);
		x2=x1+k*(NARROW_RECT_WIDTH+1);
		LCD_DrawLine(x1,y,x2,y,Blue);
		map_horizontal_line_to_matrix(x1,x2,y,WALL,labyrinth_mat);
		
		x1=x2+k*(CORRIDOR_WIDTH+1);
		x2=x1+k*(TUBE_WIDTH+1);
		LCD_DrawLine(x1,y,x2,y,Blue);
		map_horizontal_line_to_matrix(x1,x2,y,WALL,labyrinth_mat);
		
		x1=x2+k*(CORRIDOR_WIDTH+1);
		x2=X_HALF;
		LCD_DrawLine(x1,y,x2,y,Blue);
		map_horizontal_line_to_matrix(x1,x2,y,WALL,labyrinth_mat);
			
		//HORIZONTAL line [5]
		
		y+=TUBE_WIDTH+1;
		
		x1=x+k*(INTERLINE_WIDTH+1+CORRIDOR_WIDTH+1);
		x2=x1+k*(NARROW_RECT_WIDTH+1);
		LCD_DrawLine(x1,y,x2,y,Blue);
		map_horizontal_line_to_matrix(x1,x2,y,WALL,labyrinth_mat);
		
		x1=x2+k*(CORRIDOR_WIDTH+1+TUBE_WIDTH+1+CORRIDOR_WIDTH+1);
		x2=X_HALF-k*1;
		LCD_DrawLine(x1,y,x2,y,Blue);
		map_horizontal_line_to_matrix(x1,x2,y,WALL,labyrinth_mat);

		
		//HORIZONTAL line [6]
		
		y+=CORRIDOR_WIDTH+1;
		
		x1=x+k*(INTERLINE_WIDTH+1);
		x2=x1+k*(CORRIDOR_WIDTH+1+NARROW_RECT_WIDTH+1);
		LCD_DrawLine(x1,y,x2,y,Blue);
		map_horizontal_line_to_matrix(x1,x2,y,WALL,labyrinth_mat);
		
		x1=x2+k*(CORRIDOR_WIDTH+1+TUBE_WIDTH+1);
		x2=x1+k*(WIDE_RECT_WIDTH-TUBE_WIDTH);
		LCD_DrawLine(x1,y,x2,y,Blue);
		map_horizontal_line_to_matrix(x1,x2,y,WALL,labyrinth_mat);
		
		
		
		//HORIZONTAL line [7]
		
		y+=INTERLINE_WIDTH+1;
		
		x1=x;
		x2=x1+k*(INTERLINE_WIDTH+1+CORRIDOR_WIDTH+1+NARROW_RECT_WIDTH-INTERLINE_WIDTH);
		LCD_DrawLine(x1,y,x2,y,Blue);
		map_horizontal_line_to_matrix(x1,x2,y,WALL,labyrinth_mat);
		
		
		//HORIZONTAL line [8] 
		
		y=y-INTERLINE_WIDTH+TUBE_WIDTH;
		
		x1=x+k*(INTERLINE_WIDTH+1+CORRIDOR_WIDTH+1+NARROW_RECT_WIDTH+1+CORRIDOR_WIDTH+1+TUBE_WIDTH+1);
		x2=x1+k*(WIDE_RECT_WIDTH-TUBE_WIDTH);
		LCD_DrawLine(x1,y,x2,y,Blue);
		map_horizontal_line_to_matrix(x1,x2,y,WALL,labyrinth_mat);
		
		x1=x2+k*(CORRIDOR_WIDTH+1);
		x2=X_HALF;
		LCD_DrawLine(x1,y,x2,y,Blue);
		map_horizontal_line_to_matrix(x1,x2,y,WALL,labyrinth_mat);
		
		
		//HORIZONTAL line [9] (end of upper recess)
		
		y=y-TUBE_WIDTH+INTERLINE_WIDTH+RECESS_HEIGHT+1;
		
		x1=x;
		x2=x1+k*(INTERLINE_WIDTH+1+5*(PILLS_DISTANCE+PILLS_SIZE)-INTERLINE_WIDTH-1);
		LCD_DrawLine(x1,y,x2,y,Blue);
		map_horizontal_line_to_matrix(x1,x2,y,WALL,labyrinth_mat);
		
		y+=INTERLINE_WIDTH+1;
		
		x2+=k*(INTERLINE_WIDTH+1);
		LCD_DrawLine(x1,y,x2,y,Blue);
		map_horizontal_line_to_matrix(x1,x2,y,WALL,labyrinth_mat);
		
		x1=x2+k*(CORRIDOR_WIDTH+1);
		x2=x1+k*(TUBE_WIDTH+1);
		LCD_DrawLine(x1,y,x2,y,Blue);
		map_horizontal_line_to_matrix(x1,x2,y,WALL,labyrinth_mat);
		
		//central CAGE (upper side)
		
		y1=y-PILLS_SIZE-PILLS_DISTANCE-PILLS_SIZE+1;
		
		
		x1=x2+k*(CORRIDOR_WIDTH+1);
		x2=X_HALF-k*(GATE_SIZE/2+1);
		LCD_DrawLine(x1,y1,x2,y1,Blue);
		map_horizontal_line_to_matrix(x1,x2,y1,WALL,labyrinth_mat);
		
		y1+=INTERLINE_WIDTH+1;
		
		x1+=k*(INTERLINE_WIDTH+1);
		
		LCD_DrawLine(x1,y1,x2,y1,Blue);
		map_horizontal_line_to_matrix(x1,x2,y1,WALL,labyrinth_mat);
		
		
		//GATE for ghosts
		
		y1-=INTERLINE_WIDTH+1;
		y1+=1;
		x1=x2+k*1;
		x2=X_HALF;
		LCD_DrawLine(x1,y1,x2,y1,White);
		map_horizontal_line_to_matrix(x1,x2,y1,GATE,labyrinth_mat);
		y1+=1;
		LCD_DrawLine(x1,y1,x2,y1,White);
		map_horizontal_line_to_matrix(x1,x2,y1,GATE,labyrinth_mat);
		
				
		//LOWER side
		
		//HORIZONTAL line [10] (start of lower recess)
		
		y+=CORRIDOR_WIDTH+1;
		
		x1=x;
		x2=x1+k*(INTERLINE_WIDTH+1+5*(PILLS_DISTANCE+PILLS_SIZE));
		LCD_DrawLine(x1,y,x2,y,Blue);
		map_horizontal_line_to_matrix(x1,x2,y,WALL,labyrinth_mat);
		
		x1=x2+k*(CORRIDOR_WIDTH+1);
		x2=x1+k*(TUBE_WIDTH+1);
		LCD_DrawLine(x1,y,x2,y,Blue);
		map_horizontal_line_to_matrix(x1,x2,y,WALL,labyrinth_mat);
		
		//HORIZONTAL line [11] 
		
		y+=INTERLINE_WIDTH+1;
		
		x1=x;
		x2=x1+k*(INTERLINE_WIDTH+1+CORRIDOR_WIDTH+1+NARROW_RECT_WIDTH+1-INTERLINE_WIDTH-1);
		LCD_DrawLine(x1,y,x2,y,Blue);
		map_horizontal_line_to_matrix(x1,x2,y,WALL,labyrinth_mat);
		
		
		//central CAGE (lower side)
		
		y1=y-INTERLINE_WIDTH-1+PILLS_SIZE+PILLS_DISTANCE+PILLS_SIZE-1;
		x1=x2+k*(INTERLINE_WIDTH+1+CORRIDOR_WIDTH+1+TUBE_WIDTH+1+CORRIDOR_WIDTH+1);
		x2=X_HALF;
		
		LCD_DrawLine(x1,y1,x2,y1,Blue);
		map_horizontal_line_to_matrix(x1,x2,y1,WALL,labyrinth_mat);
		
		
		y1-=INTERLINE_WIDTH+1;
		
		x1=x1+k*(INTERLINE_WIDTH+1);
		x2=X_HALF;
		LCD_DrawLine(x1,y1,x2,y1,Blue);	
		map_horizontal_line_to_matrix(x1,x2,y1,WALL,labyrinth_mat);
		
		//HORIZONTAL line [12] 
		
		y+=RECESS_HEIGHT+1;
		
		x1=x;
		x2=x1+k*(INTERLINE_WIDTH+1+CORRIDOR_WIDTH+1+NARROW_RECT_WIDTH+1-INTERLINE_WIDTH-1);
		
		LCD_DrawLine(x1,y,x2,y,Blue);	
		map_horizontal_line_to_matrix(x1,x2,y,WALL,labyrinth_mat);
		
		//HORIZONTAL line [13] (end of lower recess)
		
		y+=INTERLINE_WIDTH+1;
		
		x1=x+k*(INTERLINE_WIDTH+1);
		x2=x1+k*(CORRIDOR_WIDTH+1+NARROW_RECT_WIDTH+1);
		
		LCD_DrawLine(x1,y,x2,y,Blue);	
		map_horizontal_line_to_matrix(x1,x2,y,WALL,labyrinth_mat);
		
		
		x1=x2+k*(CORRIDOR_WIDTH+1);
		x2=x1+k*(TUBE_WIDTH+1);
		LCD_DrawLine(x1,y,x2,y,Blue);	
		map_horizontal_line_to_matrix(x1,x2,y,WALL,labyrinth_mat);
		
		x1=x2+k*(CORRIDOR_WIDTH+1);
		x2=X_HALF-k*1;
		LCD_DrawLine(x1,y,x2,y,Blue);	
		map_horizontal_line_to_matrix(x1,x2,y,WALL,labyrinth_mat);
		
		y1=y-TUBE_WIDTH-1;
		x2=X_HALF;
		
		LCD_DrawLine(x1,y1,x2,y1,Blue);	
		map_horizontal_line_to_matrix(x1,x2,y1,WALL,labyrinth_mat);
		
		//HORIZONTAL line [14]
		
		y+=CORRIDOR_WIDTH+1;
		
		x1=x+k*(INTERLINE_WIDTH+1+CORRIDOR_WIDTH+1);
		x2=x1+k*(NARROW_RECT_WIDTH+1);		
		LCD_DrawLine(x1,y,x2,y,Blue);	
		map_horizontal_line_to_matrix(x1,x2,y,WALL,labyrinth_mat);
		
		x1=x2+k*(CORRIDOR_WIDTH+1);
		x2=x1+k*(WIDE_RECT_WIDTH+1);		
		LCD_DrawLine(x1,y,x2,y,Blue);
		map_horizontal_line_to_matrix(x1,x2,y,WALL,labyrinth_mat);
		
		
		//HORIZONTAL line [15]
		
		y+=TUBE_WIDTH+1;
		
		x1=x+k*(INTERLINE_WIDTH+1+CORRIDOR_WIDTH+1);
		x2=x1+k*(NARROW_RECT_WIDTH-TUBE_WIDTH);
		LCD_DrawLine(x1,y,x2,y,Blue);
		map_horizontal_line_to_matrix(x1,x2,y,WALL,labyrinth_mat);
		
		x1=x2+k*(TUBE_WIDTH+1+CORRIDOR_WIDTH+1);
		x2=x1+k*(WIDE_RECT_WIDTH+1);		
		LCD_DrawLine(x1,y,x2,y,Blue);
		map_horizontal_line_to_matrix(x1,x2,y,WALL,labyrinth_mat);
		
		x1=x2+k*(CORRIDOR_WIDTH+1);
		x2=X_HALF;
		LCD_DrawLine(x1,y,x2,y,Blue);
		map_horizontal_line_to_matrix(x1,x2,y,WALL,labyrinth_mat);
		
		//HORIZONTAL line [16]
		
		y+=CORRIDOR_WIDTH+1;
		
		x1=x+k*(INTERLINE_WIDTH+1);
		x2=x1+k*(SMALL_RECESS_WIDTH+1);
		LCD_DrawLine(x1,y,x2,y,Blue);
		map_horizontal_line_to_matrix(x1,x2,y,WALL,labyrinth_mat);
		
		x1=x2+k*(CORRIDOR_WIDTH+1+TUBE_WIDTH+1+CORRIDOR_WIDTH+1);
		x2=x1+k*(TUBE_WIDTH+1);
		LCD_DrawLine(x1,y,x2,y,Blue);
		map_horizontal_line_to_matrix(x1,x2,y,WALL,labyrinth_mat);
		
		x1=x2+k*(CORRIDOR_WIDTH+1);
		x2=X_HALF;
		LCD_DrawLine(x1,y,x2,y,Blue);
		map_horizontal_line_to_matrix(x1,x2,y,WALL,labyrinth_mat);
		
		
		//HORIZONTAL line [17]
		
		y+=TUBE_WIDTH+1;
		
		x1=x+k*(INTERLINE_WIDTH+1);
		x2=x1+k*(SMALL_RECESS_WIDTH+1);
		LCD_DrawLine(x1,y,x2,y,Blue);
		map_horizontal_line_to_matrix(x1,x2,y,WALL,labyrinth_mat);
		
		x1=x2+k*(CORRIDOR_WIDTH+1);
		x2=x1+k*(TUBE_WIDTH+1);
		LCD_DrawLine(x1,y,x2,y,Blue);
		map_horizontal_line_to_matrix(x1,x2,y,WALL,labyrinth_mat);
		
		x1=x2+k*(CORRIDOR_WIDTH+1+TUBE_WIDTH+1+CORRIDOR_WIDTH+1);
		x2=X_HALF-k*1;
		LCD_DrawLine(x1,y,x2,y,Blue);
		map_horizontal_line_to_matrix(x1,x2,y,WALL,labyrinth_mat);
		
		
		//HORIZONTAL line [18]
		
		y+=CORRIDOR_WIDTH+1;
		
		x1=x+k*(INTERLINE_WIDTH+1+CORRIDOR_WIDTH+1);
		x2=x1+k*(NARROW_RECT_WIDTH+1+CORRIDOR_WIDTH+1);
		LCD_DrawLine(x1,y,x2,y,Blue);
		map_horizontal_line_to_matrix(x1,x2,y,WALL,labyrinth_mat);
		
		x1=x2+k*(TUBE_WIDTH+1);
		x2=x1+k*(WIDE_RECT_WIDTH-TUBE_WIDTH);
		LCD_DrawLine(x1,y,x2,y,Blue);
		map_horizontal_line_to_matrix(x1,x2,y,WALL,labyrinth_mat);
		
		//HORIZONTAL line [19]
		
		y+=TUBE_WIDTH+1;
		
		x1=x+k*(INTERLINE_WIDTH+1+CORRIDOR_WIDTH+1);
		x2=x1+k*(NARROW_RECT_WIDTH+1+CORRIDOR_WIDTH+1+WIDE_RECT_WIDTH+1);
		LCD_DrawLine(x1,y,x2,y,Blue);
		map_horizontal_line_to_matrix(x1,x2,y,WALL,labyrinth_mat);
		
		x1=x2+k*(CORRIDOR_WIDTH+1);
		x2=X_HALF;
		LCD_DrawLine(x1,y,x2,y,Blue);
		map_horizontal_line_to_matrix(x1,x2,y,WALL,labyrinth_mat);
		
		//HORIZONTAL line [20]
		
		y+=CORRIDOR_WIDTH+1;
		
		x1=x+k*(INTERLINE_WIDTH+1);
		x2=X_HALF;
		LCD_DrawLine(x1,y,x2,y,Blue);
		map_horizontal_line_to_matrix(x1,x2,y,WALL,labyrinth_mat);
		
		//HORIZONTAL line [21]
		
		y+=INTERLINE_WIDTH+1;
		
		x1=x;
		x2=X_HALF;
		LCD_DrawLine(x1,y,x2,y,Blue);
		map_horizontal_line_to_matrix(x1,x2,y,WALL,labyrinth_mat);
			
		
		
		/* VERTICAL lines */
		
		y=Y_START;
		
		if (i == 0) x=X_START_LEFT;
		else x=X_START_RIGHT;
		
		//VERTICAL line [0]
		
		y1=y;
		y2=y1+INTERLINE_WIDTH+1+8*(PILLS_DISTANCE+PILLS_SIZE)+PILLS_DISTANCE+1+INTERLINE_WIDTH+1;
		LCD_DrawLine(x,y1,x,y2,Blue);
		map_vertical_line_to_matrix(y1, y2, x, WALL, labyrinth_mat);
		
		y1=y2+RECESS_HEIGHT+1+INTERLINE_WIDTH+1+CORRIDOR_WIDTH+1+INTERLINE_WIDTH+1+RECESS_HEIGHT+1;
		y2=Y_END;
		LCD_DrawLine(x,y1,x,y2,Blue);
		map_vertical_line_to_matrix(y1, y2, x, WALL, labyrinth_mat);
		
		
		//line [1]
		x+=k*(INTERLINE_WIDTH+1);
		
		y1=y+INTERLINE_WIDTH+1;
		y2=y1+CORRIDOR_WIDTH+1+RECTANGLE_HEIGHT+1+CORRIDOR_WIDTH+1+TUBE_WIDTH+1+CORRIDOR_WIDTH+1;
		LCD_DrawLine(x,y1,x,y2,Blue);
		map_vertical_line_to_matrix(y1, y2, x, WALL, labyrinth_mat);
		
		y1=y2+INTERLINE_WIDTH+1+RECESS_HEIGHT+1+INTERLINE_WIDTH+1+CORRIDOR_WIDTH+1+INTERLINE_WIDTH+1+RECESS_HEIGHT+1+INTERLINE_WIDTH+1;
		y2=y1+CORRIDOR_WIDTH+1+TUBE_WIDTH+1+CORRIDOR_WIDTH+1;
		LCD_DrawLine(x,y1,x,y2,Blue);
		map_vertical_line_to_matrix(y1, y2, x, WALL, labyrinth_mat);
		
		y1=y2+TUBE_WIDTH+1;
		y2=y1+CORRIDOR_WIDTH+1+TUBE_WIDTH+1+CORRIDOR_WIDTH+1;
		LCD_DrawLine(x,y1,x,y2,Blue);
		map_vertical_line_to_matrix(y1, y2, x, WALL, labyrinth_mat);
		
		//VERTICAL line [2]
		
		x+=k*(CORRIDOR_WIDTH+1);
		
		y1=y+INTERLINE_WIDTH+1+CORRIDOR_WIDTH+1;
		y2=y1+RECTANGLE_HEIGHT+1;
		LCD_DrawLine(x,y1,x,y2,Blue);
		map_vertical_line_to_matrix(y1, y2, x, WALL, labyrinth_mat);
		
		y1=y2+CORRIDOR_WIDTH+1;
		y2=y1+TUBE_WIDTH+1;
		LCD_DrawLine(x,y1,x,y2,Blue);
		map_vertical_line_to_matrix(y1, y2, x, WALL, labyrinth_mat);
		
		y1=y2+CORRIDOR_WIDTH+1+INTERLINE_WIDTH+1+RECESS_HEIGHT+1+INTERLINE_WIDTH+1+CORRIDOR_WIDTH+1+INTERLINE_WIDTH+1+RECESS_HEIGHT+1+INTERLINE_WIDTH+1+CORRIDOR_WIDTH+1;
		y2=y1+TUBE_WIDTH+1;
		LCD_DrawLine(x,y1,x,y2,Blue);
		map_vertical_line_to_matrix(y1, y2, x, WALL, labyrinth_mat);
		
		y1=y2+CORRIDOR_WIDTH+1;
		y2=y1+TUBE_WIDTH+1;
		x1=x+k*(-CORRIDOR_WIDTH-1+SMALL_RECESS_WIDTH+1);
		LCD_DrawLine(x1,y1,x1,y2,Blue);
		map_vertical_line_to_matrix(y1, y2, x1, WALL, labyrinth_mat);
		
		y1=y2+CORRIDOR_WIDTH+1;
		y2=y1+TUBE_WIDTH+1;
		LCD_DrawLine(x,y1,x,y2,Blue);
		map_vertical_line_to_matrix(y1, y2, x, WALL, labyrinth_mat);
		
		//VERTICAL line [3]
		
		x+=k*(NARROW_RECT_WIDTH+1);
		
		y1=y+INTERLINE_WIDTH+1+CORRIDOR_WIDTH+1;
		y2=y1+RECTANGLE_HEIGHT+1;
		LCD_DrawLine(x,y1,x,y2,Blue);
		map_vertical_line_to_matrix(y1, y2, x, WALL, labyrinth_mat);
		
		y1=y2+CORRIDOR_WIDTH+1;
		y2=y1+TUBE_WIDTH+1;
		LCD_DrawLine(x,y1,x,y2,Blue);
		map_vertical_line_to_matrix(y1, y2, x, WALL, labyrinth_mat);
		
		y1=y2+CORRIDOR_WIDTH+1;
		y2=y1+INTERLINE_WIDTH+1+RECESS_HEIGHT+1+INTERLINE_WIDTH+1;
		LCD_DrawLine(x,y1,x,y2,Blue);
		map_vertical_line_to_matrix(y1, y2, x, WALL, labyrinth_mat);
		
		x1=x-k*(INTERLINE_WIDTH+1);
		y1+=INTERLINE_WIDTH+1;
		y2-=INTERLINE_WIDTH+1;
		LCD_DrawLine(x1,y1,x1,y2,Blue);
		map_vertical_line_to_matrix(y1, y2, x1, WALL, labyrinth_mat);
		
		y1=y2+INTERLINE_WIDTH+1+CORRIDOR_WIDTH+1;
		y2=y1+INTERLINE_WIDTH+1+RECESS_HEIGHT+1+INTERLINE_WIDTH+1;
		LCD_DrawLine(x,y1,x,y2,Blue);
		map_vertical_line_to_matrix(y1, y2, x, WALL, labyrinth_mat);
		
		x1=x-k*(INTERLINE_WIDTH+1);
		y1+=INTERLINE_WIDTH+1;
		y2-=INTERLINE_WIDTH+1;
		LCD_DrawLine(x1,y1,x1,y2,Blue);
		map_vertical_line_to_matrix(y1, y2, x1, WALL, labyrinth_mat);
		
		y1=y2+INTERLINE_WIDTH+1+CORRIDOR_WIDTH+1;
		y2=y1+TUBE_WIDTH+1+CORRIDOR_WIDTH+1+TUBE_WIDTH+1;
		LCD_DrawLine(x,y1,x,y2,Blue);
		map_vertical_line_to_matrix(y1, y2, x, WALL, labyrinth_mat);
		
		x1=x-k*(TUBE_WIDTH+1);
		y1+=TUBE_WIDTH+1;
		LCD_DrawLine(x1,y1,x1,y2,Blue);
		map_vertical_line_to_matrix(y1, y2, x1, WALL, labyrinth_mat);
		
		//VERTICAL line [4]
		
		x+=k*(CORRIDOR_WIDTH+1);
		
		y1=y+INTERLINE_WIDTH+1+CORRIDOR_WIDTH+1;
		y2=y1+RECTANGLE_HEIGHT+1;
		LCD_DrawLine(x,y1,x,y2,Blue);
		map_vertical_line_to_matrix(y1, y2, x, WALL, labyrinth_mat);
		
		y1=y2+CORRIDOR_WIDTH+1;
		y2=y1+TUBE_WIDTH+1+CORRIDOR_WIDTH+1+INTERLINE_WIDTH+1+RECESS_HEIGHT+1+INTERLINE_WIDTH+1;
		LCD_DrawLine(x,y1,x,y2,Blue);
		map_vertical_line_to_matrix(y1, y2, x, WALL, labyrinth_mat);
		
		y1=y2+CORRIDOR_WIDTH+1;
		y2=y1+INTERLINE_WIDTH+1+RECESS_HEIGHT+1+INTERLINE_WIDTH+1;
		LCD_DrawLine(x,y1,x,y2,Blue);
		map_vertical_line_to_matrix(y1, y2, x, WALL, labyrinth_mat);
		
		y1=y2+CORRIDOR_WIDTH+1;
		y2=y1+TUBE_WIDTH+1;
		LCD_DrawLine(x,y1,x,y2,Blue);
		map_vertical_line_to_matrix(y1, y2, x, WALL, labyrinth_mat);
		
		y1=y2+CORRIDOR_WIDTH+1;
		y2=y1+TUBE_WIDTH+1+CORRIDOR_WIDTH+1;
		LCD_DrawLine(x,y1,x,y2,Blue);
		map_vertical_line_to_matrix(y1, y2, x, WALL, labyrinth_mat);
		
		
		//VERTICAL line [5]
		
		x+=k*(TUBE_WIDTH+1);
		
		y1=y+INTERLINE_WIDTH+1+CORRIDOR_WIDTH+1+RECTANGLE_HEIGHT+1+CORRIDOR_WIDTH+1;
		y2=y1+TUBE_WIDTH+1+CORRIDOR_WIDTH+1;
		LCD_DrawLine(x,y1,x,y2,Blue);
		map_vertical_line_to_matrix(y1, y2, x, WALL, labyrinth_mat);
		
		y1=y2+TUBE_WIDTH+1;
		y2=y1+TUBE_WIDTH+1+CORRIDOR_WIDTH+1;
		LCD_DrawLine(x,y1,x,y2,Blue);
		map_vertical_line_to_matrix(y1, y2, x, WALL, labyrinth_mat);
		
		y1=y2+CORRIDOR_WIDTH+1;
		y2=y1+INTERLINE_WIDTH+1+RECESS_HEIGHT+1+INTERLINE_WIDTH+1;
		LCD_DrawLine(x,y1,x,y2,Blue);
		map_vertical_line_to_matrix(y1, y2, x, WALL, labyrinth_mat);
		
		y1=y2+CORRIDOR_WIDTH+1+TUBE_WIDTH+1+CORRIDOR_WIDTH+1;
		y2=y1+TUBE_WIDTH+1+CORRIDOR_WIDTH+1;
		LCD_DrawLine(x,y1,x,y2,Blue);
		map_vertical_line_to_matrix(y1, y2, x, WALL, labyrinth_mat);
		
		//VERTICAL line [6]
		
		x+=k*(CORRIDOR_WIDTH+1);
		
		y1=y+INTERLINE_WIDTH+1+CORRIDOR_WIDTH+1+RECTANGLE_HEIGHT+1+CORRIDOR_WIDTH+1;
		y2=y1+TUBE_WIDTH+1;
		LCD_DrawLine(x,y1,x,y2,Blue);
		map_vertical_line_to_matrix(y1, y2, x, WALL, labyrinth_mat);
		
		
		y1=y2+CORRIDOR_WIDTH+1+TUBE_WIDTH+1+CORRIDOR_WIDTH+1;
		y2=y1+CENTER_HEIGHT;
		LCD_DrawLine(x,y1,x,y2,Blue);
		map_vertical_line_to_matrix(y1, y2, x, WALL, labyrinth_mat);
		
		x+=k*(INTERLINE_WIDTH+1);
		
		y1=y1+INTERLINE_WIDTH+1;
		y2=y1-INTERLINE_WIDTH-1+CENTER_HEIGHT+1-INTERLINE_WIDTH-1;
		LCD_DrawLine(x,y1,x,y2,Blue);
		map_vertical_line_to_matrix(y1, y2, x, WALL, labyrinth_mat);
		
		x-=k*(INTERLINE_WIDTH+1);
		
		y1=y2+INTERLINE_WIDTH+1+CORRIDOR_WIDTH+1;
		y2=y1+TUBE_WIDTH+1;
		LCD_DrawLine(x,y1,x,y2,Blue);
		map_vertical_line_to_matrix(y1, y2, x, WALL, labyrinth_mat);
		
		y1=y2+CORRIDOR_WIDTH+1+TUBE_WIDTH+1+CORRIDOR_WIDTH+1;
		y2=y1+TUBE_WIDTH+1;
		LCD_DrawLine(x,y1,x,y2,Blue);
		map_vertical_line_to_matrix(y1, y2, x, WALL, labyrinth_mat);
		
		
		//VERTICAL line [7]
		
		x=x-k*(CORRIDOR_WIDTH+TUBE_WIDTH-WIDE_RECT_WIDTH+1);
		
		y1=y+INTERLINE_WIDTH+1+CORRIDOR_WIDTH+1;
		y2=y1+RECTANGLE_HEIGHT+1;
		LCD_DrawLine(x,y1,x,y2,Blue);
		map_vertical_line_to_matrix(y1, y2, x, WALL, labyrinth_mat);
		
		y1=y2+CORRIDOR_WIDTH+1+TUBE_WIDTH+1+CORRIDOR_WIDTH+1;
		y2=y1+TUBE_WIDTH+1;
		LCD_DrawLine(x,y1,x,y2,Blue);
		map_vertical_line_to_matrix(y1, y2, x, WALL, labyrinth_mat);
		
		y1=y2+CORRIDOR_WIDTH+1+CENTER_HEIGHT+1+CORRIDOR_WIDTH+1+TUBE_WIDTH+1+CORRIDOR_WIDTH+1;
		y2=y1+TUBE_WIDTH+1;
		LCD_DrawLine(x,y1,x,y2,Blue);
		map_vertical_line_to_matrix(y1, y2, x, WALL, labyrinth_mat);
		
		y1=y2+CORRIDOR_WIDTH+1+TUBE_WIDTH+1+CORRIDOR_WIDTH+1;
		y2=y1+TUBE_WIDTH+1;
		LCD_DrawLine(x,y1,x,y2,Blue);
		map_vertical_line_to_matrix(y1, y2, x, WALL, labyrinth_mat);
		
		
		//VERTICAL line [8]
		
		x+=k*(CORRIDOR_WIDTH+1);
		
		y1=y+INTERLINE_WIDTH+1;
		y2=y1+CORRIDOR_WIDTH+1+RECTANGLE_HEIGHT+1;
		LCD_DrawLine(x,y1,x,y2,Blue);
		map_vertical_line_to_matrix(y1, y2, x, WALL, labyrinth_mat);
		
		y1=y2+CORRIDOR_WIDTH+1+TUBE_WIDTH+1;
		y2=y1+CORRIDOR_WIDTH+1+TUBE_WIDTH+1;
		LCD_DrawLine(x,y1,x,y2,Blue);
		map_vertical_line_to_matrix(y1, y2, x, WALL, labyrinth_mat);
		
		y1=y2+CORRIDOR_WIDTH+1+CENTER_HEIGHT+1+CORRIDOR_WIDTH+1+TUBE_WIDTH+1;
		y2=y1+CORRIDOR_WIDTH+1+TUBE_WIDTH+1;
		LCD_DrawLine(x,y1,x,y2,Blue);
		map_vertical_line_to_matrix(y1, y2, x, WALL, labyrinth_mat);
		
		y1=y2+CORRIDOR_WIDTH+1+TUBE_WIDTH+1;
		y2=y1+CORRIDOR_WIDTH+1+TUBE_WIDTH+1;
		LCD_DrawLine(x,y1,x,y2,Blue);
		map_vertical_line_to_matrix(y1, y2, x, WALL, labyrinth_mat);
	}
		
}
	
