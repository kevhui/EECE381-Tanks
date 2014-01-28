#ifndef CONSTANT_VALUES_AND_STRUCTS
#define CONSTANT_VALUES_AND_STRUCTS

#include <system.h>

#define GRAVITY -200
#define PIXEL_SCALE 1000
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240
#define keys (volatile char *) PARALLEL_PORT_BASE
#define switches (volatile char *) SWITCHES_BASE
#define VERBOSE 0
#define TANK_LENGTH 12
#define TANK_HEIGHT 8
#define TURRET_LENGTH 13
#define pOne 0
#define pTwo 1
#define pThree 2
#define pFour 3
#define pFive 5
#define NOTHING 9
#define GROUND 8

struct player{
	int x;
	int y;
	int deg;
	int hp;
	int colour;
	int points;
	int alive;
	int gas;
};

struct bullet{
	int x;
	int y;
	int dx;
	int dy;
};
#endif
