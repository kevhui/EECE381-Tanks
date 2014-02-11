/*
 * ai.c
 *
 *	Created: 2014-01-18
 *		Author: Brittaney Geisler, Isaac Cheng, Kelvin Au, Kevin Hui
 */

#include "ai.h"

void ai(void){
	int target, peak;

	target = findClosest();
	peak = findPeak(target);

}


int findClosest(){
	int min = 500;
	int minID, id;
	for(id = 0; id < numPlayers; id++){
		if(turn == id){continue;}
		else
			if(pythag(id) < min){
				minID = id;
			}
			else
				continue;
	}
	return minID;
}

int pythag(int id){
	int a,b,c;
	a = p[id].x - p[turn].x;
	b = p[id].y - p[turn].y;
	c = sqrt((a*a) + (b*b));
	return c;
}

int findPeak(int id){
	int i, j;
	int pStart = p[id].x > p[turn].x ? p[turn].x : p[id].x;
	int diff = p[id].x > p[turn].x ? p[id].x - pStart : p[turn].x - pStart;
	for (i = pStart; i < diff; i++){
		for(j = SCREEN_HEIGHT; j = 0; j--){
			if(map[j][i] == NOTHING){
				peaks[0] = i;
				peaks[1] = j;
				break;
			}
		}
	}
	return peaks[0];
}

void aiFire(int target, int turn, int power, int fire){
	struct bullet b;
	int i;
	int bullet_alive = 1;
	int screenX, screenY;
	int turret_start_x = p[turn].x + TANK_LENGTH / 2 + getTurretWidth(
			p[turn].deg * p[turn].dir);
	int turret_start_y = p[turn].y + TANK_HEIGHT / 2 - getTurretHeight(
			p[turn].deg * p[turn].dir);
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

		//clearScreen();
		//TODO: loop through alive players
		//updateField();
		if(fire){
			for (i = 0; i < numPlayers; ++i) {
				updatePlayer(i);
			}
			updateBullet(b.x / PIXEL_SCALE, b.y / PIXEL_SCALE);
			updateScreen();
		}


		screenX = b.x / PIXEL_SCALE;
		screenY = b.y / PIXEL_SCALE;
		//printf("field[x]:%i \t bullet y: %i \n",field[screenX],screenY);
		//printf("b.x:%i \t b.y: %i ",b.x,b.y);
		//printf("x:%i \t y: %i ",screenX,screenY);
		//printf("dx:%i dy:%i \n",b.dx,b.dy);
		if (getHitPlayer(screenX, screenY, 2)) {
			bullet_alive = 0;
			if(fire){
				bulletExplode(screenX, screenY, 1);
			}
		} else if (getHitGround(screenX, screenY, 2)) {
			bullet_alive = 0;
			if(fire){
				bulletExplode(screenX, screenY, 1);
				field[screenX] = field[screenX] + 1;
				printf("hit ground!\n");
			}
		} else if (screenX >= SCREEN_WIDTH - 1 || screenX <= 0 || screenY
				>= SCREEN_HEIGHT - 1) {
			bullet_alive = 0;
		}
	} while (bullet_alive);
}
