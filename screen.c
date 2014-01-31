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
	int i;
	for (i = 0; i < SCREEN_WIDTH; i++) {
		alt_up_pixel_buffer_dma_draw_line(pixel_buffer, i, SCREEN_HEIGHT - 1,
				i, field[i], 0xFFFF, 1);
	}
}

//prints the prints a player to the screen
void updatePlayer(int pNumber) {
	// Draw a rectangle for the field
	int x = p[pNumber].x;
	int y = p[pNumber].y;
	int colour = p[pNumber].colour;
	int deg = p[pNumber].deg;

	int i;
	//printf("\n\n");
	for (i = 0; i < 16; ++i) {
		//printf("%x",0x0000+i);
		alt_up_pixel_buffer_dma_draw(pixel_buffer, 0x000F + i, i, 10);//1
		alt_up_pixel_buffer_dma_draw(pixel_buffer, 0x00F0 + i, i, 14);//2
		alt_up_pixel_buffer_dma_draw(pixel_buffer, 0x0F0F + i, i, 18);//3
		alt_up_pixel_buffer_dma_draw(pixel_buffer, 0x0FF0 + i, i, 22);//4
		alt_up_pixel_buffer_dma_draw(pixel_buffer, 0x0FFF + i, i, 26);//5
		alt_up_pixel_buffer_dma_draw(pixel_buffer, 0xF000 + i, i, 30);//6
		alt_up_pixel_buffer_dma_draw(pixel_buffer, 0xF00F + i, i, 34);//7
		alt_up_pixel_buffer_dma_draw(pixel_buffer, 0xF0FF + i, i, 38);//8
		alt_up_pixel_buffer_dma_draw(pixel_buffer, 0xFF00 + i, i, 42);//9
		alt_up_pixel_buffer_dma_draw(pixel_buffer, 0xFF0F + i, i, 46);//10

		alt_up_pixel_buffer_dma_draw(pixel_buffer, 0xFF00 + 4*i, 10, 50);//yellow
		alt_up_pixel_buffer_dma_draw(pixel_buffer, 0xF50F + 4*i, 12, 50);//orange
		alt_up_pixel_buffer_dma_draw(pixel_buffer, 0xF01F + 4*i, 14, 50);//purple
		alt_up_pixel_buffer_dma_draw(pixel_buffer, 0x0000 + 4*i, 16, 50);//black
		alt_up_pixel_buffer_dma_draw(pixel_buffer, 0xFFFF + 4*i, 16, 50);//white




	}


	alt_up_pixel_buffer_dma_draw_rectangle(pixel_buffer, x, y, x + TANK_LENGTH,
			y + TANK_HEIGHT, colour, 1);
	alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x + TANK_LENGTH / 2, y,
			x + TANK_LENGTH / 2 + getTurretWidth(deg),
			y - getTurretHeight(deg), colour, 1);
}

//prints a bullet to the screen
//TODO: make the bullet not one pixel
void updateBullet(int x, int y) {
	alt_up_pixel_buffer_dma_draw(pixel_buffer, 0xFFFF, x, y);
}

//draws a circle as an explosion
void updateExplosion(int x, int y, int offset,int colour) {
	//The first two draw lines is to clean up the circle
	alt_up_pixel_buffer_dma_draw_line(pixel_buffer, x, y+offset, x, y-offset,colour, 1);
}

//prints lines
void printLines() {
	alt_up_pixel_buffer_dma_dev* pixel_buffer;
	// Use the name of your pixel buffer DMA core
	pixel_buffer = alt_up_pixel_buffer_dma_open_dev(PIXEL_BUFFER_DMA_NAME);
	// Set the background buffer address � Although we don�t use the
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

void initCharBuffer(){
	char_buffer = alt_up_char_buffer_open_dev("/dev/char_drawer");
	alt_up_char_buffer_init(char_buffer);
}

//Prints string
void printString() {
	// Write some text
	alt_up_char_buffer_string(char_buffer, "EECE 381", 40, 30);
}

//Prints string
void printHp(int pNumber) {
	if(pNumber==0){
		switch(p[pNumber].hp){
		case 1:
			alt_up_char_buffer_string(char_buffer, "Player One: 1HP", 20, 30);
			break;
		case 2:
			alt_up_char_buffer_string(char_buffer, "Player One: 2HP", 20, 30);
			break;
		case 3:
			alt_up_char_buffer_string(char_buffer, "Player One: 3HP", 20, 30);
			break;
		}
	}
	else if(pNumber==1){
		switch(p[pNumber].hp){
		case 1:
			alt_up_char_buffer_string(char_buffer, "Player Two: 1HP", 40, 30);
			break;
		case 2:
			alt_up_char_buffer_string(char_buffer, "Player Two: 2HP", 40, 30);
			break;
		case 3:
			alt_up_char_buffer_string(char_buffer, "Player Two: 3HP", 40, 30);
			break;
		}
	}
}
