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
	I_BlueJ,
	M_Wall,
	B_FireBall
};

enum Class_Category
{
	C_None,
	C_Player,
	C_Monster,
	C_Armor,
	C_Bullet,
	C_Wall,
	C_Item
};

enum Direction
{
	RIGHT, UP, LEFT, DOWN
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

const TypeInfo TP_INFO[12] =
{//  w--h--speed--health--att--category--img
	{0, 0, 0, 0, 0, C_None, ""},
	{52, 64, 4, 40, 2, C_Player, "src/player/walkD.bmp"},
	{64, 64, 2, 4, 1, C_Monster, "src/moblin0.bmp"},
	{48, 44, 3, 4, 1, C_Monster, "src/slime.bmp"},
	{64, 64, 0, 1, 2, C_Armor, "src/sword/sword_I.bmp"},
	{72, 72, 10, 1, 2, C_Bullet, "src/arrow/Bow.bmp"},
	{0, 0, 0, 0, 0, C_None, ""},
	{0, 0, 0, 0, 0, C_None, ""},
//   w--h--spd_bst--heal--att_bst--img
	{32, 28, 0, 16, 0, C_Item, "src/heart/heart.bmp"},
	{0, 0, 0, 0, 0, C_None, ""},
	{0, 0, 0, 100, 200, C_Wall, ""},
	{28, 28, 10, 1, 3, C_Bullet, "src/fireball/big.bmp"}
};

const char soundPath[15][40]=
{
	"src/sound/DarkWorld.mid",
	"src/sound/Tal Tal Heights.wav",
	"src/sound/Enemy_Hit.wav",
	"src/sound/Enemy_Kill.wav",
	"src/sound/Arrow_Shoot.wav"
};

const int arrowKey[4] = {VK_RIGHT, VK_UP, VK_LEFT, VK_DOWN};
const int MAX_SPRITES = 200;
const int W_Width = 1280, W_Height = 720;
const int Map_Width = 16384, Map_Height = 16384;
const int MAX_ANIM = 100;

#endif
