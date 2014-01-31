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
	int i = 0;
	for (i = 0; i < SCREEN_WIDTH; i++) {
		field[i] = SCREEN_HEIGHT * 7 / 10;
	}
}

//Prints the field out
void printField() {
	int i = 0;
	for (i = 0; i < SCREEN_WIDTH; i++) {
		printf("%i", field[i]);
	}
}

