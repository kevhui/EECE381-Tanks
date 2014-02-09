/*
 * images_bars.h
 *
 *  Created on: 2014-02-09
 *      Author: Kevin
 */

#ifndef IMAGES_BARS_H_
#define IMAGES_BARS_H_

#ifndef BARS_H_
#define BARS_H_



#define CHARACTER_MARIO_WIDTH 20
#define CHARACTER_MARIO_HEIGHT 20



#define NAME_HEIGHT 5


#define HEALTH_BAR_HEIGHT 16
#define HEALTH_BAR_WIDTH 54
#define HEALTH_Y_GREEN_START 3
#define HEALTH_Y_GREEN_END 12
#define HEALTH_X_GREEN_START 3
#define HEALTH_X_GREEN_END 49

static int const health_bar[HEALTH_BAR_HEIGHT][HEALTH_BAR_WIDTH]={
{0x0,0x0,0x8c71,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x8c51,0x0,0x0,},
{0x0,0x8c51,0x0,0x8430,0x5acb,0x31a6,0x31a6,0x31a6,0x31a6,0x39c7,0x39c7,0x39c7,0x39c7,0x39c7,0x39c7,0x39c7,0x39c7,0x39c7,0x39c7,0x39c7,0x39e7,0x39e7,0x39e7,0x39e7,0x39e7,0x39e7,0x39e7,0x39e7,0x39e7,0x39e7,0x39e7,0x39e7,0x39c7,0x39c7,0x39c7,0x39c7,0x39e7,0x39e7,0x39e7,0x39e7,0x39e7,0x39e7,0x39e7,0x39e7,0x39e7,0x39e7,0x39e7,0x39e7,0x5acb,0x6b6d,0x8c51,0x8410,0x8c51,0x0,},
{0x0,0x8c51,0x8410,0x8c51,0x8c51,0x8430,0x8c51,0x8c51,0x8c51,0x8c51,0x8c51,0x8c51,0x8c51,0x8c51,0x8c51,0x8c51,0x8c51,0x8c51,0x8c51,0x8c51,0x8c51,0x8c51,0x8c51,0x8c51,0x8c51,0x8c51,0x8c51,0x8c51,0x8c51,0x8c51,0x8c51,0x8c51,0x8c51,0x8c51,0x8c51,0x8c51,0x8c51,0x8c51,0x8c51,0x8c51,0x8c51,0x8c51,0x8c51,0x8c51,0x8c51,0x8c51,0x8c51,0x8c51,0x8430,0x8c51,0x9492,0x8410,0x8c51,0x841,},
{0x0,0x0,0x20,0x7bef,0x7fb2,0x7fb2,0x7792,0x7792,0x7792,0x7792,0x7792,0x7792,0x7792,0x7792,0x7792,0x7792,0x7792,0x7792,0x7792,0x7792,0x7792,0x7792,0x7792,0x7792,0x7792,0x7792,0x7792,0x7792,0x7792,0x7792,0x7792,0x7792,0x7792,0x7792,0x7792,0x7792,0x7792,0x7792,0x7792,0x7792,0x7792,0x7792,0x7792,0x7792,0x7792,0x7792,0x7792,0x7792,0x77b2,0x77b2,0x8410,0x7bcf,0x0,0x0,},
{0x0,0x0,0x0,0x73ae,0x1ec9,0x1ec9,0x1ec9,0x1ec8,0x1ec9,0x1ec9,0x1ec9,0x1ec9,0x1ec8,0x1ec8,0x26e8,0x1ec8,0x26e9,0x1ec9,0x1ec9,0x1ec9,0x1ec9,0x1ec8,0x1ec8,0x26e8,0x1ec9,0x1ec9,0x1ec9,0x26e9,0x1ec9,0x1ec8,0x26e8,0x1ec9,0x26e8,0x1ec8,0x1ec9,0x26e9,0x1ec8,0x1ec8,0x1ec8,0x1ec8,0x1ec8,0x1ec8,0x1ec8,0x26e8,0x1ec9,0x1ec9,0x1ec9,0x1ec9,0x26c9,0x26c9,0x7bcf,0x73ae,0x0,0x0,},
{0x0,0x0,0x0,0x6b6d,0x1e88,0x1e88,0x1687,0x1e88,0x1e88,0x1e88,0x1e88,0x1e88,0x1e88,0x1e88,0x1e88,0x1e88,0x1e88,0x1687,0x1e88,0x1688,0x1e88,0x1e88,0x1688,0x1e88,0x1e88,0x1e88,0x1e88,0x1e88,0x1e88,0x1e88,0x1e88,0x1e88,0x1e88,0x1e88,0x1e88,0x1e88,0x1e88,0x1e88,0x1e88,0x1e88,0x1e88,0x1687,0x1e88,0x1e88,0x1e88,0x1e88,0x1e88,0x1e88,0x1e68,0x1e68,0x738e,0x738e,0x0,0x0,},
{0x0,0x0,0x0,0x632c,0x15c7,0x15c7,0x15c6,0x15c6,0x15c6,0x15c6,0x15c6,0x15a6,0x15c6,0x15a6,0x15c6,0x15c6,0x15c6,0x15a6,0x15c6,0x15c6,0x15c6,0x15c6,0x15a6,0x15c6,0x15c6,0x15c6,0x15c6,0x15a6,0x15c6,0x15c6,0x15c6,0x15c6,0x15c6,0x15c6,0x15a6,0x15c6,0x15c6,0x15c6,0x15c6,0x15c6,0x15c6,0x15a6,0x15a6,0x15c6,0x15c6,0x15c6,0x15c6,0x15c6,0x15a6,0x15a6,0x632c,0x632c,0x0,0x0,},
{0x0,0x0,0x0,0x5aeb,0xce5,0xce5,0xd05,0xd05,0xd05,0xd05,0x1505,0x1505,0xd05,0xce5,0xd05,0xce5,0x1505,0x1505,0xce5,0x1505,0xd05,0x1505,0xce5,0x1505,0x1505,0x1505,0x1505,0x1505,0xd05,0x1505,0x1505,0xd05,0x1505,0x1505,0xce5,0xce5,0xce5,0xd05,0xd05,0x1505,0x1505,0xce5,0x1505,0x1505,0xd05,0xd05,0xd05,0xd05,0x1505,0x1505,0x5aeb,0x5aeb,0x0,0x0,},
{0x0,0x0,0x0,0x5acb,0xc64,0xc64,0xc65,0xc65,0xc65,0xc65,0xc65,0xc65,0xc65,0xc65,0xc65,0xc65,0xc65,0xc65,0xc65,0xc65,0xc65,0xc65,0xc65,0xc65,0xc65,0xc65,0xc65,0xc65,0xc65,0xc65,0xc65,0xc65,0xc65,0xc65,0xc65,0xc65,0xc65,0xc65,0xc65,0xc65,0xc65,0xc65,0xc65,0xc65,0xc65,0xc65,0xc65,0xc65,0xc65,0xc65,0x5acb,0x5acb,0x0,0x0,},
{0x0,0x0,0x0,0x630c,0x13c5,0x13c5,0x13c5,0x13a5,0x13a5,0x13a5,0x13a5,0x13a5,0x13a5,0x13a5,0x13a5,0x13a5,0x13a5,0x13c5,0x13a5,0x13a5,0x13a5,0x13a5,0x13a5,0x13c5,0x13a5,0x13a5,0x13a5,0x13a5,0x13a5,0x13a5,0x13a5,0x13a5,0x13a5,0x13a5,0x13c5,0x13c5,0x13a5,0x13a5,0x13c5,0x13a5,0x13a5,0x13a5,0x13a5,0x13a5,0x13a5,0x13a5,0x13a5,0x13a5,0x1384,0x1384,0x5aeb,0x5aeb,0x0,0x0,},
{0x0,0x0,0x0,0x630c,0x13c5,0x13c5,0x13c5,0x13a5,0x13a5,0x13a5,0x13a5,0x13a5,0x13a5,0x13a5,0x13a5,0x13a5,0x13a5,0x13c5,0x13a5,0x13a5,0x13a5,0x13a5,0x13a5,0x13c5,0x13a5,0x13a5,0x13a5,0x13a5,0x13a5,0x13a5,0x13a5,0x13a5,0x13a5,0x13a5,0x13c5,0x13c5,0x13a5,0x13a5,0x13c5,0x13a5,0x13a5,0x13a5,0x13a5,0x13a5,0x13a5,0x13a5,0x13a5,0x13a5,0x1384,0x1384,0x5aeb,0x5aeb,0x0,0x0,},
{0x0,0x0,0x0,0x73ae,0x2487,0x2487,0x2487,0x2487,0x2487,0x24a7,0x2487,0x2487,0x2487,0x2487,0x2487,0x2487,0x2487,0x2487,0x2487,0x24a7,0x2487,0x24a7,0x2487,0x2487,0x2487,0x2487,0x2487,0x2487,0x2487,0x2487,0x2487,0x2487,0x2487,0x2487,0x2487,0x2487,0x2487,0x2487,0x24a7,0x2487,0x24a7,0x2487,0x24a7,0x24a7,0x2487,0x2487,0x2487,0x2487,0x1c26,0x1c26,0x6b8e,0x6b6d,0x0,0x0,},
{0x0,0x0,0x0,0x94b2,0x670f,0x670f,0x670f,0x670f,0x670f,0x670f,0x670f,0x670f,0x670f,0x670f,0x670f,0x670f,0x670f,0x670f,0x670f,0x670f,0x670f,0x670f,0x670f,0x670f,0x670f,0x670f,0x670f,0x670f,0x670f,0x5f0f,0x670f,0x670f,0x670f,0x670f,0x670f,0x670f,0x670f,0x670f,0x670f,0x670f,0x670f,0x670f,0x670f,0x670f,0x670f,0x670f,0x670f,0x670f,0x66ef,0x66ef,0x8c91,0x8c71,0x0,0x0,},
{0x0,0x0,0x94b2,0x94f3,0x94f3,0x94d2,0x94f2,0x94f2,0x94f2,0x9513,0x9513,0x9513,0x9513,0x9513,0x9513,0x9d13,0x9513,0x9d13,0x9d13,0x9d13,0x9d13,0x9d13,0x9d13,0x9d13,0x9d13,0x9d33,0x9d13,0x9d13,0x9d33,0x9d33,0x9d33,0x9d33,0x9d33,0x9d33,0x9d33,0x9d33,0x9d33,0x9d33,0x9d33,0x9d33,0x9d33,0x9d33,0x9d33,0x9d33,0x9d33,0x9d33,0x9d33,0x9d33,0xa533,0xa513,0xa514,0xa514,0x0,0x0,},
{0x0,0x5acb,0x5acb,0x5acb,0x5acb,0x31a6,0x31a6,0x31a6,0x31a6,0x39c7,0x39c7,0x39c7,0x39c7,0x39c7,0x39c7,0x39c7,0x39c7,0x39c7,0x39c7,0x39c7,0x39e7,0x39e7,0x39e7,0x39e7,0x39e7,0x39e7,0x39e7,0x39e7,0x39e7,0x39e7,0x39e7,0x39e7,0x39c7,0x39c7,0x39c7,0x39c7,0x39e7,0x39e7,0x39e7,0x39e7,0x39e7,0x39e7,0x39e7,0x39e7,0x39e7,0x39e7,0x39e7,0x39e7,0x5acb,0x6b6d,0x6b4d,0x5aeb,0x6b6d,0x0,},
{0x0,0x31a6,0x0,0x3186,0x861,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x861,0x4228,0x20,0x4208,0x0,}
};


