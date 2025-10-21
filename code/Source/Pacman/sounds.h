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
** File name:           sounds.h
** Last modified Date:  
** Last Version:        V1.00
** Descriptions:        Prototypes of functions, constants and data types included in sounds.c file
** Correlated files:    sounds.c, music/music.h
**-------------------------------------------------------------------------------------------------------------------
********************************************************************************************************************/


#ifndef __SOUNDS_H
#define __SOUNDS_H

#include "music/music.h"


NOTE francesco_totti[] = 
{
    // 1
		{e4, time_minima},
		{g4, time_minima},
		{d4, time_semiminima},
		{d4, time_semiminima},
		{c4, time_semiminima},
		{g3, time_semiminima},
		{e4, time_minima},
		{g4, time_minima},
		{b3, time_semiminima},
		{b3, time_semiminima},
		{c4, time_semiminima},
		{g3, time_semiminima},
		{e4, time_minima},
		{g4, time_minima},
		{d4, time_semiminima},
		{d4, time_semiminima},
		{c4, time_semiminima},
		{pause, time_semiminima},
		{e4, time_minima},
		{g4, time_minima},
		{c4, time_semiminima},
		{b3, time_semiminima},
		{c4, time_semiminima},
		{pause,time_minima}
};
	
NOTE power_up[] =
{
	
	{e3, time_biscroma},
	{g3, time_biscroma},
	{e4, time_biscroma},
	{c4, time_biscroma},
	{d4, time_biscroma},
	{g4, time_biscroma}

}	;

NOTE blue[] = 
{
	/*
	//0
	{a4,time_semiminima},
	//1
	{b4b,time_croma},
	{d4,time_croma},
	{g4,time_croma},
	{b4b,time_croma},
	{c5,time_croma},
	{f4,time_croma},
	{a4,time_croma},
	{b4b,time_croma},
	//2
	{b4b,time_croma},
	{g4,time_croma},
	{b4b,time_croma},
	{d5,time_croma},
	{e5b,time_semiminima},
	{d5,time_croma},
	{c5,time_croma},
	//3
	{b4b,time_croma},
	{d4,time_croma},
	{g4,time_croma},
	{b4b,time_croma},
	{c5,time_croma},
	{f4,time_croma},
	{a4,time_croma},
	{b4b,time_croma},
	//4
	{b4b,time_croma},
	{g4,time_croma},
	{b4b,time_croma},
	{d5,time_croma},
	{e5b,time_semiminima},
	{d5,time_croma},
	{c5,time_croma},
	//5
	{b4b,time_croma},
	{d4,time_croma},
	{g4,time_croma},
	{b4b,time_croma},
	{c5,time_croma},
	{f4,time_croma},
	{a4,time_croma},
	{b4b,time_croma},
	//6
	{b4b,time_croma},
	{g4,time_croma},
	{b4b,time_croma},
	{d5,time_croma},
	{e5b,time_semiminima},
	{d5,time_croma},
	{c5,time_croma},
	//7
	{b4b,time_croma},
	{d4,time_croma},
	{g4,time_croma},
	{b4b,time_croma},
	{a4,time_croma},
	{c4,time_croma},
	{f4,time_croma},
	{g4,time_croma},
	//8
	{g4,time_semiminima},
	{f4,time_croma},
	{g4,time_semiminima},
	{pause,time_croma},
	*/
	{a4,time_semiminima},
	//9
	{b4b,time_semiminima},
	{g4,time_croma},
	{b4b,time_croma},
	{c5,time_croma},
	{c5,time_croma},
	{a4,time_croma},
	//{b4b,time_croma},
	//10
	{b4b,time_semiminima},
	{c5,time_croma},
	{d5,time_croma},
	{e5b,time_croma},
	{e5b,time_croma},
	{d5,time_croma},
	{c5,time_croma},
	//11
	{b4b,time_semiminima},
	{g4,time_croma},
	{b4b,time_croma},
	{c5,time_croma},
	{c5,time_croma},
	{a4,time_croma},
	//{b4b,time_croma},
	//12
	{b4b,time_semiminima},
	{c5,time_croma},
	{d5,time_croma},
	{e5b,time_semiminima},
	{d5,time_croma},
	{c5,time_croma},
	//13
	{b4b,time_semiminima},
	{g4,time_croma},
	{b4b,time_croma},
	{c5,time_croma},
	{c5,time_croma},
	{a4,time_croma},
	//{pause,time_croma},
	//14
	{b4b,time_semiminima},
	{g4,time_croma},
	{g4,time_croma},
	{g4,time_croma},
	{a4,time_croma},
	{g4,time_croma},
	{a4,time_croma},
	//15
	{b4b,time_semiminima},
	{a4,time_croma},
	{g4,time_croma},
	{d4,time_croma},
	{d4,time_croma},
	{a4,time_croma},
	{a4,time_croma},
	//16
	{g4,time_minima}
	
};


NOTE titanic[] = 
{
	{f4,time_minima},
	{f4,time_croma},
	{f4,time_semiminima},
	{f4,time_semiminima},
	{e4,time_semiminima},
	{f4,time_minima},
	{f4,time_semiminima},
	{e4,time_semiminima},
	{f4,time_minima},
	{g4,time_semiminima},
	{a4,time_minima},
	{g4,time_minima}
};


NOTE chase1[] = {
	{a4b,time_semicroma},
	{pause, time_semicroma},
	{a4b,time_semicroma},
	{pause, time_semicroma},
	{a4b,time_semicroma},
	{pause, time_semicroma},
	{a4b,time_semicroma},
	{pause, time_semicroma},
	{a4,time_semicroma},
	{pause,time_semicroma},
	{a4,time_semicroma},
	{pause,time_semicroma},
	{a4,time_semicroma},
	{pause,time_semicroma},
	{a4,time_semicroma},
	{pause,time_semicroma},	
};

NOTE chase2[] = {
	{a4b,time_biscroma},
	{pause, time_biscroma},
	{a4b,time_biscroma},
	{pause, time_biscroma},
	{a4b,time_biscroma},
	{pause, time_biscroma},
	{a4b,time_biscroma},
	{pause, time_biscroma},
	{a4,time_biscroma},
	{pause,time_biscroma},
	{a4,time_biscroma},
	{pause,time_biscroma},
	{a4,time_biscroma},
	{pause,time_biscroma},
	{a4,time_biscroma},
	{pause,time_biscroma},	
};


NOTE chase3[] = {
	{a4b,time_semibiscroma},
	{pause, time_semibiscroma},
	{a4b,time_semibiscroma},
	{pause, time_semibiscroma},
	{a4b,time_semibiscroma},
	{pause, time_semibiscroma},
	{a4b,time_semibiscroma},
	{pause, time_semibiscroma},
	{a4,time_semibiscroma},
	{pause,time_semibiscroma},
	{a4,time_semibiscroma},
	{pause,time_semibiscroma},
	{a4,time_semibiscroma},
	{pause,time_semibiscroma},
	{a4,time_semibiscroma},
	{pause,time_semibiscroma},	
};

		
			
		


#endif 