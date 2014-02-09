/*
 * menu.h
 *
 *  Created on: 2014-02-03
 *      Author: Kevin
 */

#ifndef MENU_H_
#define MENU_H_

#include "screen.h"
#include "altera_up_ps2_keyboard.h"
#include "altera_up_avalon_ps2.h"
#include "nios2_ctrl_reg_macros.h"
#include <string.h>

extern volatile int state;

void initState0(void);//initializes the first menu screen
void initState1(int);//initializes the second menu screen
void AdjustChar();//change character on screen
void Name_Entered(char *);//player name entered handler
void clean_up(void);//clean up game variables etc. (reset basically)
void clearPlayerName(void);//clears all player names
void printPlayerStruct(int);//test for player struct
void updateNumPlayers(); //updates the number of players for screen0
void state_0(int, alt_8);//state_0 logic
void state_1(int, alt_8, char);//state_0 logic

#endif /* MENU_H_ */
