/*
 * sd_card.c
 *
 *	Created: 2014-01-18
 *		Author: Brittaney Geisler, Isaac Cheng, Kelvin Au, Kevin Hui
 */

#include "sd_card.h"

/*void printSD() {
 alt_up_sd_card_dev *device_reference = NULL;
 int connected = 0;
 char* fileName;
 device_reference = alt_up_sd_card_open_dev(SD_CARD_NAME);
 if (device_reference != NULL) {
 while (1) {
 if ((connected == 0) && (alt_up_sd_card_is_Present())) {
 printf("Card connected. \n");
 printf("fat16: %d", alt_up_sd_card_is_FAT16());
 if (alt_up_sd_card_is_FAT16()) {
 printf("FAT16 file system detected. \n");

 if (alt_up_sd_card_find_first("", fileName) == 0) {
 printf("Files detected: \n");
 do {
 printf("%s \n", fileName);
 } while (alt_up_sd_card_find_next(fileName) == 0);
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
 }*/
void initSD() {
	int connected = 0;
	alt_up_sd_card_dev *device_reference = NULL;
	device_reference = alt_up_sd_card_open_dev(SD_CARD_NAME);
	if (device_reference != NULL) {

		if ((connected == 0) && (alt_up_sd_card_is_Present())) {
			//printf("Card connected. \n");
			//printf("fat16: %d",alt_up_sd_card_is_FAT16());
			if (alt_up_sd_card_is_FAT16())
				; //printf("FAT16 file system detected. \n");
			else
				printf("Unknown file system. \n");
			connected = 1;
		} else if ((connected == 1) && (alt_up_sd_card_is_Present() == false)) {
			printf("Card disconnected. \n");
			connected = 0;
		}
	}
}

void printSD() {
	char* fileName;
	if (alt_up_sd_card_is_Present() && alt_up_sd_card_is_FAT16()) {

		if (alt_up_sd_card_find_first("", fileName) == 0) {
			printf("Files detected: \n");
			do {
				printf("%s \n", fileName);
			} while (alt_up_sd_card_find_next(fileName) == 0);
		} else if (alt_up_sd_card_find_first("", fileName) == -1)
			printf("No files. \n");
	}

}

void writeSD(char name[], int score) {
	short int handler = alt_up_sd_card_fopen(SCORE_NAME, true);
	int index = 0;
	char score_str[4];
	if (handler == -1) {
		handler = alt_up_sd_card_fopen(SCORE_NAME, false);
		setPositionToEnd(handler);
	}

	if (handler >= 0) {
		while (name[index] != '\0') {
			alt_up_sd_card_write(handler, name[index]);
			index++;
		}
		alt_up_sd_card_write(handler, 0x2F); // slash
		index = 0;

		convertInt(score_str, score);

		while (score_str[index] != '\0') {
			alt_up_sd_card_write(handler, score_str[index]);
			index++;
		}
		//alt_up_sd_card_write(handler, 0x20); // double_space
		//alt_up_sd_card_write(handler, 0x20);
		//alt_up_sd_card_write(handler, 0x00); //  null
		alt_up_sd_card_fclose(handler);
	} else {
		//printf("%c",name_score[0][0][index]);
		printf("Handler:%d\n", handler);
		printf("Cannot write the score. \n");
	}

}

void setPositionToEnd(short int handler) {
	int position = alt_up_sd_card_read(handler);
	//int numOfChar = 0;
	//int count = 0;
	while (position >= 0) {
		//numOfChar++;
		//printf("%c",position);
		position = alt_up_sd_card_read(handler);
		/*printf("%d",numOfChar);
		 printf("%c",position);*/
	}
	/*
	 alt_up_sd_card_fclose(handler);
	 handler = alt_up_sd_card_fopen(SCORE_NAME, false);
	 position = alt_up_sd_card_read(handler);
	 while (count < numOfChar){
	 alt_up_sd_card_read(handler);
	 count++;
	 }*/
}

