/*
 * audio.c
 *
 *	Created: 2014-01-18
 *		Author: Brittaney Geisler, Isaac Cheng, Kelvin Au, Kevin Hui
 */

#include "audio.h"
#include "sd_card.h"

int audio(void) {
	aud_buf ab;
	short int file_handle;
	char *fname = "clip.wav";

	alt_up_sd_card_dev *device_reference = NULL;
	device_reference = alt_up_sd_card_open_dev(SD_CARD_NAME);

	file_handle = open_sd(fname);

	printf("Start\n");

	av_config_setup();
	init_audio_buff(&ab);

	ab.audio = alt_up_audio_open_dev(AUDIO_0_NAME);
	assert(ab.audio);

	printf("Wipe audio FIFO\n");
	alt_up_audio_reset_audio_core(ab.audio);
	if(device_reference != NULL){
		offset(file_handle, &ab);
	}
	else
		return 0;

	while(1){
		fill_buff(file_handle, &ab);
		write_fifo(&ab);
	}


	printf("\nClose SD\n");
	alt_up_sd_card_fclose(file_handle);

	return 1;
}



void av_config_setup(){
	alt_up_av_config_dev * av_config = alt_up_av_config_open_dev(AUDIO_AND_VIDEO_CONFIG_0_NAME);
	//assert(av_config);
	while (!alt_up_av_config_read_ready(av_config)) {
	}
}

void init_audio_buff(aud_buf* ab) {
	ab->start = 0;
	ab->end = 1;
}

short int open_sd(char *fname){
	short int fileHandle;
	if (alt_up_sd_card_is_Present()) {
		printf("Card connected. \n");
		printf("fat16: %d",alt_up_sd_card_is_FAT16());
		if (alt_up_sd_card_is_FAT16()) {
			printf("FAT16 file system detected. \n");
		} else {
			printf("Unknown file system. \n");
		}
	}

	fileHandle = alt_up_sd_card_fopen(fname, 0);
	printf("fileHandle: %i\n", fileHandle);

	return fileHandle;
}

int offset(short int fileHandle, aud_buf *ab){
	int offset;
	for (offset = 0; offset < 44; offset++){
		ab->buf[0] = alt_up_sd_card_read(fileHandle);
		//printf("|%i:%.2x| ",offset+1, ab->buf[0]);
	}
	return 1;
}

int fill_buff(short int fileHandle, aud_buf *ab){
	int start, end, i, audio_size;
	char a;
	char b;

	//printf("Fill buff\n");

	start = ab->start;
	end = ab->end;

	audio_size = start > end ? start - end : start + MAX_BUFFER_SIZE - end;
	audio_size--;

	for (i = 0; i < audio_size; i++) {
		a = alt_up_sd_card_read(fileHandle);
		b = alt_up_sd_card_read(fileHandle);
		//printf("|a = %.2x, b = %.2x |", a, b);
		ab->buf[end++] = (((unsigned char)b<<8)|(unsigned char)a);
		//printf("a.buf[end]:%i| ", ab->buf[end]);
		if( end == MAX_BUFFER_SIZE ) end = 0; //reached end of buffer
	}

	ab->end = end;
	return 1;
}

void write_fifo(aud_buf *ab){
	//printf("Write FIFO\n");
	int start = ab->start;
	int end = ab->end;

	while (1) {
		int space = alt_up_audio_write_fifo_space(ab->audio, ALT_UP_AUDIO_LEFT);
		//printf("Space:%d\n", space);
		if (space >= 96)
			break;
	}
	alt_up_audio_write_fifo(ab->audio, ab->buf + start, 96, ALT_UP_AUDIO_LEFT);
	alt_up_audio_write_fifo(ab->audio, ab->buf + start, 96, ALT_UP_AUDIO_RIGHT);

	start += 96;
	if( start > end ){ start = 0;}

	ab->start = start;
}
