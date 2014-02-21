/*
 * ai.c
 *
 *	Created: 2014-01-18
 *		Author: Brittaney Geisler, Isaac Cheng, Kelvin Au, Kevin Hui
 */

#include "ai.h"
#include "player.h"
#include "screen.h"

void aiMain(int turn) {
	// check if ai is hit, if so, move out of the way
	if (p[turn].ai.isHit) {
		p[turn].ai.turnLock = 1;
		p[turn].ai.offset = 0;
		p[turn].ai.offshoot = 1;
		aiMove(p[turn].ai.hitBy);
		p[turn].ai.isHit = FALSE;
	}
	
	// if the ai does not have a target, set the closest player as the target
	if (!(p[turn].ai.hasTarget)) {
		p[turn].ai.target = findClosest();
		p[turn].ai.hasTarget = TRUE;
		p[turn].ai.turnLock = 1;
		p[turn].ai.offset = 0;
		p[turn].ai.offshoot = 1;
		
	// if the ai's current target is not the closest, change targets
	} else if (p[turn].ai.target != findClosest()) {
		p[turn].ai.target = findClosest();
		p[turn].ai.hasTarget = TRUE;
		p[turn].ai.turnLock = 1;
		p[turn].ai.offset = 0;
		p[turn].ai.offshoot = 1;
	}
	//	if (p[p[turn].ai.target].moved) {
	//		p[turn].ai.turnLock = 1;
	//		p[turn].ai.offset = 0;
	//		p[turn].ai.offshoot = 1;
	//	}

	//printf("target: %i\n", p[turn].ai.target);
	p[turn].ai.checkNum = 0;
	p[turn].ai.fire = 0;

	aiFire(p[turn].ai.target, turn, 80); // find ai's shot

	p[turn].ai.turnLock++;
}

int findClosest() {
	int min = 500;
	int minID, id;
	for (id = 0; id < numPlayers; id++) {
		if (turn != id) {
			if (pythag(id) < min) {
				minID = id; // set the closest player as the one closest to the current player
			}
		}
	}
	return minID;
}

// returns distance of a player from another player
int pythag(int id) {
	int a, b, c;
	a = p[id].x - p[turn].x; // x coord of target - x coord of player
	b = p[id].y - p[turn].y; // y coord of targe - y coord of player
	c = sqrt((a * a) + (b * b)); // pythag (c^2 = a^2 + b^2)
	return c;
}

// returns distance of a bullet from a player
int bPythag(int id, int screenX, int screenY) {
	int a, b, c;
	a = (p[id].x + TANK_LENGTH / 2) - screenX; // x coord of player - x coord of bullet
	b = (p[id].y + TANK_LENGTH / 2) - screenY; // y coord of player - y coord of bullet
	c = sqrt((a * a) + (b * b)); // pythag
	return c;
}

//int findPeak(int id) {
//	int i, j;
//	int pStart = p[id].x > p[turn].x ? p[turn].x : p[id].x;
//	int diff = p[id].x > p[turn].x ? p[id].x - pStart : p[turn].x - pStart;
//	for (i = pStart; i < diff; i++) {
//		for (j = SCREEN_HEIGHT; j == 0; j--) {
//			if (map[j][i] == NOTHING) {
//				peaks[0] = i;
//				peaks[1] = j;
//				break;
//			}
//		}
//	}
//	return peaks[0];
//}

// returns the direction of the player's target
int targetDir(int target) {
	if (p[target].x > p[turn].x) {
		return RIGHT;
	} else
		return LEFT;
}