// Gas Bar
#define GAS_BAR_HEIGHT 20

#define GAS_BAR_2_WIDTH 37
#define GAS_Y_2_RED_START 4
#define GAS_Y_2_RED_END 15
#define GAS_X_2_RED_START 5
#define GAS_X_2_RED_END 32

static int const gas_bar_2[GAS_BAR_HEIGHT][GAS_BAR_2_WIDTH]={
{0x0,0x0,0x8c71,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x8c51,0x0,0x0,},
{0x0,0x8c51,0x0,0x8430,0x18c3,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x8c51,0x8410,0x8c51,0x0,},
{0x0,0x8c51,0x8410,0x8c51,0x8c51,0x8430,0x8c51,0x8c51,0x8c51,0x8c51,0x8c51,0x8c51,0x8c51,0x8c51,0x8c51,0x8c51,0x8c51,0x8c51,0x8c51,0x8c51,0x8c51,0x8c51,0x8c51,0x8c51,0x8c51,0x8c51,0x8c51,0x8c51,0x8c51,0x8c51,0x8c51,0x8430,0x8c51,0x9492,0x8410,0x8c51,0x841,},
{0x0,0x20,0x8430,0x8430,0x738e,0x20,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x8c51,0x8430,0x8430,0x0,0x0,},
{0x0,0x0,0x20,0x7bef,0x9e3,0xfc90,0xfc90,0xfc90,0xfc90,0xfc90,0xfc90,0xfc90,0xfc90,0xfc90,0xfc90,0xfc90,0xfc90,0xfc90,0xfc90,0xfc90,0xfc90,0xfc90,0xfc90,0xfc90,0xfc90,0xfc90,0xfc90,0xfc90,0xfc90,0xfc90,0xfc90,0xfc90,0xfc90,0x8410,0x7bcf,0x0,0x0,},
{0x0,0x0,0x0,0x73ae,0x200,0xfb10,0xfb10,0xfb10,0xfb10,0xfb10,0xfb10,0xfb10,0xfb10,0xfb10,0xfb10,0xfb10,0xfb10,0xfb10,0xfb10,0xfb10,0xfb10,0xfb10,0xfb10,0xfb10,0xfb10,0xfb10,0xfb10,0xfb10,0xfb10,0xfb10,0xfb10,0xfb10,0xfb10,0x7bcf,0x73ae,0x0,0x0,},
{0x0,0x0,0x0,0x6b6d,0x1e0,0xfa0c,0xfa0c,0xfa0c,0xfa0c,0xfa0c,0xfa0c,0xfa0c,0xfa0c,0xfa0c,0xfa0c,0xfa0c,0xfa0c,0xfa0c,0xfa0c,0xfa0c,0xfa0c,0xfa0c,0xfa0c,0xfa0c,0xfa0c,0xfa0c,0xfa0c,0xfa0c,0xfa0c,0xfa0c,0xfa0c,0xfa0c,0xfa0c,0x738e,0x738e,0x0,0x0,},
{0x0,0x0,0x0,0x632c,0x1a0,0xf908,0xf908,0xf908,0xf908,0xf908,0xf908,0xf908,0xf908,0xf908,0xf908,0xf908,0xf908,0xf908,0xf908,0xf908,0xf908,0xf908,0xf908,0xf908,0xf908,0xf908,0xf908,0xf908,0xf908,0xf908,0xf908,0xf908,0xf908,0x632c,0x632c,0x0,0x0,},
{0x0,0x0,0x0,0x5aeb,0x180,0xe804,0xe804,0xe804,0xe804,0xe804,0xe804,0xe804,0xe804,0xe804,0xe804,0xe804,0xe804,0xe804,0xe804,0xe804,0xe804,0xe804,0xe804,0xe804,0xe804,0xe804,0xe804,0xe804,0xe804,0xe804,0xe804,0xe804,0xe804,0x5aeb,0x5aeb,0x0,0x0,},
{0x0,0x0,0x0,0x5acb,0x140,0xd800,0xd800,0xd800,0xd800,0xd800,0xd800,0xd800,0xd800,0xd800,0xd800,0xd800,0xd800,0xd800,0xd800,0xd800,0xd800,0xd800,0xd800,0xd800,0xd800,0xd800,0xd800,0xd800,0xd800,0xd800,0xd800,0xd800,0xd800,0x5acb,0x5acb,0x0,0x0,},
{0x0,0x0,0x0,0x5acb,0x100,0xb800,0xb800,0xb800,0xb800,0xb800,0xb800,0xb800,0xb800,0xb800,0xb800,0xb800,0xb800,0xb800,0xb800,0xb800,0xb800,0xb800,0xb800,0xb800,0xb800,0xb800,0xb800,0xb800,0xb800,0xb800,0xb800,0xb800,0xb800,0x5acb,0x5acb,0x0,0x0,},
{0x0,0x0,0x0,0x630c,0x100,0xb800,0xb800,0xb800,0xb800,0xb800,0xb800,0xb800,0xb800,0xb800,0xb800,0xb800,0xb800,0xb800,0xb800,0xb800,0xb800,0xb800,0xb800,0xb800,0xb800,0xb800,0xb800,0xb800,0xb800,0xb800,0xb800,0xb800,0xb800,0x5aeb,0x5aeb,0x0,0x0,},
{0x0,0x0,0x0,0x73ae,0x140,0xd800,0xd800,0xd800,0xd800,0xd800,0xd800,0xd800,0xd800,0xd800,0xd800,0xd800,0xd800,0xd800,0xd800,0xd800,0xd800,0xd800,0xd800,0xd800,0xd800,0xd800,0xd800,0xd800,0xd800,0xd800,0xd800,0xd800,0xd800,0x6b8e,0x6b6d,0x0,0x0,},
{0x0,0x0,0x0,0x94b2,0x1a2,0xfc90,0xfc90,0xfc90,0xfc90,0xfc90,0xfc90,0xfc90,0xfc90,0xfc90,0xfc90,0xfc90,0xfc90,0xfc90,0xfc90,0xfc90,0xfc90,0xfc90,0xfc90,0xfc90,0xfc90,0xfc90,0xfc90,0xfc90,0xfc90,0xfc90,0xfc90,0xfc90,0xfc90,0x8c91,0x8c71,0x0,0x0,},
{0x0,0x0,0x0,0xa514,0x1c1,0xfa0c,0xfa0c,0xfa0c,0xfa0c,0xfa0c,0xfa0c,0xfa0c,0xfa0c,0xfa0c,0xfa0c,0xfa0c,0xfa0c,0xfa0c,0xfa0c,0xfa0c,0xfa0c,0xfa0c,0xfa0c,0xfa0c,0xfa0c,0xfa0c,0xfa0c,0xfa0c,0xfa0c,0xfa0c,0xfa0c,0xfa0c,0xfa0c,0x9d13,0x9cf3,0x0,0x0,},
{0x0,0x0,0x0,0xad55,0x120,0xfa0c,0xfa0c,0xfa0c,0xfa0c,0xfa0c,0xfa0c,0xfa0c,0xfa0c,0xfa0c,0xfa0c,0xfa0c,0xfa0c,0xfa0c,0xfa0c,0xfa0c,0xfa0c,0xfa0c,0xfa0c,0xfa0c,0xfa0c,0xfa0c,0xfa0c,0xfa0c,0xfa0c,0xfa0c,0xfa0c,0xfa0c,0xfa0c,0xad55,0xad55,0x0,0x0,},
{0x0,0x0,0x94b2,0x94b2,0x94f3,0x94d2,0x94f2,0x94f2,0x94f2,0x94f2,0x94f2,0x94f2,0x94f2,0x94f2,0x94f2,0x94f2,0x9513,0x9513,0x9513,0x9d13,0x9513,0x9513,0x9513,0x9d33,0x9d33,0x9d33,0x9d33,0x9d33,0x9d33,0x9d33,0x9d33,0xa533,0xa513,0xa514,0xa514,0x0,0x0,},
{0x0,0x5acb,0x5acb,0x5acb,0x5acb,0x31a6,0x31a6,0x31a6,0x31a6,0x31a6,0x31a6,0x31a6,0x31a6,0x31a6,0x31a6,0x31a6,0x31a6,0x31a6,0x31a6,0x31a6,0x31a6,0x39e7,0x39e7,0x39e7,0x39e7,0x39e7,0x39e7,0x39e7,0x39e7,0x39e7,0x39e7,0x5acb,0x6b6d,0x6b4d,0x5aeb,0x6b6d,0x0,},
{0x0,0x31a6,0x0,0x3186,0x861,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x861,0x4228,0x20,0x4208,0x0,},
{0x0,0x0,0x20,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x861,0x0,0x0,}
};

