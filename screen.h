/*
 * screen.h
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
#include "field.h"
#include "images.h"
#include "images_bars.h"
#include "sd_card.h"

void initScreen(void); //Initialise screen
void initCharBuffer(void); //Initialise char buffer
void clearScreen(void); //Clears screen
void updateScreen(void); //Swaps buffers
void undrawPlayers(void); //updates the players
void undrawBullet(int,int);
void updateField(void); //updates the field
void updatePlayer(int); //updates the players
void updateBullet(int, int); //updates the bullet
void updateExplosion(int, int, int, int); //update the explosion
void printLines(void); //draw lines
void printString(char*, int, int); //print string
void printTimer(int); //print string
void printHp(int); //print hp
void drawTest(void); //testing drawing
void clearCharBuffer(void); //clear char buffer
void fastPixel(int, int, int); //draws a single pixel to screen
void drawName(char*,char*,char*,char*);
void drawTest(void);
void drawHealth(int,int,int,int);
void drawGas(int);
void drawPower(int);
//void drawBullet(int);
//void drawWindIndicator(int);

void displayHighScore(char *,char *,char *,char *);


#endif
