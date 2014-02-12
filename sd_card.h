/*
 * sd_card.h
 *
 *	Created: 2014-01-18
 *		Author: Brittaney Geisler, Isaac Cheng, Kelvin Au, Kevin Hui
 */
#ifndef SD_CARD
#define SD_CARD
#include <altera_up_sd_card_avalon_interface.h>
#include <stdio.h>
#include <system.h>
#include <string.h>
#include <stdlib.h>
#define SCORE_BUFFER_SIZE 512
#define MAX_CHARACTER_OF_NAME 50
#define MAX_CHARACTER_OF_SCORE 3
#define SCORE_NAME "score.xml"

typedef struct score{
	char* name;
	char* score;
} score;

void initSD(void);
void printSD(void);
void writeSD(char[],int);
void setPositionToEnd(short int);
int getAllScore(score[]);
int getPersonalScore(score[],int[],char*);
int cmp_func(const void *a,const void *b);
void getMax10Score(score[],score[]);
void appendCharacter(char* , char );
void convertInt(char[],int);

#endif
