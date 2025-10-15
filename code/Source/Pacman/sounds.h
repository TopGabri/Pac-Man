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
** Descriptions:        Prototypes of functions included in sounds.c file
** Correlated files:    sounds.c
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
    // 1
    {g4, time_croma},
    {a4, time_croma},
    {b4, time_croma},
    {g4, time_croma},
    {pause, time_semicroma},
    {g4, time_semicroma},
    {a4, time_semicroma},
    {b4, time_semicroma},
    {g4, time_croma},
    // 2
    {f4, time_croma},
    {e4, time_croma},
    {f4, time_croma},
    {d4, time_croma},
    {pause, time_semicroma},
    {d4, time_semicroma},
    {e4, time_semicroma},
    {f4, time_semicroma},
    {d4, time_croma},
    // 3
    {g4, time_croma},
    {a4, time_croma},
    {b4, time_croma},
    {g4, time_croma},
    {pause, time_semicroma},
    {g4, time_semicroma},
    {a4, time_semicroma},
    {b4, time_semicroma},
    {g4, time_croma},
    // 4
    {f4, time_croma},
    {e4, time_croma},
    {f4, time_croma},
    {d4, time_croma},
    {pause, time_semicroma},
    {d4, time_semicroma},
    {e4, time_semicroma},
    {f4, time_semicroma},
    {d4, time_croma},
};

		
		
		


#endif 