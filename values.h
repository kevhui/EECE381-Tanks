#ifndef CONSTANT_VALUES_AND_STRUCTS
#define CONSTANT_VALUES_AND_STRUCTS

#include <system.h>

#define GRAVITY -35
#define PIXEL_SCALE 250
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240
#define keys (volatile char *) PARALLEL_PORT_BASE
#define switches (volatile char *) SWITCHES_BASE
#define VERBOSE 0
#define TANK_LENGTH 19
#define TANK_HEIGHT 19
#define TURRET_LENGTH 16
#define pOne 0
#define pTwo 1
#define pThree 2
#define pFour 3
#define pFive 5
#define NOTHING 0x0000
#define GROUND 8
#define RIGHT 1
#define LEFT -1
#define LEFT_ARROW 0x6b
#define RIGHT_ARROW 0x74
#define UP_ARROW 0x75
#define DOWN_ARROW 0x72
#define PAGE_UP 0x7d
#define PAGE_DOWN 0x7A
#define SPACEBAR 0x29
#define BACKSPACE 0x66
//TODO: chnage the mask colour
#define MASK 0x0000
#define MARIO 0
#define LUIGI 1
#define COMPUTER 0
#define HUMAN 1
#define SCREEN_CHARACTER_WIDTH 80
#define SCREEN_CHARACTER_HEIGHT 60
#define ALIVE 1
#define DEAD 0
#define TRUE 1
#define FALSE 0

typedef struct ai {
	int target;
	int hasTarget;
	int turnLock;
	int checkNum;
	int closest[2];
	int isHit;
	int hitBy;
	int fire;
	int offset;
	int offshoot;
} ai;

typedef struct player {
	int x;
	int y;
	int dx;
	int dy;
	int deg;
	int hp;
	int character;
	int points;
	int alive;
	int gas;
	int dir;
	int colour;
	char name[10];
	int type;
	int power;
	int isFalling;
	int moved;
	int bulletType;
	ai ai;
} player;



struct bullet {
	int x;
	int y;
	int dx;
	int dy;
};

enum bulletType {
	regular,
	splits
};
#endif
