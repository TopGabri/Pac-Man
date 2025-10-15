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

#include "pills.h"
#include "GLCD/GLCD.h"
#include "mapping.h"
#include "labyrinth.h"
#include "game.h"
#include <stdio.h>

const int x_coordinates[8] = {1,1,0,-1,-1,-1,0,1};
const int y_coordinates[8] = {0,-1,-1,-1,0,1,1,1};

extern Object_TypeDef labyrinth_mat[ROWS][COLS];

int tot_pills;

void generate_pills(){
	
	int x,y,i,n,k;
	
	int x_i;
	int y_i = Y_START;
	
	
	//generate pills on left half and mirror on right half
	
	for (n=0;n<2;n++){
	
		if (n==0){
			x_i=0;
			k=1;
		} else {
			x_i=X_START_RIGHT;
			k=-1;
		}		
		
		/* HORIZONTAL sets of pills */
		
		
		//HORIZONTAL set of pills 1
		
		y=y_i+INTERLINE_WIDTH+1+(PILLS_DISTANCE+PILLS_SIZE)*1-1;
		x=x_i+k*(INTERLINE_WIDTH+1+(PILLS_DISTANCE+PILLS_SIZE)*1-1);
		
    generate_set_pills(x,y,k,12,HORIZONTAL);
		
		//HORIZONTAL set of pills 2
		
		x=x_i+k*(INTERLINE_WIDTH+1+(PILLS_DISTANCE+PILLS_SIZE)*1-1);
		y=y_i+INTERLINE_WIDTH+1+(PILLS_DISTANCE+PILLS_SIZE)*5-1;
		
		generate_set_pills(x,y,k,13,HORIZONTAL);
		
		
		//HORIZONTAL set of pills 3
		
		x=x_i+k*(INTERLINE_WIDTH+1+(PILLS_DISTANCE+PILLS_SIZE)*1-1);
		y=y_i+INTERLINE_WIDTH+1+(PILLS_DISTANCE+PILLS_SIZE)*8-1;
		generate_set_pills(x,y,k,5,HORIZONTAL);
				
				
		//HORIZONTAL set of pills 4
		
		x=x_i+k*(INTERLINE_WIDTH+1+(PILLS_DISTANCE+PILLS_SIZE)*(PILLS_DISTANCE+PILLS_SIZE)-1);
		y=y_i+INTERLINE_WIDTH+1+(PILLS_DISTANCE+PILLS_SIZE)*8-1;
		generate_set_pills(x,y,k,3,HORIZONTAL);
		
		//HORIZONTAL set of pills 5
		
		x=x_i+k*(INTERLINE_WIDTH+1+(PILLS_DISTANCE+PILLS_SIZE)*1-1);
		y=y_i+INTERLINE_WIDTH+1+(PILLS_DISTANCE+PILLS_SIZE)*20-1;
		generate_set_pills(x,y,k,12,HORIZONTAL);
		
		//HORIZONTAL set of pills 6
		
		x=x_i+k*(INTERLINE_WIDTH+1+(PILLS_DISTANCE+PILLS_SIZE)*1-1);
		y=y_i+INTERLINE_WIDTH+1+(PILLS_DISTANCE+PILLS_SIZE)*23-1;
		generate_set_pills(x,y,k,3,HORIZONTAL);
		
		//HORIZONTAL set of pills 7
		
		x=x_i+k*(INTERLINE_WIDTH+1+(PILLS_DISTANCE+PILLS_SIZE)*1-1);
		y=y_i+INTERLINE_WIDTH+1+(PILLS_DISTANCE+PILLS_SIZE)*26-1;
		generate_set_pills(x,y,k,6,HORIZONTAL);
		
		//HORIZONTAL set of pills 8
		
		x=x_i+k*(INTERLINE_WIDTH+1+(PILLS_DISTANCE+PILLS_SIZE)*1-1);
		y=y_i+INTERLINE_WIDTH+1+(PILLS_DISTANCE+PILLS_SIZE)*29-1;
		generate_set_pills(x,y,k,13,HORIZONTAL);
		
		//HORIZONTAL set of pills 9 
		
		x=x_i+k*(INTERLINE_WIDTH+1+7*(PILLS_DISTANCE+PILLS_SIZE)-1);
		y=y_i+INTERLINE_WIDTH+1+23*(PILLS_DISTANCE+PILLS_SIZE)-1;
		generate_set_pills(x,y,k,6,HORIZONTAL);
		
		//HORIZONTAL set of pills 10
		
		x=x_i+k*(INTERLINE_WIDTH+1+(PILLS_DISTANCE+PILLS_SIZE)*(PILLS_DISTANCE+PILLS_SIZE)-1);
		y=y_i+INTERLINE_WIDTH+1+(PILLS_DISTANCE+PILLS_SIZE)*26-1;
		generate_set_pills(x,y,k,4,HORIZONTAL);
		
		
		/* VERTICAL sets of pills */
		
		
		
		//VERTICAL set of pills 1
		
		x=x_i+k*(INTERLINE_WIDTH+1+(PILLS_DISTANCE+PILLS_SIZE)*1-1);
		y=y_i+INTERLINE_WIDTH+1+(PILLS_DISTANCE+PILLS_SIZE)*1-1;
		generate_set_pills(x,y,k,8,VERTICAL);
		
		
		//VERTICAL set of pills 2
		
		x=x_i+k*(INTERLINE_WIDTH+1+(PILLS_DISTANCE+PILLS_SIZE)*6-1);
		y=y_i+INTERLINE_WIDTH+1+(PILLS_DISTANCE+PILLS_SIZE)*1-1;
		generate_set_pills(x,y,k,26,VERTICAL);
		
		
		//VERTICAL set of pills 3
		
		x=x_i+k*(INTERLINE_WIDTH+1+(PILLS_DISTANCE+PILLS_SIZE)*12-1);
		y=y_i+INTERLINE_WIDTH+1+(PILLS_DISTANCE+PILLS_SIZE)*1-1;
		generate_set_pills(x,y,k,4,VERTICAL);
		
		//VERTICAL set of pills 4
		
		x=x_i+k*(INTERLINE_WIDTH+1+(PILLS_DISTANCE+PILLS_SIZE)*(PILLS_DISTANCE+PILLS_SIZE)-1);
		y=y_i+INTERLINE_WIDTH+1+(PILLS_DISTANCE+PILLS_SIZE)*5-1;
		generate_set_pills(x,y,k,4,VERTICAL);
		
		//VERTICAL set of pills 5
		
		x=x_i+k*(INTERLINE_WIDTH+1+(PILLS_DISTANCE+PILLS_SIZE)*1-1);
		y=y_i+INTERLINE_WIDTH+1+(PILLS_DISTANCE+PILLS_SIZE)*20-1;
		generate_set_pills(x,y,k,4,VERTICAL);
		
		//VERTICAL set of pills 6
		
		x=x_i+k*(INTERLINE_WIDTH+1+(PILLS_DISTANCE+PILLS_SIZE)*3-1);
		y=y_i+INTERLINE_WIDTH+1+(PILLS_DISTANCE+PILLS_SIZE)*23-1;
		generate_set_pills(x,y,k,4,VERTICAL);
		
		//VERTICAL set of pills 7
		
		x=x_i+k*(INTERLINE_WIDTH+1+(PILLS_DISTANCE+PILLS_SIZE)*1-1);
		y=y_i+INTERLINE_WIDTH+1+(PILLS_DISTANCE+PILLS_SIZE)*26-1;
		generate_set_pills(x,y,k,4,VERTICAL);
				
		//VERTICAL set of pills 8
		
		x=x_i+k*(INTERLINE_WIDTH+1+(PILLS_DISTANCE+PILLS_SIZE)*12-1);
		y=y_i+INTERLINE_WIDTH+1+(PILLS_DISTANCE+PILLS_SIZE)*21-1;
		generate_set_pills(x,y,k,3,VERTICAL);
		
		//VERTICAL set of pills 9
		
		x=x_i+k*(INTERLINE_WIDTH+1+(PILLS_DISTANCE+PILLS_SIZE)*(PILLS_DISTANCE+PILLS_SIZE)-1);
		y=y_i+INTERLINE_WIDTH+1+(PILLS_DISTANCE+PILLS_SIZE)*23-1;
		generate_set_pills(x,y,k,3,VERTICAL);
		
		//VERTICAL set of pills 10 
		
		x=x_i+k*(INTERLINE_WIDTH+1+(PILLS_DISTANCE+PILLS_SIZE)*12-1);
		y=y_i+INTERLINE_WIDTH+1+(PILLS_DISTANCE+PILLS_SIZE)*26-1;
		generate_set_pills(x,y,k,3,VERTICAL);
		
		}	
	
}


