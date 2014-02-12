/*
 * player.c
 *
 *	Created: 2014-01-23
 *		Author: Brittaney Geisler, Isaac Cheng, Kelvin Au, Kevin Hui
 */

#include "player.h"

void initPlayer(int id, int character, char *name, int hp, int gas, int type) {
	switch (id) {
	case pOne:
		p[id].x = 50;
		p[id].y = SCREEN_HEIGHT / 2;
		break;
	case pTwo:
		p[id].x = SCREEN_WIDTH * 3 / 4;
		p[id].y = SCREEN_HEIGHT / 2;
		break;
	case pThree:
		p[id].x = 150;
		p[id].y = SCREEN_HEIGHT / 2;
		break;
	case pFour:
		p[id].x = 200;
		p[id].y = SCREEN_HEIGHT / 2;
		break;
	}

	printf("init player %i with character %i", id, character);
	switch (character) {
	case MARIO:
		p[id].colour = 0x4800;
		break;
	case LUIGI:
		p[id].colour = 0x4648;
		break;
	}

	//these can be fixed
	p[id].deg = 90;
	p[id].points = 0;
	p[id].alive = ALIVE;
	p[id].dir = RIGHT;
	p[id].type = type;
	p[id].character = character;//0=MARIO//1=LUIGI
	strcpy((p[id].name), name);
	p[id].isFalling = TRUE;

	//TODO:these should be adjustable
	//TODO: more than 3 hp start
	p[id].hp = hp; //game options
	p[id].gas = gas; //gas
	p[id].power = 50;

}

//moves the specified player one unit left if possible
void moveLeft(int id) {
	p[id].dir = LEFT;
	int new_x = p[id].x - 1;
	int end_y = p[id].y + TANK_HEIGHT - 1;
	int j;
	int counter = 0;
	for (j = p[id].y; j < p[id].y + TANK_HEIGHT - 3; j++) {
		if (map[j][new_x] == NOTHING) {
			counter++;
		}
	}
	//printf("counter %i",counter);
	if (counter == TANK_HEIGHT - 3) {
		if (new_x >= 0) {
			if ((map[end_y][new_x] == NOTHING) && (map[end_y - 1][new_x]
					== NOTHING) && (map[end_y - 2][new_x] == NOTHING)) {
				p[id].x -= 1;
				p[id].gas--;
			} else if ((map[end_y - 1][new_x] == NOTHING)
					&& (map[end_y - 2][new_x] == NOTHING)) {
				p[id].x -= 1;
				p[id].y -= 1;
				p[id].gas--;
			} else if ((map[end_y - 2][new_x] == NOTHING)) {
				p[id].x -= 1;
				p[id].y -= 2;
				p[id].gas--;
			}
		}
	}
}

//moves the specified player one unit right if possible
void moveRight(int id) {
	p[id].dir = RIGHT;
	int new_x = p[id].x + TANK_LENGTH;
	int end_y = p[id].y + TANK_HEIGHT - 1;
	int j;
	int counter = 0;
	for (j = p[id].y; j < p[id].y + TANK_HEIGHT - 3; j++) {
		if (map[j][new_x] == NOTHING) {
			counter++;
		}
	}
	//printf("counter %i",counter);
	if (counter == TANK_HEIGHT - 3) {
		if (new_x < SCREEN_WIDTH) {
			if ((map[end_y][new_x] == NOTHING) && (map[end_y - 1][new_x]
					== NOTHING) && (map[end_y - 2][new_x] == NOTHING)) {
				p[id].x += 1;
				p[id].gas--;
			} else if ((map[end_y - 1][new_x] == NOTHING)
					&& (map[end_y - 2][new_x] == NOTHING)) {
				p[id].x += 1;
				p[id].y -= 1;
				p[id].gas--;
				//printf("two");
			} else if ((map[end_y - 2][new_x] == NOTHING)) {
				p[id].x += 1;
				p[id].y -= 2;
				p[id].gas--;
			}
		}
	}
}

