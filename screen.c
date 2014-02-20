/*
 * vga.c
 *
 *	Created: 2014-01-18
 *		Author: Brittaney Geisler, Isaac Cheng, Kelvin Au, Kevin Hui
 */

#include "screen.h"
#include "audio.h"

alt_up_pixel_buffer_dma_dev *pixel_buffer;
alt_up_char_buffer_dev *char_buffer;
alt_up_char_buffer_dev *timer_buffer;
int i = 0;

//initialises the screen buffer
void initScreen() {
	unsigned int pixel_buffer_addr1 = PIXEL_BUFFER_BASE;
	unsigned int pixel_buffer_addr2 = PIXEL_BUFFER_BASE + PIXEL_BUFFER_SPAN / 2;// Set the 1st buffer address

	// Use the name of your pixel buffer DMA core
	pixel_buffer = alt_up_pixel_buffer_dma_open_dev(PIXEL_BUFFER_DMA_NAME);

	alt_up_pixel_buffer_dma_change_back_buffer_address(pixel_buffer,
			pixel_buffer_addr1);
	alt_up_pixel_buffer_dma_swap_buffers(pixel_buffer);
	while (alt_up_pixel_buffer_dma_check_swap_buffers_status(pixel_buffer))
		;
	alt_up_pixel_buffer_dma_change_back_buffer_address(pixel_buffer,
			pixel_buffer_addr2);

	alt_up_pixel_buffer_dma_clear_screen(pixel_buffer, 0);
	alt_up_pixel_buffer_dma_clear_screen(pixel_buffer, 1);
}

//clears the screen
void clearScreen() {
	alt_up_pixel_buffer_dma_clear_screen(pixel_buffer, 1);
}

//swaps the background buffer to the foreground
void updateScreen() {
	alt_up_pixel_buffer_dma_swap_buffers(pixel_buffer);
	while (alt_up_pixel_buffer_dma_check_swap_buffers_status(pixel_buffer)){
		if(aOn)loop_audio(file_handle, fname, ab);
	}

	//printf("is it white?"); 	for (count = 0; count < wait; ++count) {	}
}

//prints the field to the screen
void updateField() {
	// Draw a rectangle for the field
	//alt_up_pixel_buffer_dma_draw_rectangle(pixel_buffer, 0, 160, SCREEN_WIDTH
	//	- 1, SCREEN_HEIGHT - 1, 0xFFFF, 1);
	int i, j;
	unsigned int addr;
	for (i = 0; i < SCREEN_WIDTH; i++) {
		if(aOn)loop_audio(file_handle, fname, ab);
		for (j = field[i]; j < SCREEN_HEIGHT; j++) {
			addr = ((i & pixel_buffer->x_coord_mask) << 1);
			addr += (((j & pixel_buffer -> y_coord_mask) * 320) << 1);
			IOWR_16DIRECT(pixel_buffer->back_buffer_start_address,addr, map[j][i]);
			//alt_up_pixel_buffer_dma_draw(pixel_buffer,hyrule[j][i],i,j);
		}
	}
}

