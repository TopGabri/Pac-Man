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
** File name:           game.h
** Last modified Date:  
** Last Version:        V1.00
** Descriptions:        Prototypes of functions, constants and variables included in game.c file
** Correlated files:    game.c
**-------------------------------------------------------------------------------------------------------------------
********************************************************************************************************************/

#ifndef __GAME_H
#define __GAME_H

#include <stdint.h>

typedef enum  __attribute__((packed)){
	SPACE,
	WALL,
	STD_PILL,
	PWR_PILL,
	NOT_PILL,
	NOT_PWR_PILL,
	GATE,
	OUT_OF_BOUNDS
	
} Object_TypeDef;

typedef enum {
	UP,
	DOWN,
	LEFT,
	RIGHT,
	NONE
} Direction_TypeDef;


typedef struct {
	int8_t row;
	int8_t col;	
} Point;

typedef enum {
	CHASE,
	FRIGHTENED
} Mode;


typedef struct {
	uint8_t chase;
	uint8_t frightened;
} Difficulty;

typedef struct {
	int8_t col_old;
	int8_t row_old;
	int8_t col;
	int8_t row;
	Direction_TypeDef direction;
	Direction_TypeDef old_direction;
	uint16_t Color;
	Point old_pill;
	Mode mode;	
} CHR_TypeDef;

typedef char Bool;
#define TRUE 1
#define FALSE 0

#define GAME_TIME 60
#define POWER_PILLS 4
#define RESPAWN_TIME 3
#define NUM_PILLS 240


void pacman();
void restart_after_hit();
void initialize_GHOST();
void initialize_PCMN();
void display_score(uint16_t score);
void display_lives(uint8_t lives);
void display_cntdown_timer(uint8_t timer);
int move(Direction_TypeDef direction);
int hit_wall(Direction_TypeDef direction);
Object_TypeDef hit_pill(Direction_TypeDef direction);
void pacman_dynamics(Direction_TypeDef direction);
Direction_TypeDef opposite_direction(Direction_TypeDef dir);
void send_parameters_CAN(uint16_t score, uint8_t num_lives, uint8_t game_time);




#endif