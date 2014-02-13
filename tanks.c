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
#include "audio.h"
#include "system.h"
#include "ai.h"

static void initKeyboard();//initializes keyboard
void runGame();
void setPlayerTurn();
void updateActions();

aud_buf ab_1;
aud_buf *ab = &ab_1;
short int file_handle;
char* fname = "clip.wav";
int aOn = 0;

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
int fBullet;

void GameOverScreen() {
	clearScreen();
	updateScreen();
	clearCharBuffer();

	initSD();
	int i;
	for (i = 0; i < numPlayers; ++i) {
		if (p[i].name != NULL && p[i].type == HUMAN) {
			char name[10];
			strcpy(name, p[i].name);
			writeSD(name, p[i].points);
			printf("write:%i score: %i\n", i,p[i].points);
		}
	}

	for (i = 0; i < numPlayers; ++i) {
		printf("%s", p[i].name);
	}

	printString("GAME OVER!", 30, 25);
	usleep(10000000);

	clearScreen();
	updateScreen();
	clearCharBuffer();
	//displayHighScore("abc","a","b","c");
	if (numPlayers == 2) {
		displayHighScore(p[pOne].name, p[pTwo].name, NULL, NULL);
		printf("TWO");
	} else if (numPlayers == 3) {
		displayHighScore(p[pOne].name, p[pTwo].name, p[pThree].name, NULL);
		printf("THREE");
	} else {
		displayHighScore(p[pOne].name, p[pTwo].name, p[pThree].name,
				p[pFour].name);
		printf("ALL");
	}
	updateScreen();
	usleep(10000000);
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
			case 'Q': //down arrow
				fBullet = 1;
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
			case 21: //bullet switchs
				//changes power, no function yet
				fBullet = 0;
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

int initAudio(char* fname) {
	alt_up_sd_card_dev *device_reference = NULL;
	device_reference = alt_up_sd_card_open_dev(SD_CARD_NAME);

	open_sd();

	av_config_setup();
	init_audio_buff(ab);

	ab->audio = alt_up_audio_open_dev(AUDIO_0_NAME);
	alt_up_audio_reset_audio_core(ab->audio);

	file_handle = alt_up_sd_card_fopen(fname, 0);
	offset(file_handle, ab);

	fill_buff(file_handle, ab);

	return file_handle;
}

void initAI() {
	int i;
	for (i = 0; i < numPlayers; i++) {
		p[i].ai.isHit = FALSE;
	}
}

int main(void) {
	while (1) {
		state = 0;
		int setTime = 15;
		numPlayers = 2;
		initScreen();
		clearScreen();
		initCharBuffer();
		clean_up();
		initKeyboard();
		initState0();


		//This is for Isaac cause he doesnt have a keyboard
		if (IORD(keys,0) == 8) {
			initPlayer(pOne, MARIO, "pOne", 50, 100, HUMAN);
			initPlayer(pTwo, LUIGI, "pTwo", 50, 100, COMPUTER);
			state = 2;
		} else {
			while (state == 0) {
				decode_scancode(ps2, &decode_mode, buf, &ascii);
				state_0(decode_mode, buf[0]);
			};
			initState1(pOne);
			if(aOn)file_handle = initAudio(fname);
			if(aOn)alt_irq_register(AUDIO_0_IRQ, &ab, (alt_isr_func) write_fifo);
			if(aOn)		alt_up_audio_enable_write_interrupt(ab->audio);
			while (state == 1) {
				decode_scancode(ps2, &decode_mode, buf, &ascii);
				state_1(decode_mode, buf[0], ascii);
				if(aOn)loop_audio(file_handle, fname, ab);
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
		drawBullet(p[pOne].bulletType);
		//drawWindIndicator(1);
		updateScreen();

		updateField();
		drawName(p[pOne].name, p[pTwo].name, p[pThree].name, p[pFour].name);
		drawGas(p[pOne].gas);
		drawHealth(p[pOne].hp, p[pTwo].hp, p[pThree].hp, p[pFour].hp);
		drawBullet(p[pOne].bulletType);
		//drawWindIndicator(1);

		initAI();

		float time;
		alt_timestamp_start();


		int start_timer_flag = 1;
		//printf("NUM PLAYERA %i\n", numPlayers);
		int i;
		while (state == 2) {
			int fallFlag = 1;

			while (fallFlag == 1) {
				fallFlag = 0;
				for (i = 0; i < numPlayers; i++) {
					if (p[i].alive) {
						if (p[i].y + TANK_HEIGHT > SCREEN_HEIGHT) {
							p[i].hp = 0;
							p[i].alive = DEAD;
						}
						checkPlayerFalling(i);
						if (p[i].isFalling) {
							undrawPlayer(i);
							updatePlayer(i);
							fallFlag = 1;
							//checkPlayerFalling(i);
						}
					}
				}
				if (fallFlag == 1) {
					updateScreen();
				}
			}

			if(start_timer_flag){
				start_time = (float) alt_timestamp() / (float) alt_timestamp_freq();
				start_timer_flag = 0;
			}
			time = (float) alt_timestamp() / (float) alt_timestamp_freq()-start_time;
			if (time >= setTime) {
				setPlayerTurn();
			}
			if (p[turn].type == HUMAN) {
				runGame();

			} else {
				p[turn].deg = 0;
				aiMain(turn);
				setPlayerTurn();
			}
			printTimer(setTime - time);
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

		alt_up_ps2_disable_read_interrupt(ps2);
		if(aOn)alt_up_audio_disable_write_interrupt(ab->audio);

		GameOverScreen();
	}
}

void runGame(void) {
	undrawPlayers();
	updateActions();
	int i;

	//printf("degree: %d \n",p[turn].deg);

	//clearScreen();
	//updateField();

	for (i = 0; i < numPlayers; i++) {
		if(p[i].alive)updatePlayer(i);
	}

	drawBullet(p[turn].bulletType);
	drawGas(p[turn].gas);
	drawPower(p[turn].power);
	updateScreen();

	//usleep(1000);


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
		p[turn].moved = TRUE;
	}
	//moves right
	if (IORD(keys,0) == 4) {
		moveRight(turn);
		p[turn].moved = TRUE;
	}
	//turret fire
	if (IORD(keys,0) == 2) {
		//fire power should be 0<power<100
		turretFire(turn, 100, windPower, 0); //need to get power from keyboard
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
		p[turn].moved = TRUE;
		moveLeft(turn);
	}
	if (fRight == 1) {
		p[turn].moved = TRUE;
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
	if (fBullet == 1) {
		fBullet = 0;
		p[turn].bulletType = (p[turn].bulletType + 1)%2;
	}
	if (fFire == 1) {
		if (!p[turn].isFalling) {
			alt_up_ps2_disable_read_interrupt(ps2);
			turretFire(turn, p[turn].power, windPower, p[turn].bulletType);
			setPlayerTurn();
			alt_up_ps2_enable_read_interrupt(ps2);
			printf("Before enabled interupt\n");
			alt_up_ps2_clear_fifo(ps2);
			printf("Fifo cleared\n");
			fFire = 0;
			drawHealth(p[pOne].hp, p[pTwo].hp, p[pThree].hp, p[pFour].hp);
			drawBullet(p[turn].bulletType);
			//drawWindIndicator(1);
			updateScreen();
			drawHealth(p[pOne].hp, p[pTwo].hp, p[pThree].hp, p[pFour].hp);
		}
	}
}

