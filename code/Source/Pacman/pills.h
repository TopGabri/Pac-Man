#ifndef __PILLS_H
#define __PILLS_H

#include "game.h"

typedef enum {
	HORIZONTAL,
	VERTICAL
} Orientation_TypeDef;

#define PILLS_DISTANCE 6
#define PILLS_SIZE 3

void generate_pills();
void display_pill(int row, int col, Object_TypeDef type);
void generate_set_pills(int x, int y, int k, int n_pills, Orientation_TypeDef orientation);
void display_pills(Object_TypeDef type);


#endif