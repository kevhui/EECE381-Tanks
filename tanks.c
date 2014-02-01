/*
 * tanks.c
 * Clone of Tanks using the Altera DE2 Board.
 *
 *	Created: 2014-01-18
 *		Author: Brittaney Geisler, Isaac Cheng, Kelvin Au, Kevin Hui
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <io.h>
#include "sd_card.h"
#include "screen.h"
#include "values.h"
#include "player.h"
#include "field.h"

struct player p[2];
int field [SCREEN_WIDTH] ;
int turn = pOne;
int numPlayers = 2;

int main(void) {
	int i;
	//TODO: player has to check where he spawns
	//TODO: field generating algorithm
	initScreen();
	initCharBuffer();
	initField();

	//note HAVE to init field then players
	initPlayer(pOne, 50, SCREEN_HEIGHT * 7 / 10 - TANK_HEIGHT - 1, 90, 3,
			0xAAAA, 0, 1, 100);
	initPlayer(pTwo, SCREEN_WIDTH*3/4, SCREEN_HEIGHT * 7 / 10 - TANK_HEIGHT - 1, -90, 3,
			0xCCCC, 0, 1, 100);

	//printField();

	while (1) {

		//printSD();
		//moves left
		if (IORD(keys,0) == 8) {
			moveLeft(turn);
		}
		//moves right
		if (IORD(keys,0) == 4) {
			moveRight(turn);
		}
		//turret fire
		if (IORD(keys,0) == 2) {
			//fire power should be 0<power<100
			turretFire(turn, 100); //need to get power from keyboard

			//TODO: skip players that are dead
			turn = (turn + 1) % numPlayers;

		}
		//turret CW
		if (IORD(switches,0) == 1) {
			turretCW(turn);
		}
		//turret CCW
		if (IORD(switches,0) == 2) {
			turretCCW(turn);
		}

		//printf("degree: %d \n",p[turn].deg);

		clearScreen();

		for (i = 0; i < numPlayers; ++i) {
			checkPlayerFalling(i);
			updatePlayer(i);
			//printHp(i);
		}

		updateField();
		//drawTest();
		updateScreen();

	}
	/*
	 printLines();
	 printString();
	 //printLines();
	 */

	return 0;
}

