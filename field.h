/*
 * field.h
 *
 *	Created: 2014-01-27
 *		Author: Brittaney Geisler, Isaac Cheng, Kelvin Au, Kevin Hui
 */

#ifndef FIELD_DATA
#define FIELD_DATA

#include "screen.h"
#include "values.h"
#include <math.h>

extern int field[SCREEN_WIDTH];

void initField(void);
void generateField(void);
void printField(void);

#endif