//prints the prints a player to the screen
void updatePlayer(int id) {
	int i, j;
	int x = p[id].x;
	int y = p[id].y;

	//alt_up_pixel_buffer_dma_draw_rectangle(pixel_buffer, x, y, x + TANK_LENGTH-1,
	//y + TANK_HEIGHT-1, colour, 1);
	switch (p[id].character) {
	case MARIO:
		for (i = 0; i < TANK_LENGTH; i++) {
			if(aOn)loop_audio(file_handle, fname, ab);
			for (j = 0; j < TANK_HEIGHT; j++) {
				if (p[id].dir == RIGHT && mario_right[j][i] != MASK)
					fastPixel(x + i, y + j, mario_right[j][i]);
				else if (p[id].dir == LEFT && mario_left[j][i] != MASK)
					fastPixel(x + i, y + j, mario_left[j][i]);
			}
		}
		break;
	case LUIGI:
		for (i = 0; i < TANK_LENGTH; i++) {
			if(aOn)loop_audio(file_handle, fname, ab);
			for (j = 0; j < TANK_HEIGHT; j++) {
				if (p[id].dir == RIGHT && luigi_right[j][i] != MASK)
					fastPixel(x + i, y + j, luigi_right[j][i]);
				else if (p[id].dir == LEFT && luigi_left[j][i] != MASK)
					fastPixel(x + i, y + j, luigi_left[j][i]);
			}
		}
		break;
	}
	if (turn == id) {
		int deg = p[id].deg * p[id].dir;
		int t_startX = x + TANK_LENGTH / 2 + getTurretWidth(deg) * 2 / 3;
		int t_startY = y + TANK_HEIGHT / 2 - getTurretHeight(deg) * 2 / 3;
		int t_endX = x + TANK_LENGTH / 2 + getTurretWidth(deg);
		int t_endY = y + TANK_HEIGHT / 2 - getTurretHeight(deg);
		if(t_endX <= 0){
			t_endX = 1;
		}
		if(t_endX >= SCREEN_WIDTH){
			t_endX = SCREEN_WIDTH - 2;
		}
		if(t_startX <= 0){
			t_startX = 1;
		}
		if(t_startX >= SCREEN_WIDTH){
			t_startX = SCREEN_WIDTH - 2;
		}
		//TODO: switch case the character and choose appropriate colour
		alt_up_pixel_buffer_dma_draw_line(pixel_buffer, t_startX, t_startY,
				t_endX, t_endY, p[turn].colour, 1);
	}
}

void undrawBullet(int x, int y) {
	int i, j;
	unsigned int addr;
	int offset = 10;

	for (i = x - offset; i < x + offset; i++) {
		if(aOn)loop_audio(file_handle, fname, ab);
		for (j = y - offset; j < y + offset; j++) {
			addr = ((i & pixel_buffer->x_coord_mask) << 1);
			addr += (((j & pixel_buffer -> y_coord_mask) * 320) << 1);
			IOWR_16DIRECT(pixel_buffer->back_buffer_start_address,addr, map[j][i]);
			//alt_up_pixel_buffer_dma_draw(pixel_buffer,hyrule[j][i],i,j);
		}
	}
	//must redraw player and UI to compensate for blackbox of bullet
	for (i = 0; i < numPlayers; ++i) {
		if (p[i].alive)
			updatePlayer(i);
	}
	drawGas(p[turn].gas);
	drawPower(p[turn].power);
	drawHealth(p[pOne].hp, p[pTwo].hp, p[pThree].hp, p[pFour].hp);
}

//prints a bullet to the screen
//TODO: make the bullet not one pixel
void updateBullet(int x, int y) {
	//only redraw the bullet
	alt_up_pixel_buffer_dma_draw(pixel_buffer, 0xFFFF, x, y);
}

//draws a circle as an explosion
void updateExplosion(int x, int y, int offset, int colour) {
	alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x, y + offset, x,
			y - offset, colour, 1);
}

//prints lines
void printLines() {
	alt_up_pixel_buffer_dma_dev* pixel_buffer;
	// Use the name of your pixel buffer DMA core
	pixel_buffer = alt_up_pixel_buffer_dma_open_dev(PIXEL_BUFFER_DMA_NAME);
	// Set the background buffer address – Although we don’t use the
	//background, they only provide a function to change the background
	//buffer address, so
	// we must set that, and then swap it to the foreground.
	alt_up_pixel_buffer_dma_change_back_buffer_address(pixel_buffer,
			PIXEL_BUFFER_BASE);
	// Swap background and foreground buffers
	alt_up_pixel_buffer_dma_swap_buffers(pixel_buffer);
	// Wait for the swap to complete while
	(alt_up_pixel_buffer_dma_check_swap_buffers_status(pixel_buffer));
	// Clear the screen
	alt_up_pixel_buffer_dma_clear_screen(pixel_buffer, 0);
	// Draw a white line to the foreground buffer
	alt_up_pixel_buffer_dma_draw_line(pixel_buffer, 0, 0, 320, 240, 0xFFFF, 0);
}

void initCharBuffer() {
	char_buffer = alt_up_char_buffer_open_dev("/dev/char_drawer");
	alt_up_char_buffer_init(char_buffer);
	alt_up_char_buffer_init(timer_buffer);
}

//Prints string
void printString(char *out_string, int x, int y) {
	// Write some text
	alt_up_char_buffer_string(char_buffer, out_string, x, y);
}