// returns recursively. Does not render the bullet until p[turn].ai.fire == TRUE
int aiFire(int target, int turn, int power) {
	struct bullet b;
	int i;
	int bullet_alive = 1;
	int screenX, screenY;

	int tDir = targetDir(target);
	p[turn].dir = tDir;
	if (p[turn].ai.checkNum > 9) { // if number of checks exceeds limit, fire the bullet that landed closest to the target
		p[turn].ai.checkNum = 0;
		p[turn].ai.fire = 1;
		return aiFire(target, turn, power);
	}

	if (p[turn].ai.fire == TRUE) { // set angles to angle resulting in closest shot
		p[turn].deg = p[turn].ai.offshoot * ((12 / p[turn].ai.turnLock)
				* p[turn].ai.closest[0]) + p[turn].ai.offset + 10;
	} else // else set angle to next iteration
		p[turn].deg = p[turn].ai.offshoot * ((12 / p[turn].ai.turnLock)
				* p[turn].ai.checkNum) + p[turn].ai.offset + 10;

	int turret_start_x = p[turn].x + TANK_LENGTH / 2 + getTurretWidth(
			p[turn].deg * tDir);
	int turret_start_y = p[turn].y + TANK_HEIGHT / 2 - getTurretHeight(
			p[turn].deg * tDir);
	b.x = (turret_start_x) * PIXEL_SCALE;
	b.y = (turret_start_y) * PIXEL_SCALE;
	b.dx = (getTurretWidth(p[turn].deg * tDir)) * power;
	b.dy = -(getTurretHeight(p[turn].deg * tDir)) * power;
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


		if (p[turn].ai.fire) { // if p[turn].ai.fire == TRUE, render bullet
			undrawPlayers();
			for (i = 0; i < numPlayers; ++i) {
				updatePlayer(i);
			}
			undrawBullet((b.x - b.dx) / PIXEL_SCALE, (b.y - b.dy) / PIXEL_SCALE);
			updateBullet(b.x / PIXEL_SCALE, b.y / PIXEL_SCALE);
			updateScreen();
		}

		screenX = b.x / PIXEL_SCALE;
		screenY = b.y / PIXEL_SCALE;
		//printf("field[x]:%i \t bullet y: %i \n",field[screenX],screenY);
		//printf("b.x:%i \t b.y: %i ",b.x,b.y);
		//printf("x:%i \t y: %i ",screenX,screenY);
		//printf("dx:%i dy:%i \n",b.dx,b.dy);
		
		// if the bullet hits a player
		if (getHitPlayer(screenX, screenY, 2)) {
			bullet_alive = 0;
			if (p[turn].ai.fire) { // if fire == true, render explosion
				bulletExplode(screenX, screenY, 1);
				p[turn].ai.offset = abs(p[turn].deg);
				p[turn].ai.closest[0] = p[turn].ai.checkNum;
				p[turn].ai.closest[1] = bPythag(p[turn].ai.target, screenX,
						screenY);
				printf("offset: %i\npower: %i\nturnLock: %i\noffshoot: %i\n",
						p[turn].ai.offset, power, p[turn].ai.turnLock,
						p[turn].ai.offshoot);
				return 1;
			}
			p[turn].ai.fire = 1;
			return aiFire(target, turn, power); // return this angle and render the bullet
			
		// if the bullet hits the ground
		} else if (getHitGround(screenX, screenY, 2)) {
			bullet_alive = 0;
			if (p[turn].ai.fire) { // render explosion if fire == true
				bulletExplode(screenX, screenY, 1);
				field[screenX] = field[screenX] + 1;
				printf("hit ground!\n");
				p[turn].ai.offset = abs(p[turn].deg);
				printf("offset: %i\npower: %i\nturnLock: %i\noffshoot: %i\n",
						p[turn].ai.offset, power, p[turn].ai.turnLock,
						p[turn].ai.offshoot);
				if (tDir == RIGHT) { // if target is to the right of player
					p[turn].ai.offshoot = p[target].x > screenX ? LEFT : RIGHT; // if bullet lands left of target, set offshoot to left, else right
				} else if (tDir == LEFT) { // if target is to the left of player
					p[turn].ai.offshoot = p[target].x < screenX ? LEFT : RIGHT; // if bullet lands right of target, set offshoot to left, else right
				}

				return 1;
			}
			if (p[turn].ai.checkNum == 0) { // if first shot of the turn, set this shot as closest and save distance in closest[1]
				p[turn].ai.closest[1] = bPythag(p[turn].ai.target, screenX,
						screenY);
				p[turn].ai.closest[0] = p[turn].ai.checkNum;
			}
			if (bPythag(p[turn].ai.target, screenX, screenY)
					< p[turn].ai.closest[1]) { // if the distance is less than the one stored in closest[1], save this shot as new closest shot
				p[turn].ai.closest[0] = p[turn].ai.checkNum;
				p[turn].ai.closest[1] = bPythag(p[turn].ai.target, screenX,
						screenY);
			}
			p[turn].ai.checkNum++;
			return aiFire(target, turn, power);
			
		// if the bullet hits the screen, return the function for the next iteration
		} else if (screenX >= SCREEN_WIDTH - 1 || screenX <= 0 || screenY
				>= SCREEN_HEIGHT - 1) {
			undrawBullet((b.x - b.dx) / PIXEL_SCALE, (b.y - b.dy) / PIXEL_SCALE);
			bullet_alive = 0;
			p[turn].ai.checkNum++;
			return aiFire(target, turn, power);
		}
	} while (bullet_alive);
	return 0;
}

//if the ai is hit by another player, move in a direction (can be set closer or futher from a player)
void aiMove(int hitBy) {
	int steps;
	int i;
	int dir = targetDir(hitBy);
	for (steps = 0; steps < 15; steps++) { // move 15 steps towards target
		undrawPlayers();
		if (dir == RIGHT) {
			moveRight(turn);
		} else
			moveLeft(turn);
		for (i = 0; i < numPlayers; i++) { // draw movement
			if (p[i].alive) {
				updatePlayer(i);
			}
		}
		updateScreen();
	}

	// check if movement happens over empty space, render falling
	int fallFlag = 1;
	while (fallFlag == 1) {
		fallFlag = 0;
		checkPlayerFalling(turn);
		if (p[turn].isFalling) {
			undrawPlayer(turn);
			updatePlayer(turn);
			fallFlag = 1;
			updateScreen();
			//checkPlayerFalling(i);
		}
	}

}
