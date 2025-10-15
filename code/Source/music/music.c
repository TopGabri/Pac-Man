#include "music.h"
#include "timer/timer.h"
#include "LPC17xx.h"

volatile Bool is_note_playing = FALSE;

void playNote(NOTE note)
{
	is_note_playing = TRUE;
	
	if(note.freq != pause)
	{
		reset_timer(2);
		init_timer(2,0, note.freq);
		enable_timer(2);
	}
	reset_timer(3);
	init_timer(3,0, note.duration);
	enable_timer(3);
}


Bool isNotePlaying(void)
{
	return ((LPC_TIM2->TCR != 0) || (LPC_TIM3->TCR != 0));
	//return is_note_playing;
}