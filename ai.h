/*
 * ai.h
 *
 *	Created: 2014-01-18
 *		Author: Brittaney Geisler, Isaac Cheng, Kelvin Au, Kevin Hui
 */

#ifndef AI_FUNCTIONS
#define AI_FUNCTIONS

#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#include "values.h"
#include "player.h"
#include "screen.h"

extern struct player p[3];
extern int numPlayers;
extern int turn;
int peaks[2];

void aiMain(int);
int findClosest(void);
int pythag(int);
int findPeak(int);
void testFire(int);
int targetDir(int);
int aiFire(int, int, int);
void aiMove(int);
int bPythag(int, int, int);

#endif
