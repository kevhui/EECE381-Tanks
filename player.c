/*
 * player.c
 *
 *	Created: 2014-01-23
 *		Author: Brittaney Geisler, Isaac Cheng, Kelvin Au, Kevin Hui
 */

#include "player.h"

//Initialises the player by the passed in arguments
void initPlayer(int id, int x, int y, int deg, int hp, int colour, int points,
		int alive, int gas, int dir) {
	p[id].x = x;
	p[id].y = y;
	p[id].deg = deg;
	p[id].hp = hp;
	p[id].colour = colour;
	p[id].points = points;
	p[id].alive = alive;
	p[id].gas = gas;
	p[id].dir = dir;

}

//moves the specified player one unit left if possible
void moveLeft(int pNumber) {
	p[pNumber].dir = LEFT;
	int new_x = p[pNumber].x - 1;
	if ( new_x >= 0 && field[new_x] > p[pNumber].y + TANK_HEIGHT){
		p[pNumber].x -= 1;
	}
	else if ( new_x >= 0 && field[new_x] == p[pNumber].y + TANK_HEIGHT ){
		p[pNumber].x -= 1;
		p[pNumber].y -= 1;
	}
	else if ( new_x >= 0 && field[new_x] == p[pNumber].y + TANK_HEIGHT - 1){
		p[pNumber].x -= 1;
		p[pNumber].y -= 2;
	}
}

//moves the specified player one unit right if possible
void moveRight(int pNumber) {
	p[pNumber].dir = RIGHT;
	int new_x = p[pNumber].x + TANK_LENGTH;
	if ( new_x < SCREEN_WIDTH && field[new_x] > p[pNumber].y + TANK_HEIGHT ){
		p[pNumber].x += 1;
	}
	else if ( new_x < SCREEN_WIDTH && field[new_x] == p[pNumber].y + TANK_HEIGHT ){
		p[pNumber].x += 1;
		p[pNumber].y -= 1;
	}
	else if ( new_x < SCREEN_WIDTH && field[new_x] == p[pNumber].y + TANK_HEIGHT - 1){
		p[pNumber].x += 1;
		p[pNumber].y -= 2;
	}
}

//TODO: bullet should have a hit radius of 1-2 pixels
//TODO: bullets need to explode
//Fires the bullet and checks for collision and updates field array accordingly
void turretFire(int turn, int power) {
	struct bullet b;
	int i;
	int bullet_alive = 1;
	int screenX, screenY;
	int turret_start_x = p[turn].x + TANK_LENGTH/2 + getTurretWidth(p[turn].deg);
	int turret_start_y = p[turn].y + TANK_HEIGHT/2 - getTurretHeight(p[turn].deg);
	b.x = (turret_start_x) * PIXEL_SCALE;
	b.y = (turret_start_y) * PIXEL_SCALE;
	b.dx = (turret_start_x - (p[turn].x + TANK_LENGTH / 2)) * power;
	b.dy = (turret_start_y - (p[turn].y)) * power;
	//printf("\tstart_x: %i\tx = %i\tdx = %i\tsin(deg)= %i",turret_start_x,b.x,b.dx,sin(p[turn].deg * M_PI) / 180);
	//printf("\tstart_y: %i\ty = %i\tdy = %i",turret_start_y,b.y,b.dy);

	do {
		//b.dx += wind
		b.dy -= GRAVITY;
		b.x += b.dx;
		b.y += b.dy;

		clearScreen();
		//TODO: loop through alive players
		for (i = 0; i < numPlayers; ++i) {
			updatePlayer(i);
		}
		updateBullet(b.x / PIXEL_SCALE, b.y / PIXEL_SCALE);
		updateField();
		updateScreen();


		screenX = b.x / PIXEL_SCALE;
		screenY = b.y / PIXEL_SCALE;
		//printf("field[x]:%i \t bullet y: %i \n",field[screenX],screenY);
		//printf("b.x:%i \t b.y: %i ",b.x,b.y);
		//printf("x:%i \t y: %i ",screenX,screenY);
		//printf("dx:%i dy:%i \n",b.dx,b.dy);
		if (getHitPlayer(screenX, screenY, 2)) {
			bullet_alive = 0;
			bulletExplode(screenX, screenY, 1);
		} else if (getHitGround(screenX, screenY, 2)) {
			bullet_alive = 0;
			bulletExplode(screenX, screenY, 1);
			field[screenX] = field[screenX] + 1;
			printf("hit ground!\n");
		}

	} while (bullet_alive);
}

