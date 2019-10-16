#ifndef TYPENAME_H
#define TYPENAME_H

#include "acllib.h"

#define None         0
#define P_Player     1
#define M_Moblin     2
#define M_Chuchu     3
#define M_Slime      4
#define A_Sword      5
#define A_Arrow      6
#define A_Bomb       7
#define A_Boomerang  8
#define I_Heart      9
#define I_BlueJ     10
#define B_Wall      11

#define C_None       0
#define C_Player     1
#define C_Monster    2
#define C_Armor      3
#define C_Bullet     4
#define C_Wall       5
#define C_Item       6

#define RIGHT 0
#define UP    1
#define LEFT  2
#define DOWN  3

const double EPS = 1e-6;

struct TypeInfo
{
	const char *imgPath;
	double w, h;
	double speed;
	int health;
	int att;
	int category;
};

const TypeInfo TP_INFO[12] =
{//    img--w--h--speed--health--att--category
	{"", 0, 0, 0, 0, 0, C_None},
	{"src/player/walkD.bmp", 52, 64, 5, 20, 1, C_Player},
	{"src/moblin0.bmp", 64, 64, 2, 2, 1, C_Monster},
	{"", 0, 0, 0, 0, 0, C_None},
	{"", 0, 0, 0, 0, 0, C_None},
	{"", 0, 0, 0, 0, 0, C_None},
	{"src/arrow/arrowU.bmp", 20, 56, 10, 1, 1, C_Bullet},
	{"", 0, 0, 0, 0, 0, C_None},
	{"", 0, 0, 0, 0, 0, C_None},
//     img--w--h--spd_bst--heal--att_bst
	{"src/heart/heart.bmp", 32, 28, 0, 8, 0, C_Item},
	{"", 0, 0, 0, 0, 0, C_None},
	{"", 0, 0, 0, 100, 200, C_Wall}
};

const int arrowKey[4] = {VK_RIGHT, VK_UP, VK_LEFT, VK_DOWN};

const int MAX_SPRITES = 200;

const int W_Width = 1280, W_Height = 720;

const int Map_Width = 10240, Map_Height = 8192;

#endif
