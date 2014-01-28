/*
 * player.h
 *
 *	Created: 2014-01-18
 *		Author: Brittaney Geisler, Isaac Cheng, Kelvin Au, Kevin Hui
 */

#ifndef PLAYER_DATA
#define PLAYER_DATA

#include "screen.h"
#include "values.h"
#include <math.h>


extern struct player p[2];
extern int numPlayers;

void initPlayer(int,int,int,int,int,int,int,int,int);
void moveLeft(int);
void moveRight(int);
void turretCW(int);
void turretCCW(int);
void turretFire(int,int);
int getTurretWidth(int);
int getTurretHeight(int);

#endif
