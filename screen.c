/*
 * vga.c
 *
 *	Created: 2014-01-18
 *		Author: Brittaney Geisler, Isaac Cheng, Kelvin Au, Kevin Hui
 */

#include "screen.h"

alt_up_pixel_buffer_dma_dev *pixel_buffer;
alt_up_char_buffer_dev *char_buffer;
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
	while (alt_up_pixel_buffer_dma_check_swap_buffers_status(pixel_buffer))
		;
	//printf("is it white?"); 	for (count = 0; count < wait; ++count) {	}
}

//TODO: Print the whole field without lag
//prints the field to the screen
void updateField() {
	// Draw a rectangle for the field
	//alt_up_pixel_buffer_dma_draw_rectangle(pixel_buffer, 0, 160, SCREEN_WIDTH
	//	- 1, SCREEN_HEIGHT - 1, 0xFFFF, 1);
	int i, j;
	unsigned int addr;
	for (i = 0; i < SCREEN_WIDTH; i++) {
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

		//TODO: switch case the character and choose appropriate colour
		alt_up_pixel_buffer_dma_draw_line(pixel_buffer, t_startX, t_startY,
				t_endX, t_endY, p[turn].colour, 1);
	}
}

//prints a bullet to the screen
//TODO: make the bullet not one pixel
void updateBullet(int x, int y) {
	//only redraw the bullet
	int i, j;
	unsigned int addr;
	int offset = 10;

	for (i = x - offset; i < x + offset; i++) {
		for (j = y - offset; j < y + offset; j++) {
			addr = ((i & pixel_buffer->x_coord_mask) << 1);
			addr += (((j & pixel_buffer -> y_coord_mask) * 320) << 1);
			IOWR_16DIRECT(pixel_buffer->back_buffer_start_address,addr, map[j][i]);
			//alt_up_pixel_buffer_dma_draw(pixel_buffer,hyrule[j][i],i,j);
		}
	}
	//must redraw player to compensate for blackbox of bullet
	for (i = 0; i < numPlayers; ++i) {
		updatePlayer(i);
	}

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
}

//Prints string
void printString(char *out_string, int x, int y) {
	// Write some text
	alt_up_char_buffer_string(char_buffer, out_string, x, y);
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


// 0<= power <= 100
void drawHealth(int health1, int health2, int health3, int health4) {
	int i, j, x_start, x_coordinate, y_coordinate;
	int count = 0;
	int percentage;
	int health;

	// Test Image
	for (j = 0; j < CHARACTER_MARIO_HEIGHT; j++) {
		for (i = 0; i < CHARACTER_MARIO_WIDTH; i++) {
			alt_up_pixel_buffer_dma_draw(pixel_buffer, 0xffff, i, j);
		}
	}

	while (count < numPlayers) {
		if (count == 0) {
			health = health1;
			x_start = CHARACTER_MARIO_WIDTH;
		} else {
			if (numPlayers == 2) {
				health = health2;
				x_start = (CHARACTER_MARIO_WIDTH + HEALTH_BAR_WIDTH) * 2
						+ WIND_WIDTH;
			} else if (numPlayers == 3) {
				if (count == 1) {
					health = health2;
					x_start = CHARACTER_MARIO_WIDTH + HEALTH_BAR_WIDTH
							+ CHARACTER_MARIO_WIDTH;
				} else if (count == 2) {
					health = health3;
					x_start = (CHARACTER_MARIO_WIDTH + HEALTH_BAR_WIDTH) * 2
							+ WIND_WIDTH;
				}
			} else {
				if (count == 1) {
					health = health2;
					x_start = CHARACTER_MARIO_WIDTH + HEALTH_BAR_WIDTH
							+ CHARACTER_MARIO_WIDTH;

					// Test Image
					for (j = 0; j < CHARACTER_MARIO_HEIGHT; j++) {
						for (i = 0, x_coordinate = (CHARACTER_MARIO_WIDTH
								+ HEALTH_BAR_WIDTH); i < CHARACTER_MARIO_WIDTH; i++, x_coordinate++) {
							alt_up_pixel_buffer_dma_draw(pixel_buffer, 0x7e0,
									x_coordinate, j);
						}
					}

				} else if (count == 2) {
					// Test Image
					for (j = 0; j < CHARACTER_MARIO_HEIGHT; j++) {
						for (i = 0, x_coordinate = (CHARACTER_MARIO_WIDTH
								+ HEALTH_BAR_WIDTH) * 2 + BULLET_BORDER_WIDTH; i
								< CHARACTER_MARIO_WIDTH; i++, x_coordinate++) {
							alt_up_pixel_buffer_dma_draw(pixel_buffer, 0xF800,
									x_coordinate, j);
						}
					}

					health = health3;
					x_start = (CHARACTER_MARIO_WIDTH + HEALTH_BAR_WIDTH) * 2
							+ CHARACTER_MARIO_WIDTH + WIND_WIDTH;
				} else {
					health = health4;
					x_start = (CHARACTER_MARIO_WIDTH + HEALTH_BAR_WIDTH) * 3
							+ CHARACTER_MARIO_WIDTH + WIND_WIDTH;

					// Test Image
					for (j = 0; j < CHARACTER_MARIO_HEIGHT; j++) {
						for (i = 0, x_coordinate = (CHARACTER_MARIO_WIDTH
								+ HEALTH_BAR_WIDTH) * 3 + BULLET_BORDER_WIDTH; i
								< CHARACTER_MARIO_WIDTH; i++, x_coordinate++) {
							alt_up_pixel_buffer_dma_draw(pixel_buffer, 0x1f,
									x_coordinate, j);
						}
					}

				}
			}
		}
		x_coordinate = x_start;
		y_coordinate = NAME_HEIGHT;

		percentage = (HEALTH_X_GREEN_END - HEALTH_X_GREEN_START) * health / 100;
		for (j = 0; j < HEALTH_BAR_HEIGHT; j++, y_coordinate++) {
			// y_coordinate in the green region
			if ((j >= HEALTH_Y_GREEN_START) && (j <= HEALTH_Y_GREEN_END)) {
				// Before the grey area
				for (i = 0, x_coordinate = x_start; i <= HEALTH_Y_GREEN_START
						+ percentage; i++, x_coordinate++) {
					alt_up_pixel_buffer_dma_draw(pixel_buffer,
							health_bar[j][i], x_coordinate, y_coordinate);
				}
				// Grey area - After the percentage, before the border
				for (; i <= HEALTH_X_GREEN_END; i++, x_coordinate++) {
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