int getAllScore(score list[]) {
	short int handler = alt_up_sd_card_fopen(SCORE_NAME, false);
	if (handler == -1)
		return -1;
	int i = 0, j = 0; // j = index of players
	char word = alt_up_sd_card_read(handler);

	while ((int) word >= 0) {
		//slash - save the score
		if ((int) word == 0x2F) {
			for (i = 0; i < MAX_CHARACTER_OF_SCORE; i++) {
				word = alt_up_sd_card_read(handler);
				list[j].score[i] = word;
			}
			list[j].score[i] = '\0';
			//word = alt_up_sd_card_read(handler);
			//word = alt_up_sd_card_read(handler);
			word = alt_up_sd_card_read(handler);
			if (!(list[j].name[0]=='\0'||list[j].score[0]=='\0'))
				j++; // move to next player
			i = 0;
		}
		// otherwise, save the name
		else {
			list[j].name[i] = word;
			word = alt_up_sd_card_read(handler);
			i++;
			if ((int) word == 0x2F)
				list[j].name[i] = '\0';
			/*
			 }

			 //printf("j: %d",j);
			 if (list[j].name == NULL){
			 list[j].name[0] = word;
			 list[j].name[1] = '\0';
			 }
			 else
			 appendCharacter(list[j].name,word);
			 //printf("name:%s\n",list[j].name);
			 word = alt_up_sd_card_read(handler);*/
		}

	}
	// Indicate the end of list
	alt_up_sd_card_fclose(handler);
	list[j].name[0] = '\0';

	return 0;
}

void appendCharacter(char* s, char c) {
	size_t len = strlen(s);
	s[len] = c;
	s[len + 1] = '\0';
}

void getMax10Score(score list[], score max_score[]) {
	int i, j, k;
	score tmp_arr[SCORE_BUFFER_SIZE];
	score tmp;

	for (i = 0; list[i].name[0] != '\0'; i++) {
		//printf("player:%s score:%s\n",list[1].name,list[1].score);
		tmp_arr[i] = list[i];
	}
	//printf("i:%s score:%s\n",list[1].name,list[1].score);
	//printf("i:%s score:%s\n",tmp_arr[2].name,tmp_arr[2].score);
	tmp_arr[i].name[0] = '\0';
	//printf("i:%s score:%s\n",tmp_arr[2].name,tmp_arr[2].score);
	//printf("i:%s score:%s\n",list[1].name,list[1].score);
	/*for (i = 0 ; list[i].name[0] != '\0'; i++){
	 printf("player:%s score:%s\n",list[1].name,list[1].score);
	 }*/
	/*
	 for (i = 0; tmp_arr[i].name[0] != '\0' ; i++){
	 printf("yes\n");
	 printf("player:%s\n",tmp_arr[1].name);
	 printf("score:%s\n",tmp_arr[1].score);
	 }
	 *///printf("i:%s score:%s\n",tmp_arr[1].name,tmp_arr[1].score);

	for (j = 0; j < i - 1; j++) {
		for (k = j + 1; k < i; k++) {
			if (atoi(tmp_arr[j].score) < atoi(tmp_arr[k].score)) {
				tmp = tmp_arr[j];
				tmp_arr[j] = tmp_arr[k];
				tmp_arr[k] = tmp;
			}
		}
	}
	//printf("i:%s score:%s\n",tmp_arr[1].name,tmp_arr[1].score);

	for (i = 0; i < 10 && tmp_arr[i].name[0] != '\0'; i++)
		max_score[i] = tmp_arr[i];
	max_score[i].name[0] = '\0';
}

int getPersonalScore(score list[], int player_score[], char* name) {
	int i, j = 0;
	int tmp[SCORE_BUFFER_SIZE];
	for (i = 0; list[i].name[0] != '\0'; i++) {
		if (strcmp(list[i].name, name) == 0) {
			tmp[j] = atoi(list[i].score);
			j++;
		}
	}
	if (j == 0){
		player_score[j] = -1;
		return -1;
	}
	qsort(tmp, j, sizeof(int), cmp_func);
	for (i = 0; i < 10 && i < j; i++)
		player_score[i] = tmp[i];
	player_score[i] = -1;
	return 1;
}

int cmp_func(const void *a, const void *b) {
	int *x = (int *) a;
	int *y = (int *) b;
	return *y - *x;
}

void convertInt(char score_str[], int score) {
	char string_2[2];
	char string_3[3];
	if (score < 10) {
		sprintf(string_2, "%d", score);
		score_str[0] = '0';
		score_str[1] = '0';
		score_str[2] = string_2[0];
	} else if (score >= 10 && score < 100) {
		sprintf(string_3, "%d", score);
		score_str[0] = '0';
		score_str[1] = string_3[0];
		score_str[2] = string_3[1];
	} else
		sprintf(score_str, "%d", score);
	score_str[3] = '\0';
}