//Rotates the turret of given player by one unit clock wise
void turretCW(int pNumber) {
	if(p[pNumber].deg + 3 < 90){
	p[pNumber].deg = p[pNumber].deg + 3;
	}
}

//Rotates the turret of given player by one unit counter clock wise
void turretCCW(int pNumber) {
	if(p[pNumber].deg + 3 > -90){
	p[pNumber].deg = p[pNumber].deg - 3;
	}
}

//get the length of "run" of the turret
int getTurretWidth(int degree) {
	return TURRET_LENGTH * sin((degree) * M_PI / 180);
}

//get the length of the "rise" of the turret
int getTurretHeight(int degree) {
	return TURRET_LENGTH * cos((degree) * M_PI / 180);
}

//See if the bullet hits the player with bullet
//TODO: decide the hit radius or hit rectangle of bullet
//It is currently a square bullet
int getHitPlayer(int x, int y, int hitBoxLength) {
	int i;

	for (i = 0; i < numPlayers; i++) {
		if (x > p[i].x - hitBoxLength && x < p[i].x + TANK_LENGTH - 1
				+ hitBoxLength && y > p[i].y - hitBoxLength && y < p[i].y
				+ TANK_HEIGHT + hitBoxLength) {
			printf("hit player %i!\n", i);
			return 1;
		}
	}
	return 0;

}

int getHitGround(int x, int y, int bulletType) {
	if (y >= field[x] - 1) {
		printf("hit ground!\n");
		return 1;
	}
	return 0;
}

void bulletExplode(int x, int y, int bulletType) {
	int r, i, colour, offset, pNumber;
	volatile int c = 2;
	switch (bulletType) {
	case 1:
		r = 8;//set the radius of the bullet
		colour = 0xF7FD;
		//Remove pixels from the field
		for (i = -r; i <= r; i++) {
			offset = sqrt(r * r - i * i);
			if (field[x + i] < y + offset) {
				//printf("y;%i \t field[x+i]: %i \ty-field[x+i]:%i \t offset:%i\t min: %i",	y,field[x + i],y - field[x + i],offset,(((y - field[x + i]) < offset) ? (y - field[x + i]): offset));
				field[x + i] = (y + offset - field[x + i] < 2 * offset) ? y + offset : field[x + i] + 2 * offset;
				//printf("\t newfield[x]:%i \n", field[x + i]);
			}
		}
		//See if player got hit
		int j; //explosion_y
		int hit;
		for(pNumber = 0; pNumber < numPlayers; pNumber++){
		//TODO: got thought alive players only
			hit = 0;
			for (i = -r; i <= r && hit==0; i++) {
				offset = sqrt(r * r - i * i);
				if( x+i >= p[pNumber].x && x+i <= p[pNumber].x + TANK_LENGTH - 1){
					for(j = y - offset; j <= y + offset && hit == 0; j++){
						if(j > p[pNumber].y && j < p[pNumber].y + TANK_HEIGHT){
							hit = 1;
							printf("Explosion HIT");
							break;
						}
					}
				}
			}
			if (hit == 1){
				p[pNumber].hp--;
			}
		}

		//Draw the explosion
		for (c = 0; c < 25; c += 1) {
			for (i = -r; i <= r; i++) {
				offset = sqrt(r * r - i * i);
				updateExplosion(x + i, y, offset, colour + c);
			}
		updateScreen();
		}
		break;
	}
}

//checks and updates where the tank needs to fall
void checkPlayerFalling(int pNumber){
	int i;
	int TankNotTouchGroundCounter = 0;

	for ( i = p[pNumber].x; i <= p[pNumber].x + TANK_LENGTH; i++){
		if(field[i] > p[pNumber].y + TANK_HEIGHT){
			TankNotTouchGroundCounter++;
		}
	}
	//printf("TankNotTouchGroundCounter: %i\n", TankNotTouchGroundCounter);
	if( TankNotTouchGroundCounter == TANK_LENGTH + 1){
		p[pNumber].y++;
	}
}


