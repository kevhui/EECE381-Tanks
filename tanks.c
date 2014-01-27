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

struct player p[2];
int turn = pOne;
int numPlayers = 2;

int main(void) {

	initScreen();
	int i;

	p[0].x = 50;
	p[0].y = 159;
	p[0].deg = 0;
	p[0].hp = 1;
	p[0].colour = 0xAAAA;

	p[1].x = 250;
	p[1].y = 159;
	p[0].deg = 0;
	p[1].hp = 1;
	p[1].colour = 0xCCCC;

	initScreen();
	while(1){
		//printSD();

		//moves left
		if(*keys == 8){
			moveLeft(turn);
		}
		//moves right
		if(*keys == 4){
			moveRight(turn);
		}
		//turret fire
		if(*keys == 2){
			turretFire(turn,50); //need to get power from keyboard
			turn = (turn+1)%2;
		}
		//turret CW
		if(*switches == 1){
			turretCW(turn);
		}
		//turret CCW
		if(*switches == 2){
			turretCCW(turn);
		}


		printf("degree: %d",p[turn].deg);

		clearScreen();
		updateField();

		for (i = 0; i < numPlayers; ++i) {
			updatePlayer(p[i].x,p[i].y,p[i].deg,p[i].colour);
		}
		updateScreen();

		printf("\n");
	}
	/*
	printLines();
	printString();
	//printLines();
	*/

	return 0;
}

