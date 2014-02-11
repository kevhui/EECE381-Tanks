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
#include <sys/alt_irq.h>
#include "altera_up_ps2_keyboard.h"
#include "altera_up_avalon_character_lcd.h"
#include "altera_up_avalon_ps2.h"
#include "nios2_ctrl_reg_macros.h"
#include "sd_card.h"
#include "screen.h"
#include "values.h"
#include "player.h"
#include "menu.h"
#include "sys/alt_alarm.h"
#include "sys/alt_timestamp.h"

static void initKeyboard();//initializes keyboard
void runGame();
void setPlayerTurn();
void updateActions();

int windPower = 0;
struct player p[3];
int field[SCREEN_WIDTH];
int map[SCREEN_HEIGHT][SCREEN_WIDTH];
int turn = pOne;
int numPlayers;
float start_time;
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
int fpUp = 0;
int fpDown = 0;

void GameOverScreen() {
	clearScreen();
	updateScreen();
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
				break;
			case 1: //page down
				break;
			}
		} else if (decode_mode == KB_LONG_BINARY_MAKE_CODE) {
			printf("Pressed %c\n", ascii);
			switch (buf[0]) {
			case LEFT_ARROW: //left arrow
				fLeft = 1;
				break;
			case RIGHT_ARROW: //right arrow
				fRight = 1;
				break;
			case UP_ARROW: //up arrow
				fUp = 1;
				break;
			case DOWN_ARROW: //down arrow
				fDown = 1;
				break;
			case PAGE_UP: //page up
				fpUp = 1;
				break;
			case PAGE_DOWN: //page down
				fpDown = 1;
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

		} else if (decode_mode == KB_LONG_BREAK_CODE) {
			printf("Released %c\n", ascii);
			printf("Released %i\n", buf[0]);
			switch (buf[0]) {
			case LEFT_ARROW: //left arrow
				fLeft = 0;
				break;
			case RIGHT_ARROW: //right arrow
				fRight = 0;
				break;
			case UP_ARROW: //up arrow
				fUp = 0;
				break;
			case DOWN_ARROW: //down arrow
				fDown = 0;
				break;
			case SPACEBAR: //space bar
				fFire = 0;
				break;
			case PAGE_UP: //page up
				fpUp = 0;
				break;
			case PAGE_DOWN: //page down
				fpDown = 0;
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
	while (1) {
		int setTime = 15;
		numPlayers = 2;
		initScreen();
		clearScreen();
		initCharBuffer();
		clean_up();
		initKeyboard();
		initState0();
		initSD();

		//This is for Isaac cause he doesnt have a keyboard
		if (IORD(keys,0) == 8) {
			initPlayer(pOne, MARIO, "pOne", HUMAN);
			initPlayer(pTwo, LUIGI, "pTwo", HUMAN);
			state = 2;
		} else {
			while (state == 0) {
				decode_scancode(ps2, &decode_mode, buf, &ascii);
				state_0(decode_mode, buf[0]);
			};

			initState1(pOne);
			while (state == 1) {
				decode_scancode(ps2, &decode_mode, buf, &ascii);
				state_1(decode_mode, buf[0], ascii);
			};
		}

		//clean_up();
		clearCharBuffer();
		clearScreen();

		//enable keyboard IRQ
		void* keyboard_control_register_ptr = (void*) (KEYBOARD_BASE + 4);
		alt_irq_register(KEYBOARD_IRQ, keyboard_control_register_ptr,
				keyboard_ISR);
		alt_up_ps2_enable_read_interrupt(ps2);

		//Draw field and UI to both buffers
		initField();
		updateField();
		drawName(p[pOne].name, p[pTwo].name, p[pThree].name, p[pFour].name);
		drawGas(p[pOne].gas);
		drawHealth(p[pOne].hp, p[pTwo].hp, p[pThree].hp, p[pFour].hp);
		//drawBullet(0);
		//drawWindIndicator(1);
		updateScreen();
		updateField();
		drawName(p[pOne].name, p[pTwo].name, p[pThree].name, p[pFour].name);
		drawGas(p[pOne].gas);
		drawHealth(p[pOne].hp, p[pTwo].hp, p[pThree].hp, p[pFour].hp);
		//drawBullet(0);
		//drawWindIndicator(1);
		updateScreen();

		float time;
		alt_timestamp_start();

		start_time = (float) alt_timestamp() / (float) alt_timestamp_freq();
		printf("NUM PLAYERA %i\n", numPlayers);
		while (state == 2) {
			time = (float) alt_timestamp() / (float) alt_timestamp_freq()- start_time;
			if(time >= setTime){
				setPlayerTurn();
			}
			runGame();
			printTimer(setTime - time);

		}
		alt_up_ps2_disable_read_interrupt(ps2);
		GameOverScreen();
		while (state == 3)
			;

	}
}

void runGame(void) {
	undrawPlayers();
	updateActions();
	int i;



	//printf("degree: %d \n",p[turn].deg);

	//clearScreen();
	//updateField();

	for (i = 0; i < numPlayers; ++i) {
		if (p[i].alive) {
			checkPlayerFalling(i);
			updatePlayer(i);
		}
	}

	drawGas(p[turn].gas);
	drawPower(p[turn].power);
	updateScreen();
	usleep(1000);

	//TODO: check all players
	int deadCount = 0;
	for (i = 0; i < numPlayers; i++) {
		if (p[i].alive == DEAD)
			deadCount++;
	}
	if (deadCount == numPlayers - 1) {
		usleep(500000);
		state = 3;
	}
}

void setPlayerTurn() {
	alt_timestamp_start();
	start_time = (float) alt_timestamp() / (float) alt_timestamp_freq();
	int playerStatus;
	do {
		turn = (turn + 1) % numPlayers;
		playerStatus = p[turn].alive;
	} while (playerStatus == DEAD);
	printf("turn %i\n", turn);
	p[turn].gas = 100;
}

void updateActions() {

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
		turretFire(turn, 100, windPower, 2); //need to get power from keyboard
		setPlayerTurn();

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
	if (fpDown == 1) {
		if (p[turn].power - 1 >= 0)
			p[turn].power--;
	}
	if (fpUp == 1) {
		if (p[turn].power + 1 <= 100)
			p[turn].power++;
	}
	if (fFire == 1) {
		alt_up_ps2_disable_read_interrupt(ps2);
		turretFire(turn, p[turn].power, windPower, 2);
		setPlayerTurn();
		alt_up_ps2_enable_read_interrupt(ps2);
		printf("Before enabled interupt\n");
		alt_up_ps2_clear_fifo(ps2);
		printf("Fifo cleared\n");
		fFire = 0;
		drawHealth(p[pOne].hp, p[pTwo].hp, p[pThree].hp, p[pFour].hp);
		//drawBullet(0);
		//drawWindIndicator(1);
		updateScreen();
		drawHealth(p[pOne].hp, p[pTwo].hp, p[pThree].hp, p[pFour].hp);
	}
}