void printTimer(int time) {
	int x = 40;
	int y = 10;
	switch (time) {
	case 0:
		alt_up_char_buffer_string(char_buffer, " 0", x, y);
		break;
	case 1:
		alt_up_char_buffer_string(char_buffer, " 1", x, y);
		break;
	case 2:
		alt_up_char_buffer_string(char_buffer, " 2", x, y);
		break;
	case 3:
		alt_up_char_buffer_string(char_buffer, " 3", x, y);
		break;
	case 4:
		alt_up_char_buffer_string(char_buffer, " 4", x, y);
		break;
	case 5:
		alt_up_char_buffer_string(char_buffer, " 5", x, y);
		break;
	case 6:
		alt_up_char_buffer_string(char_buffer, " 6", x, y);
		break;
	case 7:
		alt_up_char_buffer_string(char_buffer, " 7", x, y);
		break;
	case 8:
		alt_up_char_buffer_string(char_buffer, " 8", x, y);
		break;
	case 9:
		alt_up_char_buffer_string(char_buffer, " 9", x, y);
		break;
	case 10:
		alt_up_char_buffer_string(char_buffer, "10", x, y);
		break;
	case 11:
		alt_up_char_buffer_string(char_buffer, "11", x, y);
		break;
	case 12:
		alt_up_char_buffer_string(char_buffer, "12", x, y);
		break;
	case 13:
		alt_up_char_buffer_string(char_buffer, "13", x, y);
		break;
	case 14:
		alt_up_char_buffer_string(char_buffer, "14", x, y);
		break;
	case 15:
		alt_up_char_buffer_string(char_buffer, "15", x, y);
		break;
	case 16:
		alt_up_char_buffer_string(char_buffer, "16", x, y);
		break;
	case 17:
		alt_up_char_buffer_string(char_buffer, "17", x, y);
		break;
	case 18:
		alt_up_char_buffer_string(char_buffer, "18", x, y);
		break;
	case 19:
		alt_up_char_buffer_string(char_buffer, "19", x, y);
		break;
	case 20:
		alt_up_char_buffer_string(char_buffer, "20", x, y);
		break;
	}
}

//Prints string
//TODO: MAKE THIS BETTER
void printHp(int id) {
	alt_up_char_buffer_string(char_buffer, p[pOne].name, 10, 10);
	alt_up_char_buffer_string(char_buffer, p[pTwo].name, 50, 10);
	/*if (p[pOne].colour==1)alt_up_char_buffer_string(char_buffer, "BLUE", 10, 14);
	 else if (p[pOne].colour==0) alt_up_char_buffer_string(char_buffer, "PINK", 10, 14);
	 if (p[pTwo].colour==1)alt_up_char_buffer_string(char_buffer, "BLUE", 50, 14);
	 else if (p[pTwo].colour==0) alt_up_char_buffer_string(char_buffer,"PINK", 50, 14);
	 if (p[pOne].type==1)alt_up_char_buffer_string(char_buffer, "REAL", 10, 18);
	 else if (p[pOne].type==0) alt_up_char_buffer_string(char_buffer, "COMP", 10, 18);
	 if (p[pTwo].type==1)alt_up_char_buffer_string(char_buffer, "REAL", 50, 18);
	 else if (p[pTwo].type==0) alt_up_char_buffer_string(char_buffer, "COMP", 50, 18);
	 */

	if (p[pTwo].hp == 0) {
		alt_up_char_buffer_string(char_buffer, ": WINS!", 20, 10);
		alt_up_char_buffer_string(char_buffer, ": X___X", 60, 10);
	} else if (p[pOne].hp == 0) {
		alt_up_char_buffer_string(char_buffer, ": X___X", 20, 10);
		alt_up_char_buffer_string(char_buffer, ": WINS!", 60, 10);
	} else if (id == pOne) {

		switch (p[pOne].hp) {
		case 1:
			alt_up_char_buffer_string(char_buffer, ": 1HP", 20, 10);
			break;
		case 2:
			alt_up_char_buffer_string(char_buffer, ": 2HP", 20, 10);
			break;
		case 3:
			alt_up_char_buffer_string(char_buffer, ": 3HP", 20, 10);
			break;
		}
	} else if (id == pTwo) {
		switch (p[pTwo].hp) {
		case 1:
			alt_up_char_buffer_string(char_buffer, ": 1HP", 60, 10);
			break;
		case 2:
			alt_up_char_buffer_string(char_buffer, ": 2HP", 60, 10);
			break;
		case 3:
			alt_up_char_buffer_string(char_buffer, ": 3HP", 60, 10);
			break;
		}
	}
}

