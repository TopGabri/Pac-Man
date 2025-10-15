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

#include "ghost.h"
#include "mapping.h"
#include "GLCD/GLCD.h"
#include <stdlib.h>
#include <math.h>


extern CHR_TypeDef* GHOST;
extern CHR_TypeDef* PCMN;
extern Object_TypeDef labyrinth_mat[ROWS][COLS];
extern int currPathIndex;
Direction_TypeDef path[MAX_PATH_LENGTH];
Direction_TypeDef directions[] = {UP,LEFT,DOWN,RIGHT};
int pathLength;



Bool is_valid_direction(int row, int col, Direction_TypeDef dir){
	
	int i;
	
	switch(dir){
		
		case UP:
			for (i=-2;i<=2;i++)
				if (labyrinth_mat[row-3][col+i]==WALL)
					return FALSE;
			break;
				
		case DOWN:
			for (i=-2;i<=2;i++)
				if (labyrinth_mat[row+3][col+i]==WALL)
					return FALSE;
			break;
				
		case LEFT:
			for (i=-2;i<=2;i++)
				if (labyrinth_mat[row+i][col-3]==WALL)
					return FALSE;
			break;
				
		case RIGHT:
			for (i=-2;i<=2;i++)
				if (labyrinth_mat[row+i][col+3]==WALL)
					return FALSE;
			break;
				
		default:
			break;					
	}
	return TRUE;	
	
}

int new_row(int row, Direction_TypeDef direction){
	
	if (direction == UP)
		return row-1;
	else if (direction == DOWN)
		return row+1;
	
	return row;
}

int new_col(int col, Direction_TypeDef direction){
	
	if (direction == LEFT)
		return col-1;
	else if (direction == RIGHT)
		return col+1;
	
	return col;
}


Bool opposite_directions(Direction_TypeDef dir1, Direction_TypeDef dir2){
	
	if (dir1 == LEFT && dir2 == RIGHT)
		return TRUE;
	if (dir1 == RIGHT && dir2 == LEFT)
		return TRUE;
	if (dir1 == UP && dir2 == DOWN)
		return TRUE;
	if (dir1 == DOWN && dir2 == UP)
		return TRUE;
	
	return FALSE;
}


void ghost_movement(int row_target, int col_target){
	
	pathLength = 0;
	
	
	int row,col, newRow, newCol;
	int index = 0;
	int i;
	float dist, min_dist;
	Direction_TypeDef dir, min_dir = NONE;
	Bool isValid;
	
	row = GHOST->row;
	col = GHOST->col;
	
	/* exit the cage */
	if (row <= GHOST_START_ROW && row > (GHOST_START_ROW - 9) && col == GHOST_START_COL){
		for(i=0;i<row-(GHOST_START_ROW-9);i++){
			path[index++]=UP;
			row=new_row(row,dir);
		}
	}
	
	/*re-draw gate */
	LCD_DrawLine(112,148,126,148,White);
	LCD_DrawLine(112,149,126,149,White);
	
	/* 
		 algorithm to implement path finding:
		 each time choose the direction that will bring 
		 the ghost closer to the target and save into array,
		 until either the target or end of the array 
		 are reached. 
	*/
	
	while(index<MAX_PATH_LENGTH){
		
		min_dist = sqrt(ROWS*ROWS+COLS*COLS);
		
		for(i=0;i<4;i++){
			dir = directions[i];
			isValid = FALSE;
			
			if(index == 0){
				if (!opposite_directions(GHOST->direction,dir))
					isValid = TRUE;
			}
			else {
				if (!opposite_directions(path[index-1],dir))
					isValid = TRUE;
			}
			if(!is_valid_direction(row,col,dir))
					isValid = FALSE;
			
			if (isValid){
				
				newRow = new_row(row,dir);
				newCol = new_col(col,dir);
				dist = sqrt((newRow-row_target)*(newRow-row_target)+(newCol-col_target)*(newCol-col_target));
				
				if(dist < min_dist){
					min_dist = dist;
					min_dir = dir;
				}
			}
		}
		
		path[index++]=min_dir;
		GHOST->direction=dir;
		row = new_row(row,min_dir);
		col = new_col(col,min_dir);
		
		if (row == row_target && col == col_target){
			pathLength = index;
			return;
		}
	}
}
			

void display_ghost(int row, int col, int row_old, int col_old, uint16_t Color)
{
	
	int x_old, y_old;
	
	int y = get_y_coordinate_from_row(row);
	int x = get_x_coordinate_from_col(col);
	
	if (row_old != -1 && col_old != -1){
		x_old = get_x_coordinate_from_col(col_old);
		y_old = get_y_coordinate_from_row(row_old);
		clear_pacman(x_old, y_old);
	}
	
	draw_ghost(x,y,GHOST->direction,Color);	
	
	if (labyrinth_mat[GHOST->row_old][GHOST->col_old]!=SPACE)
			display_pill(GHOST->row_old, GHOST->col_old,labyrinth_mat[GHOST->row_old][GHOST->col_old]);
		
	
	GHOST->col_old = GHOST->col;
	GHOST->row_old = GHOST->row;
	
}


void draw_ghost(int x, int y, Direction_TypeDef direction, uint16_t Color){
	
	
	int x1,x2,y1,y2,i,k;
	
	x1=x;
	y1=y-GHOST_SIZE_PX/2;
	y2=y+GHOST_SIZE_PX/2-2;
	
	LCD_DrawLine(x1,y1,x1,y2,Color);
	
	for (i=0;i<2;i++){
		
		if(i==0) k=1;
		else k=-1;
		
		x1=x+k;
		y1=y-GHOST_SIZE_PX/2;
		y2=y+GHOST_SIZE_PX/2;
		LCD_DrawLine(x1,y1,x1,y2,Color);
		
		x1+=k;
		y1+=1;
		y2-=1;
		LCD_DrawLine(x1,y1,x1,y2,Color);
		
		x1+=k;
		y2-=1;
		LCD_DrawLine(x1,y1,x1,y2,Color);
		
		x1+=k;
		y1+=1;
		LCD_DrawLine(x1,y1,x1,y2,Color);
		
		x1+=k;
		y1+=1;
		y2+=1;
		LCD_DrawLine(x1,y1,x1,y2,Color);
		
		x1+=k;
		y1+=3;
		y2+=1;
		LCD_DrawLine(x1,y1,x1,y2,Color);
	}
	
}


Bool hit_pacman(){
	
	int row1,col1,row2,col2;
		
	row1=GHOST->row;
	row2=PCMN->row;
	col1=GHOST->col;
	col2=PCMN->col;
	
	/* ghost hits pacman : */
	
	
	//from above
	if (row1+2 >= row2-2 && row1<row2 && col1==col2)
		return TRUE;
	//from below
	if (row1-2 <= row2+2 && row1>row2 && col1==col2)
		return TRUE;
	//from the left
	if (col1+2 >= col2-2 && col1<col2 && row1==row2)
		return TRUE;
	//from the right
	if (col1-2 <= col2+2 && col1>col2 && row1==row2)
		return TRUE;
	
	return FALSE;
	
}
	