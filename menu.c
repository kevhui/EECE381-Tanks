/*
 * menu.c
 *
 *  Created on: 2014-02-03
 *      Author: Kevin
 */

#include "menu.h"

char *display_string;//string to write to screen
char player_name[10];//player name
int count = 0;//count for player name
char playersconfig;//number of players configured
int playerCharacter;
int playertype;

void initState0() {
	playersconfig = 0;
	playerCharacter = MARIO;
	playertype = 0;

	printString("TANKS", 36, 10);
	printString("NUMBER OF PLAYERS:", 15, 20);
	printString("2", 22, 24);
	printString("(press left and right", 14, 28);
	printString("arrows to change)", 16, 30);
	printString("PRESS SPACE", 33, 50);
	printString("CONTROLS:", 45, 20);
	printString("KEY(3) AND KEY(2) : MOVE TANK", 45, 24);
	printString("SW(1) AND SW(0) : TILT GUN", 45, 28);
	//printString("PGUP AND PGDOWN : CHANGE POWER",45, 32);
	//printString("W : CHANGE WEAPON",45, 36);
	printString("KEY(1) : FIRE", 45, 32);
	updateScreen();
}

void initState1(int id) {
	clearCharBuffer();
	clearScreen();
	printString("TANKS", 36, 10);
	printString("Player #", 33, 14);
	if (id == pOne)
		printString("1", 42, 14);
	else if (id == pTwo)
		printString("2", 42, 14);
	else if (id == pThree)
		printString("1", 42, 14);
	else if (id == pFour)
		printString("1", 42, 14);
	printString("ENTER NAME: ", 14, 20);
	printString("CHANGE COLOR: ", 14, 24);
	printString("MARIO", 28, 24);//default
	//print player color
	printString("SELECT PLAYER TYPE: ", 14, 28);
	printString("COMP", 34, 28);//default
	//print player type
	printString("PRESS SPACE TO START", 25, 50);
	updateScreen();
}

void state_0(int decode_mode, alt_8 buf) {
	if (decode_mode == KB_BINARY_MAKE_CODE && buf == SPACEBAR) {
		state = 1;
	} else if (decode_mode == KB_LONG_BINARY_MAKE_CODE) {
		if (buf == LEFT_ARROW && numPlayers > 2) {
			numPlayers -= 1;
			updateNumPlayers();
		}
		if (buf == RIGHT_ARROW && numPlayers < 4) {
			numPlayers += 1;
			updateNumPlayers();
		}
	}
}

void state_1(int decode_mode, alt_8 buf, char ascii) {
	if (decode_mode == KB_ASCII_MAKE_CODE) {//letters
		Name_Entered(ascii);
	}

	else if (decode_mode == KB_BINARY_MAKE_CODE) {
		if (buf == SPACEBAR) {
			//TODO: make an options menu to adust hp
			//printf("playerCharacter %i",playerCharacter);
			initPlayer(playersconfig, playerCharacter, player_name, playertype);
			clearPlayerName();
			playersconfig++;//this corresponds to the player ID
			initState1(playersconfig);
			printf("numPlyaers %i\n", numPlayers);
			printf("playersconfig %i\n", playersconfig);
			if (playersconfig == numPlayers)
				state = 2;
		} else if (buf == BACKSPACE) {//back space
			if (count > 0) {
				player_name[count - 1] = 0;
				count--;
				AdjustChar(" ", 26 + count, 20);
			}
		}
	} else if (decode_mode == KB_LONG_BINARY_MAKE_CODE) {
		switch (buf) {
		case LEFT_ARROW: //left
			if (playerCharacter == LUIGI) {
				playerCharacter = MARIO;
				AdjustChar("MARIO", 28, 24);
			} else {
				playerCharacter = LUIGI;
				AdjustChar("LUIGI", 28, 24);
			}
			break;
		case RIGHT_ARROW: //right
			if (playerCharacter == LUIGI) {
				playerCharacter = MARIO;
				AdjustChar("MARIO", 28, 24);
			} else {
				playerCharacter = LUIGI;
				AdjustChar("LUIGI", 28, 24);
			}
			break;
		case UP_ARROW: //up
			if (playertype == 0) {
				playertype = 1;
				AdjustChar("REAL", 34, 28);
			} else {
				playertype = 0;
				AdjustChar("COMP", 34, 28);
			}
			break;
		case DOWN_ARROW:
			if (playertype == 0) {
				playertype = 1;
				AdjustChar("REAL", 34, 28);
			} else {
				playertype = 0;
				AdjustChar("COMP", 34, 28);
			}
			break;
		}
	}
}

void AdjustChar(char *string, int x, int y) {
	printString(string, x, y);
}

void clearPlayerName() {
	while (count > 0) {
		player_name[count] = 0;
		count--;
	}
}

void Name_Entered(char *a) {
	player_name[count] = a;
	count++;
	if (count <= 10)
		AdjustChar(player_name, 26, 20);
}

void updateNumPlayers() {
	switch (numPlayers) {
	case 2:
		AdjustChar("2", 22, 24);
		break;
	case 3:
		AdjustChar("3", 22, 24);
		break;
	case 4:
		AdjustChar("4", 22, 24);
		break;
	}
}