/*
 void drawTest() {
 int i, j;
 for (j = 0; j < HYRULE_HEIGHT; j++) {
 for (i = 0; i < HYRULE_WIDTH; i++) {
 alt_up_pixel_buffer_dma_draw(pixel_buffer, hyrule[j][i], i, j);
 }
 }

 }
 */

void clearCharBuffer() {
	alt_up_char_buffer_clear(char_buffer);
}

void undrawPlayers() {
	int id, i, j, x, y, character;
	int offset = 16;
	//TODO:change to cycle only alive players
	for (id = 0; id < numPlayers; ++id) {
		if(aOn)loop_audio(file_handle, fname, ab);
		x = p[id].x;
		y = p[id].y;

		character = p[id].character;
		for (j = -offset; j < TANK_HEIGHT + offset; j++) {
			for (i = -offset; i < TANK_LENGTH + offset; i++) {
				fastPixel(x + i, y + j, map[y + j][x + i]);
			}
		}

	}
}

void undrawPlayer(int id) {
	int i, j, x, y, character;
	int offset = 16;
	//TODO:change to cycle only alive players
		if(aOn)loop_audio(file_handle, fname, ab);
		x = p[id].x;
		y = p[id].y;

		character = p[id].character;
		for (j = -offset; j < TANK_HEIGHT + offset; j++) {
			for (i = -offset; i < TANK_LENGTH + offset; i++) {
				fastPixel(x + i, y + j, map[y + j][x + i]);
			}
		}
}

void fastPixel(int x, int y, int colour) {
	unsigned int addr;
	addr = ((x & pixel_buffer->x_coord_mask) << 1);
	addr += (((y & pixel_buffer -> y_coord_mask) * 320) << 1);
	IOWR_16DIRECT(pixel_buffer->back_buffer_start_address,addr, colour);
}

void drawName(char* name1, char* name2, char* name3, char* name4) {
	if (numPlayers == 2) {
		alt_up_char_buffer_string(char_buffer, name1, 6, 0);
		alt_up_char_buffer_string(char_buffer, name2, 48, 0);
	} else if (numPlayers == 3) {
		alt_up_char_buffer_string(char_buffer, name1, 6, 0);
		alt_up_char_buffer_string(char_buffer, name2, 24, 0);
		alt_up_char_buffer_string(char_buffer, name3, 48, 0);
	} else {
		alt_up_char_buffer_string(char_buffer, name1, 6, 0);
		alt_up_char_buffer_string(char_buffer, name2, 24, 0);
		alt_up_char_buffer_string(char_buffer, name3, 48, 0);
		alt_up_char_buffer_string(char_buffer, name4, 66, 0);
	}
}

