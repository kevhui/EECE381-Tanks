/*
 * audio.h
 *
 *	Created: 2014-01-18
 *		Author: Brittaney Geisler, Isaac Cheng, Kelvin Au, Kevin Hui
 */

#ifndef AUDIO_FUNCTIONS
#define AUDIO_FUNCTIONS

#include <assert.h>
#include <stdio.h>

#include "altera_up_avalon_audio_and_video_config.h"
#include "altera_up_avalon_audio.h"
#include "system.h"

#define MAX_BUFFER_SIZE 960

typedef struct{
	unsigned int buf[MAX_BUFFER_SIZE];

	int start;
	int end;

	alt_up_audio_dev *audio;
} aud_buf;

int audio(void);
void av_config_setup();
short int open_sd(char *fname);
void write_fifo(aud_buf *ab);
int fill_buff(short int fileHandle, aud_buf *ab);
void init_audio_buff(aud_buf* ab);
int offset(short int fileHandle, aud_buf *ab);

#endif