#define GAS_BAR_3_WIDTH 27
#define GAS_Y_3_RED_START 4
#define GAS_Y_3_RED_END 15
#define GAS_X_3_RED_START 5
#define GAS_X_3_RED_END 22

static int const gas_bar_3[GAS_BAR_HEIGHT][GAS_BAR_3_WIDTH]={
{0x0,0x0,0x8c71,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x8c51,0x0,0x0,},
{0x0,0x8c51,0x0,0x8430,0x18c3,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x8c51,0x8410,0x8c51,0x0,},
{0x0,0x8c51,0x8410,0x8c51,0x8c51,0x8430,0x8c51,0x8c51,0x8c51,0x8c51,0x8c51,0x8c51,0x8c51,0x8c51,0x8c51,0x8c51,0x8c51,0x8c51,0x8c51,0x8c51,0x8c51,0x8430,0x8c51,0x9492,0x8410,0x8c51,0x841,},
{0x0,0x20,0x8430,0x8430,0x738e,0x20,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x8c51,0x8430,0x8430,0x0,0x0,},
{0x0,0x0,0x20,0x7bef,0x9e3,0xfc90,0xfc90,0xfc90,0xfc90,0xfc90,0xfc90,0xfc90,0xfc90,0xfc90,0xfc90,0xfc90,0xfc90,0xfc90,0xfc90,0xfc90,0xfc90,0xfc90,0xfc90,0x8410,0x7bcf,0x0,0x0,},
{0x0,0x0,0x0,0x73ae,0x200,0xfb10,0xfb10,0xfb10,0xfb10,0xfb10,0xfb10,0xfb10,0xfb10,0xfb10,0xfb10,0xfb10,0xfb10,0xfb10,0xfb10,0xfb10,0xfb10,0xfb10,0xfb10,0x7bcf,0x73ae,0x0,0x0,},
{0x0,0x0,0x0,0x6b6d,0x1e0,0xfa0c,0xfa0c,0xfa0c,0xfa0c,0xfa0c,0xfa0c,0xfa0c,0xfa0c,0xfa0c,0xfa0c,0xfa0c,0xfa0c,0xfa0c,0xfa0c,0xfa0c,0xfa0c,0xfa0c,0xfa0c,0x738e,0x738e,0x0,0x0,},
{0x0,0x0,0x0,0x632c,0x1a0,0xf908,0xf908,0xf908,0xf908,0xf908,0xf908,0xf908,0xf908,0xf908,0xf908,0xf908,0xf908,0xf908,0xf908,0xf908,0xf908,0xf908,0xf908,0x632c,0x632c,0x0,0x0,},
{0x0,0x0,0x0,0x5aeb,0x180,0xe804,0xe804,0xe804,0xe804,0xe804,0xe804,0xe804,0xe804,0xe804,0xe804,0xe804,0xe804,0xe804,0xe804,0xe804,0xe804,0xe804,0xe804,0x5aeb,0x5aeb,0x0,0x0,},
{0x0,0x0,0x0,0x5acb,0x140,0xd800,0xd800,0xd800,0xd800,0xd800,0xd800,0xd800,0xd800,0xd800,0xd800,0xd800,0xd800,0xd800,0xd800,0xd800,0xd800,0xd800,0xd800,0x5acb,0x5acb,0x0,0x0,},
{0x0,0x0,0x0,0x5acb,0x100,0xb800,0xb800,0xb800,0xb800,0xb800,0xb800,0xb800,0xb800,0xb800,0xb800,0xb800,0xb800,0xb800,0xb800,0xb800,0xb800,0xb800,0xb800,0x5acb,0x5acb,0x0,0x0,},
{0x0,0x0,0x0,0x630c,0x100,0xb800,0xb800,0xb800,0xb800,0xb800,0xb800,0xb800,0xb800,0xb800,0xb800,0xb800,0xb800,0xb800,0xb800,0xb800,0xb800,0xb800,0xb800,0x5aeb,0x5aeb,0x0,0x0,},
{0x0,0x0,0x0,0x73ae,0x140,0xd800,0xd800,0xd800,0xd800,0xd800,0xd800,0xd800,0xd800,0xd800,0xd800,0xd800,0xd800,0xd800,0xd800,0xd800,0xd800,0xd800,0xd800,0x6b8e,0x6b6d,0x0,0x0,},
{0x0,0x0,0x0,0x94b2,0x1a2,0xfc90,0xfc90,0xfc90,0xfc90,0xfc90,0xfc90,0xfc90,0xfc90,0xfc90,0xfc90,0xfc90,0xfc90,0xfc90,0xfc90,0xfc90,0xfc90,0xfc90,0xfc90,0x8c91,0x8c71,0x0,0x0,},
{0x0,0x0,0x0,0xa514,0x1c1,0xfa0c,0xfa0c,0xfa0c,0xfa0c,0xfa0c,0xfa0c,0xfa0c,0xfa0c,0xfa0c,0xfa0c,0xfa0c,0xfa0c,0xfa0c,0xfa0c,0xfa0c,0xfa0c,0xfa0c,0xfa0c,0x9d13,0x9cf3,0x0,0x0,},
{0x0,0x0,0x0,0xad55,0x120,0xfa0c,0xfa0c,0xfa0c,0xfa0c,0xfa0c,0xfa0c,0xfa0c,0xfa0c,0xfa0c,0xfa0c,0xfa0c,0xfa0c,0xfa0c,0xfa0c,0xfa0c,0xfa0c,0xfa0c,0xfa0c,0xad55,0xad55,0x0,0x0,},
{0x0,0x0,0x94b2,0x94b2,0x94f3,0x94d2,0x94f2,0x94f2,0x94f2,0x94f2,0x94f2,0x9513,0x9513,0x9d33,0x9d33,0x9d33,0x9d33,0x9d33,0x9d33,0x9d33,0x9d33,0xa533,0xa513,0xa514,0xa514,0x0,0x0,},
{0x0,0x5acb,0x5acb,0x5acb,0x5acb,0x31a6,0x31a6,0x31a6,0x31a6,0x31a6,0x31a6,0x39e7,0x39e7,0x39e7,0x39e7,0x39e7,0x39e7,0x39e7,0x39e7,0x39e7,0x39e7,0x5acb,0x6b6d,0x6b4d,0x5aeb,0x6b6d,0x0,},
{0x0,0x31a6,0x0,0x3186,0x861,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x861,0x4228,0x20,0x4208,0x0,},
{0x0,0x0,0x20,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x861,0x0,0x0,}
};

