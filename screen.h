/*
 * vga.h
 *
 *	Created: 2014-01-18
 *		Author: Brittaney Geisler, Isaac Cheng, Kelvin Au, Kevin Hui
 */

#ifndef SCREEN_FUNCTIONS
#define SCREEN_FUNCTIONS

#include <altera_up_avalon_video_character_buffer_with_dma.h>
#include <altera_up_avalon_video_pixel_buffer_dma.h>
#include <altera_up_avalon_video_character_buffer_with_dma_regs.h>
#include <stdlib.h>
#include <stdio.h>
#include <system.h>
#include <math.h>
#include "values.h"
#include "player.h"

void initScreen(void);
void clearScreen(void);
void updateScreen(void);
void updateField(void);
void updatePlayer(int,int,int,int);
void updateBullet(int,int);
void printLines(void);
void printString(void);

#endif