void drawHealth(int health1, int health2, int health3, int health4) {
	int i, j, x_start, x_coordinate, y_coordinate;
	int count = 0;
	int percentage;
	int health;

	// Test Image
/*	for (j = 0; j < CHARACTER_MARIO_HEIGHT; j++) {
		loop_audio(file_handle, fname, ab);
		for (i = 0; i < CHARACTER_MARIO_WIDTH; i++) {
			alt_up_pixel_buffer_dma_draw(pixel_buffer, 0xffff, i, j);
		}
	}*/

	while (count < numPlayers) {
		if (count == 0) {
			health = health1;
			x_start = CHARACTER_MARIO_WIDTH;
		} else {
			if (numPlayers == 2) {
				health = health2;
				x_start = (CHARACTER_MARIO_WIDTH + HEALTH_BAR_WIDTH) * 2
						+ WIND_WIDTH + CHARACTER_MARIO_WIDTH;
			} else if (numPlayers == 3) {
				if (count == 1) {
					health = health2;
					x_start = CHARACTER_MARIO_WIDTH + HEALTH_BAR_WIDTH
							+ CHARACTER_MARIO_WIDTH;
				} else if (count == 2) {
					health = health3;
					x_start = (CHARACTER_MARIO_WIDTH + HEALTH_BAR_WIDTH) * 2
							+ CHARACTER_MARIO_WIDTH + WIND_WIDTH;
				}
			} else {
				if (count == 1) {
					health = health2;
					x_start = CHARACTER_MARIO_WIDTH + HEALTH_BAR_WIDTH
							+ CHARACTER_MARIO_WIDTH;

					// Test Image
/*					for (j = 0; j < CHARACTER_MARIO_HEIGHT; j++) {
						for (i = 0, x_coordinate = (CHARACTER_MARIO_WIDTH
								+ HEALTH_BAR_WIDTH); i < CHARACTER_MARIO_WIDTH; i++, x_coordinate++) {
							alt_up_pixel_buffer_dma_draw(pixel_buffer, 0x7e0,
									x_coordinate, j);
						}
					}*/

				} else if (count == 2) {
					// Test Image
/*					for (j = 0; j < CHARACTER_MARIO_HEIGHT; j++) {
						for (i = 0, x_coordinate = (CHARACTER_MARIO_WIDTH
								+ HEALTH_BAR_WIDTH) * 2 + BULLET_BORDER_WIDTH; i
								< CHARACTER_MARIO_WIDTH; i++, x_coordinate++) {
							alt_up_pixel_buffer_dma_draw(pixel_buffer, 0xF800,
									x_coordinate, j);
						}
					}*/

					health = health3;
					x_start = (CHARACTER_MARIO_WIDTH + HEALTH_BAR_WIDTH) * 2
							+ CHARACTER_MARIO_WIDTH + WIND_WIDTH;
				} else {
					health = health4;
					x_start = (CHARACTER_MARIO_WIDTH + HEALTH_BAR_WIDTH) * 3
							+ CHARACTER_MARIO_WIDTH + WIND_WIDTH;

					// Test Image
/*					for (j = 0; j < CHARACTER_MARIO_HEIGHT; j++) {
						for (i = 0, x_coordinate = (CHARACTER_MARIO_WIDTH
								+ HEALTH_BAR_WIDTH) * 3 + BULLET_BORDER_WIDTH; i
								< CHARACTER_MARIO_WIDTH; i++, x_coordinate++) {
							alt_up_pixel_buffer_dma_draw(pixel_buffer, 0x1f,
									x_coordinate, j);
						}
					}*/

				}
			}
		}
		x_coordinate = x_start;
		y_coordinate = NAME_HEIGHT;

		percentage = (HEALTH_GREEN_X_END - HEALTH_GREEN_X_START) * health / 100;
		for (j = 0; j < HEALTH_BAR_HEIGHT; j++, y_coordinate++) {
			if(aOn)loop_audio(file_handle, fname, ab);
			// y_coordinate in the green region
			if ((j >= HEALTH_GREEN_Y_START) && (j <= HEALTH_GREEN_Y_END)) {
				// Before the grey area
				for (i = 0, x_coordinate = x_start; i <= HEALTH_GREEN_Y_START
						+ percentage; i++, x_coordinate++) {
					alt_up_pixel_buffer_dma_draw(pixel_buffer,
							health_bar[j][i], x_coordinate, y_coordinate);
				}
				// Grey area - After the percentage, before the border
				for (; i <= HEALTH_GREEN_X_END; i++, x_coordinate++) {
					alt_up_pixel_buffer_dma_draw(pixel_buffer, 0x7BEF,
							x_coordinate, y_coordinate);
				}
				// After the grey area, Start the border again
				for (; i < HEALTH_BAR_WIDTH; i++, x_coordinate++) {
					alt_up_pixel_buffer_dma_draw(pixel_buffer,
							health_bar[j][i], x_coordinate, y_coordinate);
				}
			} else {
				for (i = 0, x_coordinate = x_start; i < HEALTH_BAR_WIDTH; i++, x_coordinate++) {
					alt_up_pixel_buffer_dma_draw(pixel_buffer,
							health_bar[j][i], x_coordinate, y_coordinate);
				}
			}
		}
		count++;
	}
}

