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
#include <unistd.h>

extern struct player p[2];
extern int numPlayers;
extern int turn;

void initPlayer(int,int,int,int,int,int,int,int,int);
void moveLeft(int);
void moveRight(int);
void turretCW(int);
void turretCCW(int);
void turretFire(int,int);
int getTurretWidth(int);
int getTurretHeight(int);
int getHitPlayer(int,int,int);
int getHitGround(int,int,int);
void bulletExplode(int x, int y,int bulletType);
void checkPlayerFalling(int);

#endif
