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
	int i,j;
	unsigned int addr;
	for (i = 0; i < SCREEN_WIDTH; i++) {
		for(j = field[i]; j < SCREEN_HEIGHT; j++){
			addr = (( i & pixel_buffer->x_coord_mask) << 1);
			addr += (((j & pixel_buffer -> y_coord_mask) * 320) << 1);
			IOWR_16DIRECT(pixel_buffer->back_buffer_start_address,addr, hyrule[j][i]);
			//alt_up_pixel_buffer_dma_draw(pixel_buffer,hyrule[j][i],i,j);
		}
	}
}

//prints the prints a player to the screen
void updatePlayer(int pNumber) {
	// Draw a rectangle for the field
	int i,j;
	unsigned int addr;
	int x = p[pNumber].x;
	int y = p[pNumber].y;
	int colour = p[pNumber].colour;

	//alt_up_pixel_buffer_dma_draw_rectangle(pixel_buffer, x, y, x + TANK_LENGTH-1,
			//y + TANK_HEIGHT-1, colour, 1);
	switch (pNumber) {
		case pOne:
			for (i = 0; i < TANK_LENGTH; i++) {
				for(j = 0; j < TANK_HEIGHT; j++){
					addr = (( (i+p[pNumber].x) & pixel_buffer->x_coord_mask) << 1);
					addr += ((((j+p[pNumber].y) & pixel_buffer -> y_coord_mask) * 320) << 1);
					if(p[pNumber].dir == RIGHT){
						IOWR_16DIRECT(pixel_buffer->back_buffer_start_address,addr, mario_right[j][i]);}
					else if(p[pNumber].dir == LEFT){
						IOWR_16DIRECT(pixel_buffer->back_buffer_start_address,addr, mario_left[j][i]);}
				}
			}
			break;
		case pTwo:
			for (i = 0; i < TANK_LENGTH; i++) {
				for(j = 0; j <TANK_HEIGHT; j++){
					addr = (( (i+p[pNumber].x) & pixel_buffer->x_coord_mask) << 1);
					addr += ((((j+p[pNumber].y) & pixel_buffer -> y_coord_mask) * 320) << 1);
					if(p[pNumber].dir == RIGHT){
						IOWR_16DIRECT(pixel_buffer->back_buffer_start_address,addr, luigi_right[j][i]);}
					else if(p[pNumber].dir == LEFT){
						IOWR_16DIRECT(pixel_buffer->back_buffer_start_address,addr, luigi_left[j][i]);}
				}
			}
			break;
	}
	if(turn == pNumber){
		int deg = p[pNumber].deg;
		int t_startX = x + TANK_LENGTH/2 + getTurretWidth(deg)*2/3;
		int t_startY = y + TANK_HEIGHT/2 - getTurretHeight(deg)*2/3;
		int t_endX = x + TANK_LENGTH/2 + getTurretWidth(deg);
		int t_endY = y + TANK_HEIGHT/2 - getTurretHeight(deg);

		alt_up_pixel_buffer_dma_draw_line(pixel_buffer,t_startX,t_startY,t_endX,t_endY, colour, 1);
	}
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

void drawTest(){
	int i,j;
	for(j = 0; j < HYRULE_HEIGHT ; j++){
		for(i = 0; i < HYRULE_WIDTH ; i++){
			alt_up_pixel_buffer_dma_draw(pixel_buffer,hyrule[j][i],i,j);
		}
	}

}