void drawGas(int gas) {
	int i, j, x_start, y_start, x_coordinate, y_coordinate, percentage;

	x_start = 3;
	y_start = CHARACTER_MARIO_HEIGHT + 10;

	percentage = (GAS_BLUE_Y_END - GAS_BLUE_Y_START) * gas / 100;

	for (i = 0, x_coordinate = x_start; i < GAS_BAR_WIDTH; i++, x_coordinate++) {
		if(aOn)loop_audio(file_handle, fname, ab);
		// In the region
		if ((i >= GAS_BLUE_X_START) && (i <= GAS_BLUE_X_END)) {

			for (j = GAS_BAR_HEIGHT - 1, y_coordinate = y_start; j
					> GAS_BLUE_Y_END; j--, y_coordinate++) {
				alt_up_pixel_buffer_dma_draw(pixel_buffer, gas_bar[j][i],
						x_coordinate, y_coordinate);
			}
			// Grey area - After the percentage, before the border
			for (; j >= GAS_BLUE_Y_START + percentage; j--, y_coordinate++) {
				alt_up_pixel_buffer_dma_draw(pixel_buffer, 0x7BEF,
						x_coordinate, y_coordinate);
			}

			// After the grey area, Start the border again
			for (; j >= 0; j--, y_coordinate++) {
				alt_up_pixel_buffer_dma_draw(pixel_buffer, gas_bar[j][i],
						x_coordinate, y_coordinate);
			}
		} else {
			for (j = GAS_BAR_HEIGHT - 1, y_coordinate = y_start; j >= 0; j--, y_coordinate++) {
				alt_up_pixel_buffer_dma_draw(pixel_buffer, gas_bar[j][i],
						x_coordinate, y_coordinate);
			}
		}
	}

	if (gas == 99) {
		for (j = 0, y_coordinate = y_start + GAS_BLUE_Y_START + 2; j < 1; j++, y_coordinate++) {
			if(aOn)loop_audio(file_handle, fname, ab);
			for (i = 0, x_coordinate = x_start + GAS_BLUE_X_START; i
					< GAS_BLUE_X_END - GAS_BLUE_X_START + 1; i++, x_coordinate++)
				alt_up_pixel_buffer_dma_draw(pixel_buffer, 0x4e9a,
						x_coordinate, y_coordinate);
		}
	} else if (gas == 100) {
		for (j = 0, y_coordinate = y_start + GAS_BLUE_Y_START + 1; j < 2; j++, y_coordinate++) {
			if(aOn)loop_audio(file_handle, fname, ab);
			for (i = 0, x_coordinate = x_start + GAS_BLUE_X_START; i
					< GAS_BLUE_X_END - GAS_BLUE_X_START + 1; i++, x_coordinate++)
				alt_up_pixel_buffer_dma_draw(pixel_buffer, 0x4e9a,
						x_coordinate, y_coordinate);
		}
	}

}

// 0<= power <= 100 - red
void drawPower(int power) {
	int i, j, x_start, y_start, x_coordinate, y_coordinate, percentage;

	x_start = SCREEN_WIDTH - 3 - POWER_BAR_WIDTH;
	y_start = CHARACTER_MARIO_HEIGHT + 10;

	percentage = (POWER_RED_Y_END - POWER_RED_Y_START) * power / 100;

	for (i = 0, x_coordinate = x_start; i < POWER_BAR_WIDTH; i++, x_coordinate++) {
		if(aOn)loop_audio(file_handle, fname, ab);
		// In the region
		if ((i >= POWER_RED_X_START) && (i <= POWER_RED_X_END)) {

			for (j = POWER_BAR_HEIGHT - 1, y_coordinate = y_start; j
					> POWER_RED_Y_END; j--, y_coordinate++) {
				fastPixel(x_coordinate, y_coordinate, power_bar[j][i]);
			}

			// Grey area - After the percentage, before the border
			for (; j >= POWER_RED_Y_START + percentage; j--, y_coordinate++) {
				fastPixel(x_coordinate, y_coordinate, 0x7BEF);
			}

			// After the grey area, Start the border again
			for (; j >= 0; j--, y_coordinate++) {
				fastPixel(x_coordinate, y_coordinate, power_bar[j][i]);
			}
		} else {
			for (j = POWER_BAR_HEIGHT - 1, y_coordinate = y_start; j >= 0; j--, y_coordinate++) {
				fastPixel(x_coordinate, y_coordinate, power_bar[j][i]);
			}
		}
	}

	if (power == 99) {
		for (j = 0, y_coordinate = y_start + POWER_RED_Y_START + 2; j < 1; j++, y_coordinate++) {
			if(aOn)loop_audio(file_handle, fname, ab);
			for (i = 0, x_coordinate = x_start + POWER_RED_X_START; i
					< POWER_RED_X_END - POWER_RED_X_START; i++, x_coordinate++)
				fastPixel(x_coordinate, y_coordinate, 0xd800);
			fastPixel(x_coordinate, y_coordinate, 0xb963);
		}
	} else if (power == 100) {
		for (j = 0, y_coordinate = y_start + POWER_RED_Y_START + 1; j < 2; j++, y_coordinate++) {
			if(aOn)loop_audio(file_handle, fname, ab);
			for (i = 0, x_coordinate = x_start + POWER_RED_X_START; i
					< POWER_RED_X_END - POWER_RED_X_START; i++, x_coordinate++)
				fastPixel(x_coordinate, y_coordinate, 0xd800);
			fastPixel(x_coordinate, y_coordinate, 0xb963);
		}
	}

}

