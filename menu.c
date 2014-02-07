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
char playersconfig = 1;//number of players configured
int playercolor;
int playertype;

void initState0() {
	playersconfig = 1;
	playercolor = 0;
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

void initState1(int playernum) {
	clearCharBuffer();
	clearScreen();
	printString("TANKS", 36, 10);
	printString("Player #", 33, 14);
	if (playernum == 1)
		printString("1", 42, 14);
	else if (playernum == 2)
		printString("2", 42, 14);
	else if (playernum == 3)
		printString("3", 42, 14);
	else if (playernum == 4)
		printString("4", 42, 14);
	//print player number
	printString("ENTER NAME: ", 14, 20);
	printString("CHANGE COLOR: ", 14, 24);
	printString("PINK", 28, 24);//default
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
			if (playersconfig < numPlayers) {
				initPlayer(playersconfig, playercolor, player_name, playertype);
				clearPlayerName();
				playersconfig++;//this corresponds to the player ID
				initState1(playersconfig);
			} else {
				initPlayer(playersconfig, playercolor, player_name, playertype);
				state = 2;
			}
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
			if (playercolor == 0) {
				playercolor = 1;
				AdjustChar("BLUE", 28, 24);
			} else {
				playercolor = 0;
				AdjustChar("PINK", 28, 24);
			}
			break;
		case RIGHT_ARROW: //right
			if (playercolor == 0) {
				playercolor = 1;
				AdjustChar("BLUE", 28, 24);
			} else {
				playercolor = 0;
				AdjustChar("PINK", 28, 24);
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

void initPlayer(int id, int colour, char *name, int type) {
	if (id == 1)
		p[id].x = 15;
	else if (id == 2)
		p[id].x = 60;
	else if (id == 3)
		p[id].x = 30;
	else if (id == 4)
		p[id].x = 45;
	p[id].y = 40;
	if (id == 1 || id == 3)
		p[id].deg = 30;
	else if (id == 2 || id == 4)
		p[id].deg = 150;
	p[id].hp = 100;
	p[id].colour = colour;//0=PINK//1=BLUE
	p[id].points = 0;
	p[id].alive = 1;//0=dead,1=alive
	p[id].gas = 100;
	if (id == 1 || id == 3)
		p[id].dir = 0;
	else if (id == 2 || id == 4)
		p[id].dir = 1;
	//0=right, 1=left
	strcpy((p[id].name), name);
	p[id].type = type;
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

