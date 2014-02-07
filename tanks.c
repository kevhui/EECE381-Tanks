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


struct player p[3];
int field[SCREEN_WIDTH];
int map[SCREEN_HEIGHT][SCREEN_WIDTH];
int turn = pOne;
int numPlayers;
//keyboard interrupt variables
alt_up_ps2_dev *ps2;
KB_CODE_TYPE decode_mode;
char ascii;
alt_u8 buf[4];

//set some of these in player struct!!!//
volatile int state = 0;//state of game

int fLeft = 0;
int fRight = 0;
int fDown = 0;
int fUp = 0;
int fFire = 0;

void WinScreenTest() {
	clearCharBuffer();
	printString("GAME OVER!", 30, 25);
	usleep(1000000);
	state = 0;
}

static void keyboard_ISR(void *c, alt_u32 id) { //keyboard interrupt handler
	if (decode_scancode(ps2, &decode_mode, buf, &ascii) == 0) {
		printf("Touched %c\n", ascii);
		printf("%d is the code\n", decode_mode);
		if (decode_mode == KB_BINARY_MAKE_CODE && buf[0] == SPACEBAR) {
			fFire = 1;
			//theres no power int in the player struct
		} else if (decode_mode == KB_ASCII_MAKE_CODE) {
			printf("Pressed %c\n", ascii);
			switch (ascii) {
			case 'A': //left arrow
				fLeft = 1;
				break;
			case 'D': //right arrow
				fRight = 1;
				break;
			case 'W': //up arrow
				fUp = 1;
				break;
			case 'S': //down arrow
				fDown = 1;
				break;
			case 0: //page up
				//changes power, no function yet
				break;
			case 1: //page down
				//changes power, no function yet
				break;
			}
		} else if (decode_mode == KB_BREAK_CODE) {
			printf("Released %c\n", ascii);
			printf("Released %i\n", buf[0]);
			switch (buf[0]) {
			case 28: //left arrow
				fLeft = 0;
				break;
			case 35: //right arrow
				fRight = 0;
				break;
			case 29: //up arrow
				fUp = 0;
				break;
			case 27: //down arrow
				fDown = 0;
				break;
			case 0: //page up
				//changes power, no function yet
				break;
			case 1: //page down
				//changes power, no function yet
				break;
			}

		}

		printf("Exited the keyboard IRQ\n");
	}
}

void clean_up() {
	clearCharBuffer();
	clearScreen();
	clearPlayerName();
	//num_of_players = 2;
	//playersconfig = 1;
	//playercolor = 0;
	//playertype = 0;
}

void initKeyboard() {
	ps2 = alt_up_ps2_open_dev(KEYBOARD_NAME);
	alt_up_ps2_init(ps2);
	alt_up_ps2_clear_fifo(ps2);

	//IOWR(KEYBOARD_BASE, 1, 0x01); //not sure but jeff put this in his code
}

int main(void) {
	int i;
	while (1) {
		numPlayers = 2;
		initScreen();
		clearScreen();
		initCharBuffer();
		//decode_scancode(ps2, &decode_mode, buf, &ascii);

		clean_up();
		initKeyboard();
		initField();
		initState0();
		while (state == 0) {
			decode_scancode(ps2, &decode_mode, buf, &ascii);
			state_0(decode_mode, buf[0]);
		};

		initState1(1);
		while (state == 1) {
			decode_scancode(ps2, &decode_mode, buf, &ascii);
			state_1(decode_mode, buf[0], ascii);
		};

		//clean_up();
		clearCharBuffer();
		clearScreen();

		void* keyboard_control_register_ptr = (void*) (KEYBOARD_BASE + 4);
		alt_irq_register(KEYBOARD_IRQ, keyboard_control_register_ptr,
				keyboard_ISR);
		alt_up_ps2_enable_read_interrupt(ps2);

		kevininitPlayer(pOne, 50, SCREEN_HEIGHT * 7 / 10 - TANK_HEIGHT - 1, 90,
				3, 0x4800, 0, 1, 100, RIGHT, p[1].name);
		kevininitPlayer(pTwo, SCREEN_WIDTH * 3 / 4,
				SCREEN_HEIGHT * 7 / 10 - TANK_HEIGHT - 1, 90, 3, 0x4648, 0, 1,
				100, LEFT, p[2].name);

		clearScreen();
		updateField();
		updateScreen();
		updateField();
		updateScreen();

		while (state == 2) {
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
			if (IORD(switches,0) == 4) {
				p[pOne].hp = 0;
			}

			if (fLeft == 1) {
				moveLeft(turn);
			}
			if (fRight == 1) {
				moveRight(turn);
			}
			if (fUp == 1) {
				turretCCW(turn);
			}
			if (fDown == 1) {
				turretCW(turn);
			}
			if (fFire == 1) {
				turretFire(turn, 100);
				turn = (turn + 1) % numPlayers;
				fFire = 0;
				/*				updateScreen();
				 clearScreen();
				 updateField();*/
				//clearScreen();
				//updateField();
			}

			//printf("degree: %d \n",p[turn].deg);

			//clearScreen();
			//updateField();


			for (i = 0; i < numPlayers; ++i) {
				checkPlayerFalling(i);
				updatePlayer(i);
				printHp(i);
			}
			//drawTest();
			updateScreen();
			usleep(5000);

			if (p[pOne].hp == 0 || p[pTwo].hp == 0) {
				usleep(1000000);
				state = 3;
			}
		}

		WinScreenTest();
		while (state == 3)
			;

	}
}

