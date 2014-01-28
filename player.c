/*
 * player.c
 *
 *	Created: 2014-01-23
 *		Author: Brittaney Geisler, Isaac Cheng, Kelvin Au, Kevin Hui
 */

#include "player.h"


//Initialises the player by the passed in arguments
void initPlayer(int id, int x,int y,int deg,int hp,int colour, int points, int alive, int gas){
	p[id].x = x;
	p[id].y = y;
	p[id].deg = deg;
	p[id].hp = hp;
	p[id].colour = colour;
	p[id].points = points;
	p[id].alive = alive;
	p[id].gas = gas;

	int i,j;
	for(j = p[id].y - TANK_HEIGHT; j < p[id].y; j++){
		for(i = p[id].x; i < p[id].x + TANK_HEIGHT; i++){
				field[j][i] = id;
				//printf("x: %i y:%i id:%i \n",i,j,playerID);
			}
	}

}

//moves the specified player one unit left
void moveLeft(int playerNumber){
	if(p[playerNumber].x-1  >= 0)
		p[playerNumber].x--;
}

//moves the specified player one unit right
void moveRight(int playerNumber){
	if(p[playerNumber].x+1 < SCREEN_WIDTH)
		p[playerNumber].x++;
}

//TODO: bullet should have a hit radius of 1-2 pixels
//TODO: bullets need to explode
//Fires the bullet and checks for collision and updates field array accordingly
void turretFire(int turn, int power){
	struct bullet b;
	int i;
	int bullet_alive = 1;
	int screenX, screenY;
	int turret_start_x = p[turn].x + TANK_LENGTH/2 + getTurretWidth(p[turn].deg);
	int turret_start_y = p[turn].y - getTurretHeight(p[turn].deg);
	b.x = (turret_start_x)*PIXEL_SCALE;
	b.y = (turret_start_y)*PIXEL_SCALE;
	b.dx = (turret_start_x-(p[turn].x+TANK_LENGTH/2))*power;
	b.dy = (turret_start_y-(p[turn].y))*power;
	//printf("\tstart_x: %i\tx = %i\tdx = %i\tsin(deg)= %i",turret_start_x,b.x,b.dx,sin(p[turn].deg * M_PI) / 180);
	//printf("\tstart_y: %i\ty = %i\tdy = %i",turret_start_y,b.y,b.dy);

	do{
		//b.dx += wind
		b.dy -= GRAVITY;
		b.x+= b.dx;
		b.y+= b.dy;

		clearScreen();
		for (i = 0; i < numPlayers; ++i) {
			updatePlayer(p[i].x,p[i].y,p[i].deg,p[i].colour);
		}
		updateBullet(b.x/PIXEL_SCALE, b.y/PIXEL_SCALE);
		updateField();
		updateScreen();

		screenX = b.x/PIXEL_SCALE;
		screenY = b.y/PIXEL_SCALE;

		if(field[screenY][screenX] < numPlayers){
			bullet_alive = 0;
			printf("hit player %i!\n",field[screenY][screenX]);
		}
		else if(field[screenY][screenX] == GROUND){
			bullet_alive = 0;
			field[screenY][screenX] = NOTHING;
			printf("hit ground!\n");
		}

	}while(bullet_alive);
}

//Rotates the turret of given player by one unit clock wise
void turretCW(int playerNumber){
	p[playerNumber].deg = (p[playerNumber].deg + 2) % 360;
}

//Rotates the turret of given player by one unit counter clock wise
void turretCCW(int playerNumber) {
	p[playerNumber].deg = (p[playerNumber].deg - 2) % 360;
}

//get the length of "run" of the turret
int getTurretWidth(int degree){
	return TURRET_LENGTH * sin((degree) * M_PI / 180);
}

//get the length of the "rise" of the turret
int getTurretHeight(int degree){
	return TURRET_LENGTH * cos((degree) * M_PI / 180);
}

