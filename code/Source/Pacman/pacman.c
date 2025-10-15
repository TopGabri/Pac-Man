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

#include "LPC17xx.h"
#include "pacman.h"
#include "mapping.h"
#include "labyrinth.h"
#include "pills.h"
#include "ghost.h"
#include "GLCD/GLCD.h" 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


extern CHR_TypeDef *PCMN;

void clear_pacman(int x, int y){
	
	
	int x1,x2,y1;
	 
	int i,k;
	
	x1 = x - PCMN_SIZE_PX/2;
	if (x1<0) x1=0;
	x2 = x + PCMN_SIZE_PX/2;
	
	for (i=y-PCMN_SIZE_PX/2;i<=y+PCMN_SIZE_PX/2;i++)
		LCD_DrawLine(x1,i,x2,i,Black);

}

void display_pacman(int row, int col, int row_old, int col_old){
	 
	
	int x_old, y_old;
	int x = get_x_coordinate_from_col(col);
	int y = get_y_coordinate_from_row(row);
	
	//clear old pacman
	if (row_old != -1 && col_old != -1){
		x_old = get_x_coordinate_from_col(col_old);
		y_old = get_y_coordinate_from_row(row_old);
		clear_pacman(x_old, y_old);
	}

	draw_pacman(x,y,PCMN->direction);	
	
	PCMN->col_old = PCMN->col;
	PCMN->row_old = PCMN->row;
}


void draw_pacman(int x, int y,Direction_TypeDef direction){
	
	int x1,x2,y1;

	int i,k;
	 
	 
	x1=x-(PCMN_SIZE_PX/2-1);
	if(x1<0) x1=0;
	x2=x+(PCMN_SIZE_PX/2-1);
	y1=y;


	/* start from middle and draw lines downwards and then upwards */ 

	LCD_DrawLine(x1,y1,x2,y1,Yellow);


	for (i=0;i<2;i++){
	 
	 if(i==0) k=1;
	 else k=-1;
	 
	 x1=x-6;
	 if (x1 < 0) x1 = 0;
	 x2=x+6;
	 y1=y+k;
	 LCD_DrawLine(x1,y1,x2,y1,Yellow);
	 
	 y1+=k;
	 LCD_DrawLine(x1,y1,x2,y1,Yellow);
	 
	 x1+=1;
	 x2-=1;
	 y1+=k;
	 LCD_DrawLine(x1,y1,x2,y1,Yellow);
	 
	 y1+=k;
	 LCD_DrawLine(x1,y1,x2,y1,Yellow);
	 
	 x1+=1;
	 x2-=1;
	 y1+=k;
	 LCD_DrawLine(x1,y1,x2,y1,Yellow);
	 
	 x1+=2;
	 x2-=2;
	 y1+=k;
	 LCD_DrawLine(x1,y1,x2,y1,Yellow);
	}
	
	draw_mouth(x,y,direction);
}


void draw_mouth(int x, int y,Direction_TypeDef direction){
	
		int x1,x2,y1,y2,i,k;
	
		switch (direction){
			
			case UP:
				x1=x;
				y1=y-PCMN_SIZE_PX/2;
				y2=y+1;
			
				LCD_DrawLine(x1,y1,x1,y2,Black);
			
				for(i=0;i<2;i++){
					if(i==0) k=1;
					else k=-1;
					
					x1=x+k;
					y1=y-PCMN_SIZE_PX/2;
					y2=y+1;
					LCD_DrawLine(x1,y1,x1,y2,Black);
					
					x1+=k;
					y2-=2;
					LCD_DrawLine(x1,y1,x1,y2,Black);
					
					x1+=k;
					y2-=2;
					LCD_DrawLine(x1,y1,x1,y2,Black);
				}				
				break;
				
			
			case DOWN:
				x1=x;
				y1=y-1;
				y2=y+PCMN_SIZE_PX/2;
			
				LCD_DrawLine(x1,y1,x1,y2,Black);
			
				for(i=0;i<2;i++){
					if(i==0) k=1;
					else k=-1;
					
					x1=x+k;
					y1=y-1;
					y2=y+PCMN_SIZE_PX/2;
					LCD_DrawLine(x1,y1,x1,y2,Black);
					
					x1+=k;
					y1+=2;
					LCD_DrawLine(x1,y1,x1,y2,Black);
					
					x1+=k;
					y1+=2;
					LCD_DrawLine(x1,y1,x1,y2,Black);
				}
				break;
				
			
			case LEFT:
				
				x1=x-PCMN_SIZE_PX/2;
				x2=x+1;
				y1=y;
	
				LCD_DrawLine(x1,y1,x2,y1,Black);
			
				for(i=0;i<2;i++){
					if(i==0) k=1;
					else k=-1;
					
					y1=y+k;
					x1=x-PCMN_SIZE_PX/2;
					x2=x+1;
					LCD_DrawLine(x1,y1,x2,y1,Black);
					
					y1+=k;
					x2-=2;
					LCD_DrawLine(x1,y1,x2,y1,Black);
					
					y1+=k;
					x2-=2;
					LCD_DrawLine(x1,y1,x2,y1,Black);
				}
				
				break;				
				
			case RIGHT:
				x1=x-1;
				x2=x+PCMN_SIZE_PX/2;
				y1=y;
	
				LCD_DrawLine(x1,y1,x2,y1,Black);
			
				for(i=0;i<2;i++){
					if(i==0) k=1;
					else k=-1;
					
					y1=y+k;
					x1=x-1;
					x2=x+PCMN_SIZE_PX/2;
					LCD_DrawLine(x1,y1,x2,y1,Black);
					
					y1+=k;
					x1+=2;
					LCD_DrawLine(x1,y1,x2,y1,Black);
					
					y1+=k;
					x1+=2;
					LCD_DrawLine(x1,y1,x2,y1,Black);
				}
				break;	
			
			default:
				break;
		}	
}
