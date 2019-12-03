#ifndef TYPENAME_H
#define TYPENAME_H

#include "acllib.h"
#include "bumpbox.h"

const double EPS = 1e-6;
const double Pi = 3.1415926535897932;

enum Type
{
	None,
	P_Player,
	M_Moblin,
	M_Slime,
	A_Sword,
	A_Arrow,
	A_Bomb,
	A_Boomerang,
	I_Heart,
	M_Bari,
	M_Wall,
	B_FireBall,
	N_Cucco,
	B_FireBall_M
};

enum Class_Category
{
	C_None,
	C_Player,
	C_Monster,
	C_Armor,
	C_Bullet,
	C_Wall,
	C_Item,
	C_NPC
};

enum Direction
{
	RIGHT, DOWN, LEFT, UP
};

enum Region
{
	Over_World, Village, Woods
};

struct TypeInfo
{
	double w, h;
	double speed;
	int health;
	int att;
	int category;
	const char *imgPath;
};

struct ImgForm
{
	const char *path;
	double x, y, w, h;
};

const TypeInfo TP_INFO[] =
{//  w--h--speed--health--att--category--img
	{0, 0, 0, 0, 0, C_None, ""},
	{52, 64, 4, 40, 2, C_Player, "res/player/walkD.bmp"},
	{64, 64, 2, 4, 1, C_Monster, "res/moblin0.bmp"},
	{48, 44, 3, 4, 1, C_Monster, "res/slime.bmp"},
	{64, 64, 0, 1, 2, C_Armor, "res/sword/sword_I.bmp"},
	{72, 72, 16, 1, 2, C_Bullet, "res/arrow/Bow.bmp"},
	{0, 0, 0, 0, 0, C_None, ""},
	{0, 0, 0, 0, 0, C_None, ""},
	{32, 28, 0, 16, 0, C_Item, "res/heart/heart.bmp"},
	{0, 0, 3, 8, 1, C_Monster, ""},
	{0, 0, 0, 100, 200, C_Wall, ""},
	{28, 28, 10, 1, 1, C_Bullet, "res/fireball/big.bmp"},
	{0, 0, 2, 1000, 2, C_Monster, ""},
	{16, 16, 10, 1, 1, C_Bullet, "res/fireball/mid.bmp"}
};

const int arrowKey[4] = {VK_RIGHT, VK_DOWN, VK_LEFT, VK_UP};
const int MAX_SPRITES = 200;
const int W_Width = 1280, W_Height = 720;
const int Map_Width = 16384, Map_Height = 16384;
const int MAX_ANIM = 100;

extern double playerPosX, playerPosY;
extern bool keyPressing[200];
extern ACL_Image tmpImg;

#endif