#define GAS_BAR_4_WIDTH 18
#define GAS_Y_4_RED_START 4
#define GAS_Y_4_RED_END 15
#define GAS_X_4_RED_START 5
#define GAS_X_4_RED_END 13

static int const gas_bar_4[GAS_BAR_HEIGHT][GAS_BAR_4_WIDTH]={
{0x0,0x0,0x8c71,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x8c51,0x0,0x0,},
{0x0,0x8c51,0x0,0x8430,0x18c3,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x8c51,0x8410,0x8c51,0x0,},
{0x0,0x8c51,0x8410,0x8c51,0x8c51,0x8430,0x8c51,0x8c51,0x8c51,0x8c51,0x8c51,0x8c51,0x8430,0x8c51,0x9492,0x8410,0x8c51,0x841,},
{0x0,0x20,0x8430,0x8430,0x738e,0x20,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x8c51,0x8430,0x8430,0x0,0x0,},
{0x0,0x0,0x20,0x7bef,0x9e3,0xfc90,0xfc90,0xfc90,0xfc90,0xfc90,0xfc90,0xfc90,0xfc90,0xfc90,0x8410,0x7bcf,0x0,0x0,},
{0x0,0x0,0x0,0x73ae,0x200,0xfb10,0xfb10,0xfb10,0xfb10,0xfb10,0xfb10,0xfb10,0xfb10,0xfb10,0x7bcf,0x73ae,0x0,0x0,},
{0x0,0x0,0x0,0x6b6d,0x1e0,0xfa0c,0xfa0c,0xfa0c,0xfa0c,0xfa0c,0xfa0c,0xfa0c,0xfa0c,0xfa0c,0x738e,0x738e,0x0,0x0,},
{0x0,0x0,0x0,0x632c,0x1a0,0xf908,0xf908,0xf908,0xf908,0xf908,0xf908,0xf908,0xf908,0xf908,0x632c,0x632c,0x0,0x0,},
{0x0,0x0,0x0,0x5aeb,0x180,0xe804,0xe804,0xe804,0xe804,0xe804,0xe804,0xe804,0xe804,0xe804,0x5aeb,0x5aeb,0x0,0x0,},
{0x0,0x0,0x0,0x5acb,0x140,0xd800,0xd800,0xd800,0xd800,0xd800,0xd800,0xd800,0xd800,0xd800,0x5acb,0x5acb,0x0,0x0,},
{0x0,0x0,0x0,0x5acb,0x100,0xb800,0xb800,0xb800,0xb800,0xb800,0xb800,0xb800,0xb800,0xb800,0x5acb,0x5acb,0x0,0x0,},
{0x0,0x0,0x0,0x630c,0x100,0xb800,0xb800,0xb800,0xb800,0xb800,0xb800,0xb800,0xb800,0xb800,0x5aeb,0x5aeb,0x0,0x0,},
{0x0,0x0,0x0,0x73ae,0x140,0xd800,0xd800,0xd800,0xd800,0xd800,0xd800,0xd800,0xd800,0xd800,0x6b8e,0x6b6d,0x0,0x0,},
{0x0,0x0,0x0,0x94b2,0x1a2,0xfc90,0xfc90,0xfc90,0xfc90,0xfc90,0xfc90,0xfc90,0xfc90,0xfc90,0x8c91,0x8c71,0x0,0x0,},
{0x0,0x0,0x0,0xa514,0x1c1,0xfa0c,0xfa0c,0xfa0c,0xfa0c,0xfa0c,0xfa0c,0xfa0c,0xfa0c,0xfa0c,0x9d13,0x9cf3,0x0,0x0,},
{0x0,0x0,0x0,0xad55,0x120,0xfa0c,0xfa0c,0xfa0c,0xfa0c,0xfa0c,0xfa0c,0xfa0c,0xfa0c,0xfa0c,0xad55,0xad55,0x0,0x0,},
{0x0,0x0,0x94b2,0x94b2,0x94f3,0x9d33,0x9d33,0x9d33,0x9d33,0x9d33,0x9d33,0x9d33,0xa533,0xa513,0xa514,0xa514,0x0,0x0,},
{0x0,0x5acb,0x5acb,0x5acb,0x39e7,0x39e7,0x39e7,0x39e7,0x39e7,0x39e7,0x39e7,0x39e7,0x5acb,0x6b6d,0x6b4d,0x5aeb,0x6b6d,0x0,},
{0x0,0x31a6,0x0,0x3186,0x861,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x861,0x4228,0x20,0x4208,0x0,},
{0x0,0x0,0x20,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x861,0x0,0x0,}
};



