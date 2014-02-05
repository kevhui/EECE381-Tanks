/*
 * menu.c
 *
 *  Created on: 2014-02-03
 *      Author: Kevin
 */

#include "menu.h"

void initState0(){
	  printString("TANKS", 36, 10);
	  printString("NUMBER OF PLAYERS:", 15, 20);
	  printString("2", 22, 24);
	  printString("(press left and right",14,28);
	  printString("arrows to change)",16,30);
	  printString("PRESS SPACE", 33, 50);
	  printString("CONTROLS:", 45, 20);
	  printString("KEY(3) AND KEY(2) : MOVE TANK", 45, 24);
	  printString("SW(1) AND SW(0) : TILT GUN",45, 28);
	  //printString("PGUP AND PGDOWN : CHANGE POWER",45, 32);
	  //printString("W : CHANGE WEAPON",45, 36);
	  printString("KEY(1) : FIRE",45, 32);
	  updateScreen();
}

void initState1(int playernum){
		  clearCharBuffer();
		  clearScreen();
		  printString("TANKS", 36, 10);
		  printString("Player #", 33, 14);
		  if (playernum==1) printString("1",42,14);
		  else if (playernum==2) printString("2",42,14);
		  else if (playernum==3) printString("3",42,14);
		  else if (playernum==4) printString("4",42,14);
		  //print player number
		  printString("ENTER NAME: ",14,20);
		  printString("CHANGE COLOR: ",14,24);
		  printString("PINK",28,24);//default
		  //print player color
		  printString("SELECT PLAYER TYPE: ", 14, 28);
		  printString("COMP",34,28);//default
		  //print player type
		  printString("PRESS SPACE TO START", 25, 50);
		  updateScreen();
}