void display_pill(int row, int col, Object_TypeDef type){
	
	int x,y,j;
	int x1,x2,y1,k;
	
	if (row == -1 || col == -1)
		return;
	
	y = get_y_coordinate_from_row(row);
	x = get_x_coordinate_from_col(col);
	
	if (type == STD_PILL){
		LCD_SetPoint(x,y,White);		
		for (j=0; j<8;j++)
			LCD_SetPoint(x+x_coordinates[j],y+y_coordinates[j],White);
	}
	else if (type == PWR_PILL){
	
		for (j=0;j<2;j++){
			
			if(j==0) k=1;
			else k=-1;
			
			y1=y;
			x1=x-3;
			x2=x+3;
			LCD_DrawLine(x1,y1,x2,y1,White);
			
			y1+=k;
			LCD_DrawLine(x1,y1,x2,y1,White);
			
			y1+=k;
			x1+=1;
			x2-=1;
			LCD_DrawLine(x1,y1,x2,y1,White);
			
			y1+=k;
			x1+=1;
			x2-=1;
			LCD_DrawLine(x1,y1,x2,y1,White);			
		}
	}
	else if (type == NOT_PWR_PILL){
		
		x1=x-CORRIDOR_WIDTH/2;
		x2=x+CORRIDOR_WIDTH/2;
		y1=y-CORRIDOR_WIDTH/2;
		for(j=0;j<CORRIDOR_WIDTH;j++)
			LCD_DrawLine(x1,y1+j,x2,y1+j,Black);
	}
}


void generate_set_pills(int x, int y, int k, int n_pills, Orientation_TypeDef orientation){
	
	int i;
	
	if (orientation == HORIZONTAL) {
		
		for (i=0;i<n_pills;i++){

			//display_std_pill(x,y);
			map_std_pill_to_matrix(x,y,labyrinth_mat);
			x+=k*(PILLS_DISTANCE+PILLS_SIZE);
		}
	}
	else{

		for (i=0;i<n_pills;i++){

			//display_std_pill(x,y);
			map_std_pill_to_matrix(x,y,labyrinth_mat);
			y+=PILLS_DISTANCE+PILLS_SIZE;
		}	
	}	
}

void display_pills(Object_TypeDef type){
	
	int i,j;
	
	if(type==PWR_PILL){
		for(i=0;i<ROWS;i++)
			for(j=0;j<COLS;j++){
				if(labyrinth_mat[i][j] == PWR_PILL)
					display_pill(i,j,PWR_PILL);
			}
	}
}