#define BULLET_BORDER_WIDTH 20
#define BULLET_BORDER_HEIGHT 15

static int const bullet_border[BULLET_BORDER_HEIGHT][BULLET_BORDER_WIDTH]={
{0x0,0x0,0x8c71,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x8c51,0x0,0x0,},
{0x0,0x8c51,0x0,0x8430,0x18c3,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x8c51,0x8410,0x8c51,0x0,},
{0x0,0x8c51,0x8410,0x8c51,0x8c51,0x8c51,0x8c51,0x8c51,0x8c51,0x8c51,0x8c51,0x8c51,0x8c51,0x8430,0x8c51,0x9492,0x8410,0x8c51,0x0,},
{0x0,0x20,0x8430,0x8430,0x0,0x20,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x8430,0x0,0x0,0x0,},
{0x0,0x0,0x20,0x7bef,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x8410,0x0,0x0,0x0,},
{0x0,0x0,0x0,0x73ae,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x7bcf,0x0,0x0,0x0,},
{0x0,0x0,0x0,0x6b6d,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x738e,0x0,0x0,0x0,},
{0x0,0x0,0x0,0x73ae,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x6b8e,0x0,0x0,0x0,},
{0x0,0x0,0x0,0x94b2,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x8c91,0x0,0x0,0x0,},
{0x0,0x0,0x0,0xa514,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x9d13,0x0,0x0,0x0,},
{0x0,0x0,0x0,0xad55,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0xad55,0x0,0x0,0x0,},
{0x0,0x0,0x94b2,0x94b2,0x94f3,0x94d2,0x94f2,0x94f2,0x94f2,0x94f2,0x94f2,0x94f2,0x9d33,0xa533,0xa513,0xa514,0xa514,0x0,0x0,},
{0x0,0x5acb,0x5acb,0x5acb,0x5acb,0x31a6,0x31a6,0x31a6,0x31a6,0x31a6,0x31a6,0x39e7,0x39e7,0x5acb,0x6b6d,0x6b4d,0x5aeb,0x6b6d,0x0,},
{0x0,0x31a6,0x0,0x3186,0x861,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x861,0x4228,0x20,0x4208,0x0,},
{0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x861,0x0,0x0,}
};





