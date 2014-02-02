/*
 * field.c
 *
 *	Created: 2014-01-27
 *		Author: Brittaney Geisler, Isaac Cheng, Kelvin Au, Kevin Hui
 */

#include "field.h"

//fill col or row first????
//Initialises the field not sure why i have this seperate from generate field
//But i remember i had a reason
void initField() {
	generateField();
}

//TODO: Make a field generator
//Generates a field
void generateField() {
	int i,j,flag;

	for(i = 0; i < HYRULE_WIDTH ; i++){
		flag = 0;
		for(j = 0; j < HYRULE_HEIGHT ; j++){
			//Using white as a mask
			if (flag == 1){
				map[j][i] = hyrule[j][i];
			}
			else{
			map[j][i] = NOTHING;
			}
			if (hyrule[j][i] != 0xFFFF && flag == 0){
				field[i] = j-2;
				map[j-1][i] = NOTHING;
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

