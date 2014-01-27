/*
 * sd_card.c
 *
 *	Created: 2014-01-18
 *		Author: Brittaney Geisler, Isaac Cheng, Kelvin Au, Kevin Hui
 */

#include "sd_card.h"

void printSD(){
	alt_up_sd_card_dev *device_reference = NULL;
	int connected = 0;
	char* fileName;
	device_reference = alt_up_sd_card_open_dev(SD_CARD_NAME);
	if (device_reference != NULL) {
		while (1) {
			if ((connected == 0) && (alt_up_sd_card_is_Present())) {
				printf("Card connected. \n");
				printf("fat16: %d",alt_up_sd_card_is_FAT16());
				if (alt_up_sd_card_is_FAT16()) {
					printf("FAT16 file system detected. \n");

					if(alt_up_sd_card_find_first("",fileName)==0){
						printf("Files detected: \n");
						do{
							printf("%s \n",fileName);
						}while(alt_up_sd_card_find_next(fileName)==0);
					}
				} else {
					printf("Unknown file system. \n");
				}
				connected = 1;
			} else if ((connected == 1) && (alt_up_sd_card_is_Present()
					== false)) {
				printf("Card disconnected. \n");
				connected = 0;
			}
		}
	}
}