//Fires the bullet and checks for collision and updates field array accordingly
void turretFire(int turn, int power, int wind, int bulletType) {
	if (bulletType == 0) {
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
		b.dx = (getTurretWidth(p[turn].deg * p[turn].dir)) * power;
		b.dy = -(getTurretHeight(p[turn].deg * p[turn].dir)) * power;
		//printf("\tstart_x: %i\tx = %i\tdx = %i\tsin(deg)= %i",turret_start_x,b.x,b.dx,sin(p[turn].deg * M_PI) / 180);
		//printf("\tstart_y: %i\ty = %i\tdy = %i",turret_start_y,b.y,b.dy);

		do {
			b.dx += wind;
			b.dy -= GRAVITY;
			b.x += b.dx;
			b.y += b.dy;

			//clearScreen();
			//updateField();
			for (i = 0; i < numPlayers; ++i) {
				if (p[i].alive)
					updatePlayer(i);
			}
			undrawBullet(b.x / PIXEL_SCALE, b.y / PIXEL_SCALE);
			updateBullet(b.x / PIXEL_SCALE, b.y / PIXEL_SCALE);
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
			} else if (screenX >= SCREEN_WIDTH - 1 || screenX <= 0 || screenY
					>= SCREEN_HEIGHT - 1) {
				undrawBullet((b.x - b.dx) / PIXEL_SCALE,
						(b.y - b.dy) / PIXEL_SCALE);
				updateScreen();
				undrawBullet((b.x - b.dx) / PIXEL_SCALE,
						(b.y - b.dy) / PIXEL_SCALE);
				bullet_alive = 0;
			}
		} while (bullet_alive);
	} else if (bulletType == 1) {
		//fireBulletOne(turn, power, wind, bulletType);
	}
	else if (bulletType == 2) {
		//fireBulletTwo(turn, power, wind, bulletType);
	}

}

void fireBulletOne(int turn, int power, int wind, int bulletType) {
	int splitBullet = 0;
	struct bullet b;
	int i, id;
	int bullet_alive = 1;
	int screenX, screenY;
	int turret_start_x = p[turn].x + TANK_LENGTH / 2 + getTurretWidth(
			p[turn].deg * p[turn].dir);
	int turret_start_y = p[turn].y + TANK_HEIGHT / 2 - getTurretHeight(
			p[turn].deg * p[turn].dir);
	b.x = (turret_start_x) * PIXEL_SCALE;
	b.y = (turret_start_y) * PIXEL_SCALE;
	b.dx = (getTurretWidth(p[turn].deg * p[turn].dir)) * power;
	b.dy = -(getTurretHeight(p[turn].deg * p[turn].dir)) * power;
	//printf("\tstart_x: %i\tx = %i\tdx = %i\tsin(deg)= %i",turret_start_x,b.x,b.dx,sin(p[turn].deg * M_PI) / 180);
	//printf("\tstart_y: %i\ty = %i\tdy = %i",turret_start_y,b.y,b.dy);

	do {
		b.dx += wind;
		b.dy -= GRAVITY;
		b.x += b.dx;
		b.y += b.dy;

		if (b.dy < 10 && b.dy > -10) {
			splitBullet = 1;
			break;
		}

		//clearScreen();
		//updateField();
		for (i = 0; i < numPlayers; ++i) {
			if (p[i].alive)
				updatePlayer(i);
		}
		undrawBullet(b.x / PIXEL_SCALE, b.y / PIXEL_SCALE);
		updateBullet(b.x / PIXEL_SCALE, b.y / PIXEL_SCALE);
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
		} else if (screenX >= SCREEN_WIDTH - 1 || screenX <= 0 || screenY
				>= SCREEN_HEIGHT - 1) {
			undrawBullet((b.x - b.dx) / PIXEL_SCALE, (b.y - b.dy) / PIXEL_SCALE);
			updateScreen();
			undrawBullet((b.x - b.dx) / PIXEL_SCALE, (b.y - b.dy) / PIXEL_SCALE);
			bullet_alive = 0;
		}
	} while (bullet_alive);

	if (splitBullet == 1) {
		struct bullet sb[4];
		int i;
		int bullet_alive[4];
		bullet_alive[0] = ALIVE;
		bullet_alive[1] = ALIVE;
		bullet_alive[2] = ALIVE;
		bullet_alive[3] = ALIVE;
		int screenX[4], screenY[4];
		for (i = 0; i < 4; i++) {
			if (i == 0 || i == 1)
				sb[i].x = b.x + (i + 1) * 10 * PIXEL_SCALE;
			else
				sb[i].x = b.x + (i + 1) * 10 * PIXEL_SCALE;

			sb[i].y = b.y;
			sb[i].dx = b.dx;
			sb[i].dy = b.dy;
		}

		do {
			for (i = 0; i < 4; i++) {
				if (bullet_alive[i] == ALIVE) {
					sb[i].dx += wind;
					sb[i].dy -= GRAVITY;
					sb[i].x += sb[i].dx;
					sb[i].y += sb[i].dy;

					//clearScreen();
					//updateField();
					for (id = 0; id < numPlayers; ++id) {
						if (p[id].alive)
							updatePlayer(id);
					}
					undrawBullet(sb[i].x / PIXEL_SCALE, sb[i].y / PIXEL_SCALE);
					updateBullet(sb[i].x / PIXEL_SCALE, sb[i].y / PIXEL_SCALE);
					updateScreen();

					screenX[i] = sb[i].x / PIXEL_SCALE;
					screenY[i] = sb[i].y / PIXEL_SCALE;
					//printf("field[x]:%i \t bullet y: %i \n",field[screenX],screenY);
					//printf("b.x:%i \t b.y: %i ",b.x,b.y);
					//printf("x:%i \t y: %i ",screenX,screenY);
					//printf("dx:%i dy:%i \n",b.dx,b.dy);
					if (getHitPlayer(screenX[i], screenY[i], 2)) {
						bullet_alive[i] = DEAD;
						bulletExplode(screenX[i], screenY[i], 1);
						printf("here");
					} else if (getHitGround(screenX[i], screenY[i], 2)) {
						bullet_alive[i] = DEAD;
						bulletExplode(screenX[i], screenY[i], 1);
						field[screenX[i]] = field[screenX[i]] + 1;
						printf("hit ground!\n");
					} else if (screenX[i] >= SCREEN_WIDTH - 1 || screenX[i]
							<= 0 || screenY[i] >= SCREEN_HEIGHT - 1) {
						printf("oob");
						undrawBullet((sb[i].x - sb[i].dx) / PIXEL_SCALE,
								(sb[i].y - sb[i].dy) / PIXEL_SCALE);
						updateScreen();
						undrawBullet((sb[i].x - sb[i].dx) / PIXEL_SCALE,
								(sb[i].y - sb[i].dy) / PIXEL_SCALE);
						bullet_alive[i] = 0;
					}
				}
			}
		} while (bullet_alive[0] || bullet_alive[1] || bullet_alive[2]
				|| bullet_alive[3]);
	}
}