#define WIND_WIDTH 20
#define WIND_HEIGHT 10

static int const wind[WIND_HEIGHT][WIND_WIDTH]={
{0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x2b33,0x5436,0x0,0x0,0x0,0x0,0xa6be,0x0,0x0,0x0,0x0,0x0,},
{0x0,0x0,0x0,0x6cd8,0x6498,0x5437,0x4bf6,0x43b5,0x3b74,0x2b33,0x1af3,0x12b2,0x1271,0xa30,0x0,0x0,0x8dfc,0x8dfc,0x0,0x0,},
{0x0,0xe77e,0x7d7a,0x7519,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x1271,0xa50,0x0,0x0,0x7d5a,0x753a,0x0,},
{0x0,0x8e1c,0x0,0x0,0x230,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0xa51,0x0,0x64b8,0x6498,0x6498,},
{0x9e9e,0x0,0x0,0xa51,0x1291,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x5416,0x4bf6,0x4bf6,},
{0xa6de,0x0,0x1271,0x12b2,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x3b74,0x3b74,0x3354,},
{0x0,0x0,0x1ad2,0x2313,0x2b34,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x1af3,0x1ad2,0x1ad2,0x0,},
{0x0,0x0,0x0,0x3b74,0x43b5,0x4bf6,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x1291,0x1271,0x1271,0x1271,0x0,0x0,0x0,},
{0x0,0x0,0x0,0x0,0x5416,0x5c57,0x6498,0x6cd8,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,},
{0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x753a,0x7d7a,0x85bb,0x8dfc,0x963d,0x9e7d,0xa6be,0xefbf,0x0,0x0,0x0,0x0,0x0,}
};




