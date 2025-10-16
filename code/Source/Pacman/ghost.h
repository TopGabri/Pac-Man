#ifndef __GHOST_H
#define __GHOST_H

#include <stdint.h>
#include "game.h"
#include "mapping.h"


void display_ghost(int row, int col, int row_old, int col_old, uint16_t Color);
void draw_ghost(int x, int y,Direction_TypeDef direction, uint16_t Color);
void draw_eyes(int x, int y, Direction_TypeDef direction);
void draw_pupils(int x, int y, Direction_TypeDef direction);
int new_row(int row, Direction_TypeDef direction);
int new_col(int col, Direction_TypeDef direction);
Bool opposite_directions(Direction_TypeDef dir1, Direction_TypeDef dir2);
Bool is_valid_direction(int row, int col, Direction_TypeDef dir);
void ghost_movement(int row_target, int col_target);
Bool hit_pacman();

#define GHOST_SIZE_PX 15
#define GHOST_START_ROW 42
#define GHOST_START_COL 39
#define MAX_PATH_LENGTH ROWS+COLS


#endif