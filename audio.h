/*
 * audio.h
 *
 *	Created: 2014-01-18
 *		Author: Brittaney Geisler, Isaac Cheng, Kelvin Au, Kevin Hui
 */

#ifndef AUDIO_FUNCTIONS
#define AUDIO_FUNCTIONS

#include <stdio.h>
#include <stdlib.h>
#include "Altera_UP_SD_Card_Avalon_Interface.h"
#include "sys/alt_irq.h"
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

void av_config_setup();
void open_sd(void);
void write_fifo(void* context, unsigned int id);
int fill_buff(short int fileHandle, aud_buf *ab);
void init_audio_buff(aud_buf* ab);
int offset(short int fileHandle, aud_buf *ab);
void loop_audio(int, char*, aud_buf*);
int audio(char*);

#endif
