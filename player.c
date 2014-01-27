/*
 * player.c
 *
 *	Created: 2014-01-23
 *		Author: Brittaney Geisler, Isaac Cheng, Kelvin Au, Kevin Hui
 */

#include "player.h"


void moveLeft(int playerNumber){
	p[playerNumber].x--;
}
void moveRight(int playerNumber){
	p[playerNumber].x++;
}
void turretFire(int turn, int power){
	struct bullet b;
	int i;
	int turret_start_x = p[turn].x + TANK_LENGTH/2 + TURRET_LENGTH * sin((p[turn].deg * M_PI) / 180);
	int turret_start_y = p[turn].y - TANK_HEIGHT - TURRET_LENGTH * cos((p[turn].deg * M_PI) / 180);
	b.x = (turret_start_x)*PIXEL_SCALE;
	b.y = (turret_start_y)*PIXEL_SCALE;
	b.dx = (turret_start_x-(p[turn].x+TANK_LENGTH/2))*power;
	b.dy = (turret_start_y-(p[turn].y-TANK_HEIGHT))*power;
	//printf("\tstart_x: %i\tx = %i\tdx = %i\tsin(deg)= %i",turret_start_x,b.x,b.dx,sin(p[turn].deg * M_PI) / 180);
	//printf("\tstart_y: %i\ty = %i\tdy = %i",turret_start_y,b.y,b.dy);

	while(*switches != 4){
	//b.dx += wind
	b.dy -= GRAVITY;
	b.x+= b.dx;
	b.y+= b.dy;

	clearScreen();
	updateField();
	for (i = 0; i < numPlayers; ++i) {
		updatePlayer(p[i].x,p[i].y,p[i].deg,p[i].colour);
	}
	updateBullet(b.x/PIXEL_SCALE, b.y/PIXEL_SCALE);
	updateScreen();
	}


}
void turretCW(int playerNumber){
	p[playerNumber].deg = (p[playerNumber].deg + 2) % 360;
}
void turretCCW(int playerNumber) {
	p[playerNumber].deg = (p[playerNumber].deg - 2) % 360;
}