#define WIND_DIRECTION_WIDTH 20
#define WIND_DIRECTION_HEIGHT 8

static int const wind_direction[WIND_DIRECTION_HEIGHT][WIND_DIRECTION_WIDTH]={
{0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x54d9,0x4498,0x3c57,0x0,0x0,0x0,0x0,0x0,0x0,0x0,},
{0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x54d9,0x4498,0x3c57,0x0,0x0,0x0,0x0,0x0,0x0,0x0,},
{0x0,0x0,0xb65c,0xa5fb,0x95bb,0x857a,0x64d9,0x64b8,0x5cb9,0x54b9,0x54b8,0x4c98,0x4498,0x4498,0x3c78,0x3478,0x0,0x0,0x0,0x0,},
{0x0,0x0,0xc69d,0xbe5c,0xae3c,0x9dfb,0x8d9a,0x7d5a,0x7519,0x5cb9,0x5cb8,0x5498,0x5498,0x4c98,0x4498,0x3c78,0x3c78,0x2a92,0x0,},
{0x0,0x0,0xc69d,0xbe5c,0xae3c,0x9dfb,0x8d9a,0x7d5a,0x7519,0x5cb9,0x5cb8,0x5498,0x5498,0x4c98,0x4498,0x3c78,0x3c78,0x2a92,0x0,},
{0x0,0x0,0x2a91,0x2ab3,0x2ad3,0x2314,0x2354,0x2395,0x23b5,0x23f6,0x9e1c,0x5cb9,0x5498,0x4c98,0x43f6,0x2ab3,0x0,0x0,0x0,0x0,},
{0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0xcefe,0x6d3a,0x22f4,0x21,0x0,0x0,0x0,0x0,0x0,0x0,},
{0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0xcefe,0x6d3a,0x22f4,0x21,0x0,0x0,0x0,0x0,0x0,0x0,}
};

#endif


#endif /* IMAGES_BARS_H_ */