// Bullet Border 20px x 20px
// 	Bullet 15px x 15px
void drawBullet(int bulletType) {
	int i, j, x_start, x_coordinate, y_coordinate, bullet_height, bullet_width;
	int bullet[14][14];

	x_start = (CHARACTER_MARIO_WIDTH + HEALTH_BAR_WIDTH) * 2;
	for (j = 0; j < BULLET_BORDER_HEIGHT; j++, y_coordinate++) {
		if(aOn)loop_audio(file_handle, fname, ab);
		for (i = 0, x_coordinate = x_start; i < BULLET_BORDER_WIDTH; i++, x_coordinate++) {
			alt_up_pixel_buffer_dma_draw(pixel_buffer, bullet_border[j][i],
					x_coordinate, j);
		}
	}


	 // Bullet
	 if (bulletType == 0){
		 alt_up_pixel_buffer_dma_draw(pixel_buffer,0xFFFF,148 + 10,5);
	 }

	 if (bulletType == 1){
		 alt_up_pixel_buffer_dma_draw(pixel_buffer,0xFFFF,148+ 8,5);
		 alt_up_pixel_buffer_dma_draw(pixel_buffer,0xFFFF,148 + 10,5);
		 alt_up_pixel_buffer_dma_draw(pixel_buffer,0xFFFF,148 + 12,5);
	 }

}

// Wind 20px x 10px
// Wind Direction 20px x 10px
/*void drawWindIndicator(int windLevel) {
	int i, j, x_coordinate, y_coordinate, x_start;
	x_start = (CHARACTER_MARIO_WIDTH + HEALTH_BAR_WIDTH) * 2;

	// Right
	if (windLevel == 1) {
		for (j = 0, y_coordinate = BULLET_BORDER_HEIGHT; j
				< WIND_DIRECTION_HEIGHT; j++, y_coordinate++) {
			if(aOn)loop_audio(file_handle, fname, ab);
			for (i = 0, x_coordinate = x_start; i < WIND_DIRECTION_WIDTH; i++, x_coordinate++) {
				alt_up_pixel_buffer_dma_draw(pixel_buffer,
						wind_direction[j][i], x_coordinate, y_coordinate);
			}
		}
	}
	// Left
	else {
		for (j = 0, y_coordinate = BULLET_BORDER_HEIGHT; j
				< WIND_DIRECTION_HEIGHT; j++, y_coordinate++) {
			if(aOn)loop_audio(file_handle, fname, ab);
			for (i = WIND_DIRECTION_WIDTH - 1, x_coordinate = x_start; i >= 0; i--, x_coordinate++) {
				alt_up_pixel_buffer_dma_draw(pixel_buffer,
						wind_direction[j][i], x_coordinate, y_coordinate);
			}
		}
	}
}*/