void fireBulletTwo(int turn, int power, int wind, int bulletType) {
	int splitBullet = 0;
	struct bullet b;
	int i, id;
	int bullet_alive = 1;
	int screenX, screenY;
	int turret_start_x = p[turn].x + TANK_LENGTH / 2 + getTurretWidth(
			p[turn].deg * p[turn].dir);
	int turret_start_y = p[turn].y + TANK_HEIGHT / 2 - getTurretHeight(
			p[turn].deg * p[turn].dir);
	b.x = (turret_start_x) * PIXEL_SCALE;
	b.y = (turret_start_y) * PIXEL_SCALE;
	b.dx = (getTurretWidth(p[turn].deg * p[turn].dir)) * power;
	b.dy = -(getTurretHeight(p[turn].deg * p[turn].dir)) * power;
	//printf("\tstart_x: %i\tx = %i\tdx = %i\tsin(deg)= %i",turret_start_x,b.x,b.dx,sin(p[turn].deg * M_PI) / 180);
	//printf("\tstart_y: %i\ty = %i\tdy = %i",turret_start_y,b.y,b.dy);

	do {
		b.dx += wind;
		b.dy -= GRAVITY;
		b.x += b.dx;
		b.y += b.dy;

		if (b.dy < 10 && b.dy > -10) {
			splitBullet = 1;
			break;
		}

		//clearScreen();
		//updateField();
		for (i = 0; i < numPlayers; ++i) {
			if (p[i].alive)
				updatePlayer(i);
		}
		undrawBullet(b.x / PIXEL_SCALE, b.y / PIXEL_SCALE);
		updateBullet(b.x / PIXEL_SCALE, b.y / PIXEL_SCALE);
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
		} else if (screenX >= SCREEN_WIDTH - 1 || screenX <= 0 || screenY
				>= SCREEN_HEIGHT - 1) {
			undrawBullet((b.x - b.dx) / PIXEL_SCALE, (b.y - b.dy) / PIXEL_SCALE);
			updateScreen();
			undrawBullet((b.x - b.dx) / PIXEL_SCALE, (b.y - b.dy) / PIXEL_SCALE);
			bullet_alive = 0;
		}
	} while (bullet_alive);
	int saved_x, saved_y, saved_dx, saved_dy;
	int bulletCount;
	if (splitBullet == 1) {
		saved_x = b.x;
		saved_y = b.y;
		saved_dx = b.dx;
		saved_dy = b.dy;
		bulletExplode(b.x,b.y,1);
		for (bulletCount = 0; bulletCount < 8; bulletCount++) {
			b.x = saved_x + rand()%(15*PIXEL_SCALE);
			b.y = saved_y;
			b.dx = rand()%(PIXEL_SCALE/3);
			b.dx = b.dx%2 == 1 ? -b.dx : b.dx;
			b.dy = saved_dy;
			bullet_alive = ALIVE;
			do {
				b.dx += wind;
				b.dy -= GRAVITY;
				b.x += b.dx;
				b.y += b.dy;

				if (b.dy < 10 && b.dy > -10) {
					splitBullet = 1;
					break;
				}

				//clearScreen();
				//updateField();
				for (i = 0; i < numPlayers; ++i) {
					if (p[i].alive)
						updatePlayer(i);
				}
				undrawBullet(b.x / PIXEL_SCALE, b.y / PIXEL_SCALE);
				updateBullet(b.x / PIXEL_SCALE, b.y / PIXEL_SCALE);
				updateScreen();

				screenX = b.x / PIXEL_SCALE;
				screenY = b.y / PIXEL_SCALE;
				//printf("field[x]:%i \t bullet y: %i \n",field[screenX],screenY);
				//printf("b.x:%i \t b.y: %i ",b.x,b.y);
				//printf("x:%i \t y: %i ",screenX,screenY);
				//printf("dx:%i dy:%i \n",b.dx,b.dy);
				bulletExplode(b.x,b.y,1);
				if (getHitPlayer(screenX, screenY, 2)) {
					bullet_alive = 0;
					bulletExplode(screenX, screenY, 2);
				} else if (getHitGround(screenX, screenY, 2)) {
					bullet_alive = 0;
					bulletExplode(screenX, screenY, 2);
					field[screenX] = field[screenX] + 1;
					printf("hit ground!\n");
				} else if (screenX >= SCREEN_WIDTH - 1 || screenX <= 0 || screenY
						>= SCREEN_HEIGHT - 1) {
					undrawBullet((b.x - b.dx) / PIXEL_SCALE, (b.y - b.dy) / PIXEL_SCALE);
					updateScreen();
					undrawBullet((b.x - b.dx) / PIXEL_SCALE, (b.y - b.dy) / PIXEL_SCALE);
					bullet_alive = 0;
				}
			} while (bullet_alive);
		}
	}

}
//Rotates the turret of given player by one unit clock wise
void turretCW(int id) {
	if (p[id].deg + 3 <= 120) {
		p[id].deg = p[id].deg + 3;
	}
}

