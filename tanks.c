/*
 * tanks.h
 * Clone of Tanks using the Altera DE2 Board.
 *
 *	Created: 2014-01-18
 *		Author: Brittaney Geisler, Isaac Cheng, Kelvin Au, Kevin Hui
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "sd_card.h"
#include "screen.h"
#include "values.h"
#include "player.h"
#include "field.h"

struct player p[2];
char field[SCREEN_HEIGHT][SCREEN_WIDTH];
int turn = pOne;
int numPlayers = 2;

int main(void) {
	int i, j;

	//TODO: player has to check where he spawns
	//TODO: field generating algorithm
	initScreen();
	initField();

	//note HAVE to init field then players
	initPlayer(pOne, 50, SCREEN_HEIGHT * 7 / 10 - TANK_HEIGHT - 1, 0, 1,
			0xAAAA, 0, 1, 100);
	initPlayer(pTwo, 250, SCREEN_HEIGHT * 7 / 10 - TANK_HEIGHT - 1, 0, 1,
			0xCCCC, 0, 1, 100);

	//printField();

	while (1) {
		//printSD();

		//moves left
		if (*keys == 8) {
			moveLeft(turn);
		}
		//moves right
		if (*keys == 4) {
			moveRight(turn);
		}
		//turret fire
		if (*keys == 2) {
			turretFire(turn, 300); //need to get power from keyboard

			//TODO: skip players that are dead
			turn = (turn + 1) % numPlayers;

		}
		//turret CW
		if (*switches == 1) {
			turretCW(turn);
		}
		//turret CCW
		if (*switches == 2) {
			turretCCW(turn);
		}

		//printf("degree: %d \n",p[turn].deg);

		clearScreen();

		for (i = 0; i < numPlayers; ++i) {
			updatePlayer(p[i].x, p[i].y, p[i].deg, p[i].colour);
		}

		updateField();
		updateScreen();
	}
	/*
	 printLines();
	 printString();
	 //printLines();
	 */

	return 0;
}