void displayHighScore(char *player1,char *player2,char *player3,char *player4){
	score list[SCORE_BUFFER_SIZE];
	int player_score[11];
	score max_score[11];
	char *player_name = player1;
	char string_buffer[4];
	char tmp[2];
	int x_coordinate,y_coordinate,x_start;
	int position = 0;
	int i,j;


	if (getAllScore(list) == -1){
		alt_up_char_buffer_string(char_buffer,"No score recorded for AI!",30,20);
	}
	else{

		for (j=0,y_coordinate=90;j<MARIO_TANK_HEIGHT ;j++,y_coordinate++){
			for (i=0;i<MARIO_TANK_WIDTH;i++)
				alt_up_pixel_buffer_dma_draw(pixel_buffer,mario_tank[j][i],i,y_coordinate);
		}

		for (j=0;j<MARIO_HEIGHT ;j++){
			for (i=0,x_coordinate = SCREEN_WIDTH - MARIO_WIDTH + 10;i<MARIO_WIDTH;i++,x_coordinate++)
				alt_up_pixel_buffer_dma_draw(pixel_buffer,mario[j][i],x_coordinate,j);
		}


		for (j=0,y_coordinate= SCREEN_HEIGHT - LUIGI_HEIGHT - 2;j<LUIGI_HEIGHT ;j++,y_coordinate++){
			for (i=0,x_coordinate = SCREEN_WIDTH/2 - 32;i<LUIGI_WIDTH;i++,x_coordinate++)
				alt_up_pixel_buffer_dma_draw(pixel_buffer,luigi[j][i],x_coordinate,y_coordinate);
		}
/*
		for(i = SCREEN_WIDTH /2 - 1,j=0; j < SCREEN_HEIGHT ; j++){
						alt_up_pixel_buffer_dma_draw(pixel_buffer,0xffff,i,j);
		}
*/


		for (i = 0 ;i<5; i++){
			printf("player:%s score:%s\n",list[i].name,list[i].score);
		}

		// Print the personal score

		alt_up_char_buffer_string(char_buffer,"Personal Score",13,3);

		while(player_name != NULL){

			// Top left
			if (position == 0){
				x_coordinate = 7 ;
				y_coordinate = 6;
			}
			// Top right
			else if (position == 1) {
				x_coordinate = 27;
				y_coordinate = 6;
			}
			// Bottom left
			else if (position == 2){
				x_coordinate = 7;
				y_coordinate = SCREEN_CHARACTER_HEIGHT/2 + 5;
			}
			// Bottom right
			else{
				x_coordinate = 27;
				y_coordinate = SCREEN_CHARACTER_HEIGHT/2 + 5;
			}

			alt_up_char_buffer_string(char_buffer,player_name,x_coordinate,y_coordinate);
			x_coordinate += 2;
			y_coordinate += 2;
			getPersonalScore(list,player_score,player_name);
			for (i = 0 ; player_score[i] != -1 ; i++){
				convertInt(string_buffer,player_score[i]);
				alt_up_char_buffer_string(char_buffer,string_buffer,x_coordinate,y_coordinate);
				y_coordinate += 2;
			}

			if (position == 0)
				player_name = player2;
			else if (position == 1)
				player_name = player3;
			else if (position == 2)
				player_name = player4;
			else
				player_name = NULL;
			position++;
		}


		// Print the highest score
		alt_up_char_buffer_string(char_buffer,"Highest Score",SCREEN_CHARACTER_WIDTH/2 + 13,3);

		x_start = SCREEN_CHARACTER_WIDTH /2 + 5;
		x_coordinate = x_start;
		y_coordinate = 6;


		y_coordinate=y_coordinate+2;
		getMax10Score(list,max_score);
		for (i = 0; max_score[i].name[0] != '\0' ; i++){
				tmp[0] = (char)((int)'0'+i+1);
				tmp[1] = '\0';

				if (i==9){
					x_coordinate -= 1;
					alt_up_char_buffer_string(char_buffer,"10",x_coordinate,y_coordinate);
					x_coordinate += 2;
				}
				else{
					alt_up_char_buffer_string(char_buffer,tmp,x_coordinate,y_coordinate);
					x_coordinate++;
				}
				alt_up_char_buffer_string(char_buffer,".",x_coordinate,y_coordinate);
				x_coordinate+=2;

				alt_up_char_buffer_string(char_buffer,max_score[i].name,x_coordinate,y_coordinate);

				x_coordinate+=strlen(max_score[i].name);
				for (; x_coordinate < 75 ; x_coordinate++){
					alt_up_char_buffer_string(char_buffer,".",x_coordinate,y_coordinate);
				}

				alt_up_char_buffer_string(char_buffer,max_score[i].score,x_coordinate,y_coordinate);

				x_coordinate = x_start;
				y_coordinate += 5;
		}
	}

}