//Rotates the turret of given player by one unit counter clock wise
void turretCCW(int id) {
	if (p[id].deg - 3 >= 0) {
		p[id].deg = p[id].deg - 3;
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
		if (p[i].alive) {
			if (x > p[i].x - hitBoxLength && x < p[i].x + TANK_LENGTH - 1
					+ hitBoxLength && y > p[i].y - hitBoxLength && y < p[i].y
					+ TANK_HEIGHT + hitBoxLength) {
				printf("hit player %i!\n", i);
				return 1;
			}
		}
	}
	return 0;

}

int getHitGround(int x, int y, int bulletType) {
	int i, j;
	for (j = -1; j <= 1; j++) {
		for (i = -1; i <= 1; ++i) {
			if ((map[y + j][x + i] != NOTHING)&& (y+j > field[i])) {
				//printf("hit ground!\n");
				return 1;
			}
		}
	}
	return 0;
}

void bulletExplode(int x, int y, int bulletType) {
	int r, j, i, colour, offset, id, hit, delay;
	volatile int c = 2;
	switch (bulletType) {
	case 1:
		r = 8;//set the radius of the bullet
		colour = 0xF7FD;
		//Remove pixels from the field
		/*for (i = -r; i <= r; i++) {
		 offset = sqrt(r * r - i * i);
		 if (field[x + i] < y + offset) {
		 //printf("y;%i \t field[x+i]: %i \ty-field[x+i]:%i \t offset:%i\t min: %i",	y,field[x + i],y - field[x + i],offset,(((y - field[x + i]) < offset) ? (y - field[x + i]): offset));
		 field[x + i] = (y + offset - field[x + i] < 2 * offset) ? y + offset : field[x + i] + 2 * offset;
		 //printf("\t newfield[x]:%i \n", field[x + i]);
		 }
		 }*/
		for (i = -r; i <= r; i++) {
			offset = sqrt(r * r - i * i);
			if (x + i >= 0 && x + i < SCREEN_WIDTH) {
				for (j = -offset; j <= offset; j++) {
					map[y + j][x + i] = NOTHING;
				}
			}
		}
		//See if player got hit
		for (id = 0; id < numPlayers; id++) {
			if (p[id].alive) {
				hit = 0;
				for (i = -r; i <= r && hit == 0; i++) {
					offset = sqrt(r * r - i * i);
					if (x + i >= p[id].x && x + i <= p[id].x + TANK_LENGTH - 1) {
						for (j = y - offset; j <= y + offset && hit == 0; j++) {
							if (j > p[id].y && j < p[id].y + TANK_HEIGHT) {
								hit = 1;
								printf("Explosion HIT");
								break;
							}
						}
					}
				}

				if (hit == 1) {
					p[id].hp -= 25;
					if (p[id].hp <= 0) {
						p[id].alive = DEAD;
					}
				}
			}
		}

		//Draw the explosion
		//c is used for a delay and colour effect
		delay = 25;
		for (c = 0; c <= delay; c += 1) {
			for (i = -r; i <= r; i++) {
				//printf("explosion: %i \n", x + i);
				if (x + i >= 0 && x + i < SCREEN_WIDTH) {
					offset = sqrt(r * r - i * i);
					if (c >= delay - 1) {
						updateExplosion(x + i, y, offset, NOTHING);
					} else {
						updateExplosion(x + i, y, offset, colour + c);
					}
				}
			}
			updateScreen();
		}
		break;
	case 2:
		r = 3;//set the radius of the bullet
		colour = 0xF7FD;
		//Remove pixels from the field
		/*for (i = -r; i <= r; i++) {
		 offset = sqrt(r * r - i * i);
		 if (field[x + i] < y + offset) {
		 //printf("y;%i \t field[x+i]: %i \ty-field[x+i]:%i \t offset:%i\t min: %i",	y,field[x + i],y - field[x + i],offset,(((y - field[x + i]) < offset) ? (y - field[x + i]): offset));
		 field[x + i] = (y + offset - field[x + i] < 2 * offset) ? y + offset : field[x + i] + 2 * offset;
		 //printf("\t newfield[x]:%i \n", field[x + i]);
		 }
		 }*/
		for (i = -r; i <= r; i++) {
			offset = sqrt(r * r - i * i);
			if (x + i >= 0 && x + i < SCREEN_WIDTH) {
				for (j = -offset; j <= offset; j++) {
					map[y + j][x + i] = NOTHING;
				}
			}
		}
		//See if player got hit
		for (id = 0; id < numPlayers; id++) {
			if (p[id].alive) {
				hit = 0;
				for (i = -r; i <= r && hit == 0; i++) {
					offset = sqrt(r * r - i * i);
					if (x + i >= p[id].x && x + i <= p[id].x + TANK_LENGTH - 1) {
						for (j = y - offset; j <= y + offset && hit == 0; j++) {
							if (j > p[id].y && j < p[id].y + TANK_HEIGHT) {
								hit = 1;
								printf("Explosion HIT");
								break;
							}
						}
					}
				}

				if (hit == 1) {
					p[id].hp -= 10;
					if (p[id].hp <= 0) {
						p[id].alive = DEAD;
					}
				}
			}
		}

		//Draw the explosion
		//c is used for a delay and colour effect
		delay = 25;
		for (c = 0; c <= delay; c += 1) {
			for (i = -r; i <= r; i++) {
				//printf("explosion: %i \n", x + i);
				if (x + i >= 0 && x + i < SCREEN_WIDTH) {
					offset = sqrt(r * r - i * i);
					if (c >= delay - 1) {
						updateExplosion(x + i, y, offset, NOTHING);
					} else {
						updateExplosion(x + i, y, offset, colour + c);
					}
				}
			}
			updateScreen();
		}
		break;

	}
}

//checks and updates where the tank needs to fall
void checkPlayerFalling(int id) {
	int i;
	int TankNotTouchGroundCounter = 0;

	for (i = p[id].x; i < p[id].x + TANK_LENGTH; i++) {
		if (map[p[id].y + TANK_HEIGHT][i] == NOTHING) {
			TankNotTouchGroundCounter++;
		}
	}
	//printf("TankNotTouchGroundCounter: %i\n", TankNotTouchGroundCounter);
	if (TankNotTouchGroundCounter == TANK_LENGTH) {
		p[id].y++;
		p[id].isFalling = TRUE;
	}
	else{
		p[id].isFalling = FALSE;
	}
}

