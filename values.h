#ifndef CONSTANT_VALUES_AND_STRUCTS
#define CONSTANT_VALUES_AND_STRUCTS

#include <system.h>

#define GRAVITY -15
#define PIXEL_SCALE 500
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240
#define keys (volatile char *) PARALLEL_PORT_BASE
#define switches (volatile char *) SWITCHES_BASE
#define VERBOSE 0
#define TANK_LENGTH 19
#define TANK_HEIGHT 19
#define TURRET_LENGTH 22
#define pOne 0
#define pTwo 1
#define pThree 2
#define pFour 3
#define pFive 5
#define NOTHING 9
#define GROUND 8
#define RIGHT 0
#define LEFT 1

struct player{
	int x;
	int y;
	int deg;
	int hp;
	int colour;
	int points;
	int alive;
	int gas;
	int dir;
};

struct bullet{
	int x;
	int y;
	int dx;
	int dy;
};
#endif
