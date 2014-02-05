/*
 * tanks.c
 * Clone of Tanks using the Altera DE2 Board.
 *
 *	Created: 2014-01-18
 *		Author: Brittaney Geisler, Isaac Cheng, Kelvin Au, Kevin Hui
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <io.h>
#include <alt_legacy_irq.h>
#include "altera_up_ps2_keyboard.h"
#include "altera_up_avalon_character_lcd.h"
#include "altera_up_avalon_ps2.h"
#include "nios2_ctrl_reg_macros.h"
#include "sd_card.h"
#include "screen.h"
#include "values.h"
#include "player.h"
#include "menu.h"

static void initKeyboard();//initializes keyboard
void initState0(void);//initializes the first menu screen
void initState1(int);//initializes the second menu screen
void AdjustChar();//change character on screen
void Name_Entered(char *);//player name entered handler
void GamePlayTest(void);//test for game play state
void WinScreenTest(void);//test for win state
void clean_up(void);//clean up game variables etc. (reset basically)
void clearPlayerName(void);//clears all player names
void initPlayer(int, int, char *, int);//initialize player struct
void printPlayerStruct(int);//test for player struct


struct player p[3];
int field[SCREEN_WIDTH];
int map[SCREEN_HEIGHT][SCREEN_WIDTH];
int turn = pOne;
int numPlayers = 2;
//keyboard interrupt variables
alt_up_ps2_dev *ps2;
KB_CODE_TYPE decode_mode;
char ascii;
alt_u8 buf[4];

//set some of these in player struct!!!//
volatile int state = 0;//state of game
int num_of_players = 2;//number of players
char *display_string;//string to write to screen
char player_name[10];//player name
int count = 0;//count for player name
char playersconfig;//number of players configured
int playercolor;
int playertype;

void WinScreenTest(){
	clearCharBuffer();
	printString("GAME OVER!",30,25);
	usleep(1000000);
	state=0;
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

static void keyboard_ISR(void *c, alt_u32 id) { //keyboard interrupt handler
	decode_scancode(ps2, &decode_mode, buf, &ascii);
	if (state == 0) {
		if (decode_mode == KB_BINARY_MAKE_CODE && buf[0] == SPACEBAR) { //spacebar
			state = 1;
		} else if (decode_mode == KB_LONG_BINARY_MAKE_CODE) {
			switch (buf[0]) {
			case LEFT_ARROW: //left arrow
				if (num_of_players > 2){
					num_of_players -= 1;
				snprintf(display_string, sizeof(display_string), "%d",num_of_players);
				//try this later: strcpy(display_string,num_of_players);
					AdjustChar(display_string, 22, 24);
				}
				break;
			case 0x74: //right arrow
				if (num_of_players < 4){
					num_of_players += 1;
				snprintf(display_string, sizeof(display_string), "%d",num_of_players);
				//try this later:	strcpy(display_string,num_of_players);
					AdjustChar(display_string, 22, 24);
				}
				break;
			case 0x75:
				break;
			}
		}
	}

	else if (state == 1) {
		if (decode_mode == KB_ASCII_MAKE_CODE) {//letters
			Name_Entered(ascii);
		}

		else if (decode_mode == KB_BINARY_MAKE_CODE) {
			if (buf[0] == SPACEBAR) { //spacebar
				if (playersconfig < num_of_players) {
					initPlayer(playersconfig, playercolor, player_name,
							playertype);
					clearPlayerName();
					playersconfig++;//this corresponds to the player ID
					initState1(playersconfig);
				} else {
					initPlayer(playersconfig, playercolor, player_name,
							playertype);
					state = 2;
				}
			} else if (buf[0] == 0x66) {//back space
				if (count > 0) {
					player_name[count - 1] = 0;
					count--;
					AdjustChar(" ", 26 + count, 20);
				}
			}
		} else if (decode_mode == KB_LONG_BINARY_MAKE_CODE) {
			printf("LOOKING FOR WHICH KEY WAS PRESSED \n");
			switch (buf[0]) {
			case LEFT_ARROW: //left
				if (playercolor == 0) {
					playercolor = 1;
					AdjustChar("BLUE", 28, 24);
				} else {
					playercolor = 0;
					AdjustChar("PINK", 28, 24);
				}
				break;
			case 0x74: //right
				if (playercolor == 0) {
					playercolor = 1;
					AdjustChar("BLUE", 28, 24);
				} else {
					playercolor = 0;
					AdjustChar("PINK", 28, 24);
				}
				break;
			case 0x75: //up
				if (playertype == 0) {
					playertype = 1;
					AdjustChar("REAL", 34, 28);
				} else {
					playertype = 0;
					AdjustChar("COMP", 34, 28);
				}
				break;
			case 0x72:
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

	else if (state == 2) {
		if (decode_mode == KB_BINARY_MAKE_CODE && buf[0] == SPACEBAR) {
			turretFire(turn, 100);
			turn = (turn + 1) % numPlayers;
			//theres no power int in the player struct
		} else if (decode_mode == KB_LONG_BINARY_MAKE_CODE) {
			switch (buf[0]) {
			case LEFT_ARROW: //left arrow
				moveLeft(turn);
				break;
			case 0x74: //right arrow
				moveRight(turn);
				break;
			case 0x75: //up arrow
				turretCCW(turn);
				break;
			case 0x72: //down arrow
				turretCW(turn);
				break;
			case 0x7d: //up arrow
				//changes power, no function yet
				break;
			case 0x7a: //down arrow
				//changes power, no function yet
				break;
			}
		}
	}
	printf("Exited the keyboard IRQ\n");
}

void AdjustChar(char *string, int x, int y) {
	printString(string, x, y);
}

void clean_up() {
	clearCharBuffer();
	clearScreen();
	clearPlayerName();
	num_of_players = 2;
	playersconfig = 1;
	playercolor = 0;
	playertype = 0;
}

void initKeyboard() {
	ps2 = alt_up_ps2_open_dev(KEYBOARD_NAME);
	alt_up_ps2_init(ps2);
	alt_up_ps2_clear_fifo(ps2);
	void* keyboard_control_register_ptr = (void*) (KEYBOARD_BASE + 4);
	alt_irq_register(KEYBOARD_IRQ, keyboard_control_register_ptr, keyboard_ISR);
	alt_up_ps2_enable_read_interrupt(ps2);
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

int main(void) {

	int i;
	//TODO: player has to check where he spawns
	//TODO: field generating algorithm
	initScreen();
	clearScreen();
	initCharBuffer();


	initState0();
	while (1) {
		//decode_scancode(ps2, &decode_mode, buf, &ascii);
		if (state == 0) {
			clean_up();
			initKeyboard();
			initField();
			initState0();
			while (state == 0);
		} else if (state == 1) {
			initState1(1);
			while (state == 1);
		} else if (state == 2) {
			//clean_up();
			clearCharBuffer();
			clearScreen();
			alt_irq_disable(KEYBOARD_IRQ);
			alt_up_ps2_disable_read_interrupt(ps2);
			ps2 = alt_up_ps2_open_dev(KEYBOARD_NAME);
			alt_up_ps2_init(ps2);
			alt_up_ps2_clear_fifo(ps2);
			printf("%s\n",p[1].name);
			printf("%s\n",p[2].name);
			kevininitPlayer(pOne, 50, SCREEN_HEIGHT * 7 / 10 - TANK_HEIGHT - 1,
					90, 3, 0x4800, 0, 1, 100, RIGHT,p[1].name);
			kevininitPlayer(pTwo, SCREEN_WIDTH * 3 / 4,
					SCREEN_HEIGHT * 7 / 10 - TANK_HEIGHT - 1, 90, 3, 0x4648, 0,
					1, 100, LEFT,p[2].name);
			printf("PLAERY 1: %s\n",p[0].name);
			printf("plaery  2: %s\n",p[1].name);
			while (state == 2) {
/*				decode_scancode(ps2, &decode_mode, buf, &ascii);
				if (decode_mode == KB_BINARY_MAKE_CODE && buf[0] == SPACEBAR) {
					turretFire(turn, 100);
					turn = (turn + 1) % numPlayers;
					//theres no power int in the player struct
				} else if (decode_mode == KB_LONG_BINARY_MAKE_CODE) {
					switch (buf[0]) {
					case LEFT_ARROW: //left arrow
						moveLeft(turn);
						break;
					case 0x74: //right arrow
						moveRight(turn);
						break;
					case 0x75: //up arrow
						turretCCW(turn);
						break;
					case 0x72: //down arrow
						turretCW(turn);
						break;
					case 0x7d: //up arrow
						//changes power, no function yet
						break;
					case 0x7a: //down arrow
						//changes power, no function yet
						break;
					}
				}
				alt_up_ps2_clear_fifo(ps2);*/
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

				//printf("GAME PLAYING");
				clearScreen();
				updateField();

				for (i = 0; i < numPlayers; ++i) {
					checkPlayerFalling(i);
					updatePlayer(i);
					printHp(i);
				}
				//drawTest();
				updateScreen();
				if(p[pOne].hp == 0 || p[pTwo].hp == 0){
					usleep(1000000);
					state = 3;
				}
			}
		} else if (state == 3) {
			WinScreenTest();
			while (state == 3)
				;
		}
	}
}

