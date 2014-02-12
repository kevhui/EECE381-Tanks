/*
 * audio.c
 *
 *	Created: 2014-01-18
 *		Author: Brittaney Geisler, Isaac Cheng, Kelvin Au, Kevin Hui
 */

#include "audio.h"

void av_config_setup(){
	alt_up_av_config_dev * av_config = alt_up_av_config_open_dev(AUDIO_AND_VIDEO_CONFIG_0_NAME);
	while (!alt_up_av_config_read_ready(av_config)) {
	}
}

void init_audio_buff(aud_buf* ab) {
	ab->start = 0;
	ab->end = 1;
}

void open_sd(void){
	if (alt_up_sd_card_is_Present()) {
		printf("Card connected. \n");
		printf("fat16: %d",alt_up_sd_card_is_FAT16());
		if (alt_up_sd_card_is_FAT16()) {
			printf("FAT16 file system detected. \n");
		} else {
			printf("Unknown file system. \n");
		}
	}
}

int offset(short int fileHandle, aud_buf *ab){
	int offset;
	for (offset = 0; offset < 44; offset++){
		ab->buf[0] = alt_up_sd_card_read(fileHandle);
		printf("|%i:%.2x| ",offset+1, ab->buf[0]);
	}
	return 1;
}

int fill_buff(short int fileHandle, aud_buf *ab){
	int start, end, i;
	short int a = 0;
	short int b = 0;

	//printf("Fill buff\n");

	start = ab->start;
	end = ab->end;

	for (i = 0; i < 960; i++) {
		a = alt_up_sd_card_read(fileHandle);
		if(a < 0){
//			//printf("|a = %i, b = %i |", a, b);
//			printf("|a = %i|", a);
			return 0;
		}
		b = alt_up_sd_card_read(fileHandle);

		//printf("|a = %.2x, b = %.2x |", a, b);
		ab->buf[end++] = (unsigned int)((b<<8)|a);
		//printf("a.buf[end]:%i| ", ab->buf[end]);
		if( end == MAX_BUFFER_SIZE ) end = 0; //reached end of buffer
	}

	ab->end = end;
	return 1;
}

void write_fifo(void* context, unsigned int id){
	//printf("Write FIFO\n");
	aud_buf *ab = *(aud_buf**)context;
	int start = ab->start;

	while (1) {
		int space = alt_up_audio_write_fifo_space(ab->audio, ALT_UP_AUDIO_LEFT);
		//printf("Space:%d\n", space);
		if (space >= 96)
			break;
	}
	alt_up_audio_write_fifo(ab->audio, (unsigned int*) ab->buf + start, 96, ALT_UP_AUDIO_LEFT);
	alt_up_audio_write_fifo(ab->audio, (unsigned int*) ab->buf + start, 96, ALT_UP_AUDIO_RIGHT);

	start += 96;
	if( start == MAX_BUFFER_SIZE ){ start = 0;}

	ab->start = start;
}

void loop_audio(int fileHandle, char* fname, aud_buf *ab){
	if(fill_buff(fileHandle, ab) == 0){
		printf("\nClose file\n");
		alt_up_sd_card_fclose(fileHandle);

		printf("\nOpen File SD\n");
		fileHandle = alt_up_sd_card_fopen(fname, 0);
		offset(fileHandle, ab);
	}
}
