/*
 * menu.c
 *
 *  Created on: 2014-02-03
 *      Author: Brittaney
 */
 

#include "menu.h"


char *display_string;//string to write to screen
char player_name[10];//stores player name (while configuring player)
int count = 0;//count for player name(while configuring player)
int playersconfig = 0;//number of players configured
int playerCharacter;//mario or luigi
int playertype;//comp or real
int hp = 50;//health points
int gas = 25;//gas level
int audio_on = 0;//audio on/off
int cursor = 0;//used while configuring player

void initState0() {
	//initializes state 0 menu screen
	playersconfig = 0;
	initScreen();
	clearCharBuffer();
	clearScreen();
	printString("TANKS", 36, 10);
	printString("NUMBER OF PLAYERS:", 10, 20);
	printString("_2", 28, 20);
	printString("HEALTH POINTS:", 10, 24);
	printString("50", 25, 24);
	printString("GAS:", 10, 28);
	printString("25", 15, 28);
	printString("AUDIO:", 10, 32);
	printString("OFF", 17, 32);
	printString("PRESS SPACE", 33, 50);
	printString("CONTROLS:", 45, 20);
	printString("LEFT AND RIGHT ARROW : MOVE TANK", 45, 24);
	printString("UP AND DOWN ARROW : TILT GUN", 45, 28);
	printString("PGUP AND PGDOWN : CHANGE POWER", 45, 32);
	printString("Q : CHANGE WEAPON", 45, 36);
	printString("SPACE : FIRE", 45, 40);
	updateScreen();
}

void initState1(int playernum) {
	//initializes state 1 menu screen
	clearCharBuffer();
	clearScreen();
	playertype = COMPUTER;
	printString("TANKS", 36, 10);
	printString("Player #", 33, 14);
	if (playernum == pOne)
		printString("1", 42, 14);
	else if (playernum == pTwo)
		printString("2", 42, 14);
	else if (playernum == pThree)
		printString("3", 42, 14);
	else if (playernum == pFour)
		printString("4", 42, 14);
	printString("ENTER NAME:_", 14, 20);
	printString("CHANGE COLOR: ", 14, 24);
	printString("MARIO", 28, 24);//default
	printString("SELECT PLAYER TYPE: ", 14, 28);
	printString("COMP ", 34, 28);//default
	printString("PRESS SPACE TO START", 25, 50);
	updateScreen();
}

void state_0(int decode_mode, alt_8 buf) {
//checks for key press in state 0 menu
	if (decode_mode == KB_BINARY_MAKE_CODE && buf == SPACEBAR) {
	//SPACEBAR
		cursor = 0;
		state = 1;//change state
		aOn = audio_on;
	} 
	else if (decode_mode == KB_LONG_BINARY_MAKE_CODE) {
		if (buf == LEFT_ARROW) {
		//LEFT ARROW
			//check which attribute the cursor is located at
			if (cursor == 0) {
				//Change # of Players
				if (numPlayers > 2)
					numPlayers -= 1;
				updateNumPlayers();
			} else if (cursor == 1) {
				//Change # of health points
				if (hp > 50)
					hp -= 10;
				snprintf(display_string, sizeof(display_string), "%d", hp);
				AdjustChar(display_string, 25, 24);
				if (hp < 100)
					AdjustChar(" ", 27, 24);
			} else if (cursor == 2) {
				//Change Gas level
				if (gas > 0)
					gas -= 5;
				snprintf(display_string, sizeof(display_string), "%d", gas);
				AdjustChar(display_string, 15, 28);
				if (gas < 100)
					AdjustChar(" ", 17, 28);
			}
			else if (cursor == 3) {
				//turn audio on/off
				if (audio_on == 0) {
					audio_on = 1;
					AdjustChar("ON", 17, 32);
					AdjustChar(" ", 19, 32);
				} else if (audio_on == 1) {
					audio_on = 0;
					AdjustChar("OFF", 17, 32);
				}
			}
		}
		if (buf == RIGHT_ARROW) {
		//RIGHT ARROW
			if (cursor == 0) {
				//Change # of Players
				if (numPlayers < 4)
					numPlayers += 1;
				updateNumPlayers();
			} else if (cursor == 1) {
				//Change # of health points
				if (hp < 100)
					hp += 10;
				snprintf(display_string, sizeof(display_string), "%d", hp);
				AdjustChar(display_string, 25, 24);
			} else if (cursor == 2) {
				//change gas level
				if (gas < 100)
					gas += 5;
				snprintf(display_string, sizeof(display_string), "%d", gas);
				AdjustChar(display_string, 15, 28);
			}
			else if (cursor == 3) {
				//turn audio on/off
				if (audio_on == 0) {
					audio_on = 1;
					AdjustChar("ON", 17, 32);
					AdjustChar(" ", 19, 32);
				} else if (audio_on == 1) {
					audio_on = 0;
					AdjustChar("OFF", 17, 32);
				}
			}
		}
		if (buf == UP_ARROW) {
		//UP ARROW
		//changes location of cursor
			if (cursor > 0) {
				cursor -= 1;
			}
			if (cursor == 0) {
				AdjustChar(" ", 24, 24);
				AdjustChar("_", 28, 20);
			} else if (cursor == 1) {
				AdjustChar("_", 24, 24);
				AdjustChar(" ", 14, 28);
			} else if (cursor == 2) {
				AdjustChar("_", 14, 28);
				AdjustChar(" ", 16, 32);
			}
		}
		if (buf == DOWN_ARROW) {
		//DOWN ARROW
		//changes location of cursor
			if (cursor < 3) {
				cursor += 1;
			}
			if (cursor == 1) {
				AdjustChar("_", 24, 24);
				AdjustChar(" ", 28, 20);
			} else if (cursor == 2) {
				AdjustChar("_", 14, 28);
				AdjustChar(" ", 24, 24);
			} else if (cursor == 3) {
				AdjustChar("_", 16, 32);
				AdjustChar(" ", 14, 28);
			}
		}
	}
}

