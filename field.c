/*
 * field.c
 *
 *	Created: 2014-01-27
 *		Author: Brittaney Geisler, Isaac Cheng, Kelvin Au, Kevin Hui
 */

#include "field.h"


//Initialises the field 
void initField() {
	generateField();
}

//Generates a field
void generateField() {
	int i, j, flag;

	for (i = 0; i < SCREEN_WIDTH; i++) {
		//field[i] = SCREEN_HEIGHT * 7 / 10;
		flag = 0;
		for (j = 0; j < SCREEN_HEIGHT; j++) {
			if (flag == 1) {
				if(fd[j][i] == 0xFFFF){
					map[j][i] = NOTHING;
				}
				else{
				map[j][i] = fd[j][i];
				}
			}
			else {
				map[j][i] = NOTHING;
			}
			if (fd[j][i] != 0xFFFF && flag == 0) {
				field[i] = j - 2;
				map[j - 1][i] = NOTHING;
				flag = 1;
			}
		}
	}

}

//Prints the field out
void printField() {
	int i = 0;
	for (i = 0; i < SCREEN_WIDTH; i++) {
		printf("%i", field[i]);
	}
}