void state_1(int decode_mode, alt_8 buf, char ascii) {
//checks for key press in state 1 menu
	if (decode_mode == KB_ASCII_MAKE_CODE) {
		//Enter Name
		Name_Entered(ascii);
	}

	else if (decode_mode == KB_BINARY_MAKE_CODE) {
		if (buf == SPACEBAR) {
		//SPACE BAR
			//check if all players have been configured
			//and decide whether to change state or configure ANOTHER player
			if (playersconfig < numPlayers - 1) {
				if (count > 0) {
					initPlayer(playersconfig, playerCharacter, player_name, hp,
							gas, playertype);
				} else {
					initPlayer(playersconfig, playerCharacter, "Guest", hp,
							gas, playertype);
				}
				clearPlayerName();
				playersconfig++;
				cursor = 0;
				count = 0;
				initState1(playersconfig);
			} else { if (count > 0) {
					initPlayer(playersconfig, playerCharacter, player_name, hp,
							gas, playertype);
				} else {
					initPlayer(playersconfig, playerCharacter, "Guest", hp,
							gas, playertype);
				}
				state = 2;
				if (numPlayers == 2) {
					initPlayer(pThree, MARIO, NULL, hp, gas, HUMAN);
					initPlayer(pFour, MARIO, NULL, hp, gas, HUMAN);
				}
				if (numPlayers == 3) {
					initPlayer(pFour, MARIO, NULL, hp, gas, HUMAN);
				}
			}
		} else if (buf == BACKSPACE) {
		  //BACK SPACE
		  	//change player name 
			if (cursor == 0) {
				if (count > 0) {
					player_name[count - 1] = 0;
					count--;
					AdjustChar(" ", 26 + count, 20);
				}
			}
		}
	} else if (decode_mode == KB_LONG_BINARY_MAKE_CODE) {
		switch (buf) {
			//check key pressed and location of cursor
		case LEFT_ARROW:
			if (cursor == 1) {
				if (playerCharacter == LUIGI) {
					playerCharacter = MARIO;
					AdjustChar("MARIO", 28, 24);
				} else {
					playerCharacter = LUIGI;
					AdjustChar("LUIGI", 28, 24);
				}
			}
			if (cursor == 2) {
				if (playertype == COMPUTER) {
					playertype = HUMAN;
					AdjustChar("HUMAN", 34, 28);
				} else {
					playertype = COMPUTER;
					AdjustChar("COMP ", 34, 28);
				}
			}
			break;
		case RIGHT_ARROW:
			if (cursor == 1) {
				if (playerCharacter == LUIGI) {
					playerCharacter = MARIO;
					AdjustChar("MARIO", 28, 24);
				} else {
					playerCharacter = LUIGI;
					AdjustChar("LUIGI", 28, 24);
				}
			}
			if (cursor == 2) {
				if (playertype == COMPUTER) {
					playertype = HUMAN;
					AdjustChar("HUMAN", 34, 28);
				} else {
					playertype = COMPUTER;
					AdjustChar("COMP ", 34, 28);
				}
			}
			break;
		case UP_ARROW: 
			if (cursor > 0) {
				cursor -= 1;
			}
			if (cursor == 0) {
				AdjustChar(" ", 27, 24);
				AdjustChar("_", 25, 20);
			} else if (cursor == 1) {
				AdjustChar(" ", 33, 28);
				AdjustChar("_", 27, 24);
			}
			break;
		case DOWN_ARROW:
			if (cursor < 2) {
				cursor += 1;
			}
			if (cursor == 1) {
				AdjustChar("_", 27, 24);
				AdjustChar(" ", 25, 20);
			} else if (cursor == 2) {
				AdjustChar("_", 33, 28);
				AdjustChar(" ", 27, 24);
			}
			break;
		}
	}
}

void AdjustChar(char *string, int x, int y) {
	//print test string on screen at location x,y
	printString(string, x, y);
}

void clearPlayerName() {
	//when player is finished being configured
	//clear player name variable so that we can configure a new player
	while (count > 0) {
		player_name[count] = 0;
		count--;
	}
}

void Name_Entered(char *a) {
	//Displays and stores player name while being configured
	player_name[count] = a;
	count++;
	if (count <= 10) AdjustChar(player_name, 26, 20);
}

void updateNumPlayers() {
	//Adjusts and displays desired number of players
	switch (numPlayers) {
	case 2:
		AdjustChar("_2", 28, 20);
		break;
	case 3:
		AdjustChar("_3", 28, 20);
		break;
	case 4:
		AdjustChar("_4", 28, 20);
		break;
	}
}

