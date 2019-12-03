#ifndef PLAYER_H
#define PLAYER_H

#include <cstdio>
#include <ctime>
#include "typename.h"
#include "entity.h"
#include "item.h"
#include "sword.h"
#include "sound.h"

#define PLAYER_MAX_ITEM 5

const ImgForm Player_Img[4][9] =
{
	{
		{"res/player/R0.bmp", -40, -64, 68, 96},
		{"res/player/R1.bmp", -40, -64, 68, 96},
		{"res/player/R2.bmp", -36, -64, 68, 96},
		{"res/player/R3.bmp", -40, -64, 68, 96},
		{"res/player/R4.bmp", -40, -64, 68, 96},
		{"res/player/R5.bmp", -40, -64, 68, 96},
		{"res/player/R6.bmp", -36, -64, 68, 96},
		{"res/player/R7.bmp", -36, -64, 68, 96},
		{"res/player/R8.bmp", -40, -64, 68, 96}
	},
	{
		{"res/player/D0.bmp", -32, -64, 64, 96},
		{"res/player/D1.bmp", -32, -64, 64, 96},
		{"res/player/D2.bmp", -32, -64, 64, 96},
		{"res/player/D3.bmp", -32, -64, 64, 96},
		{"res/player/D4.bmp", -32, -64, 64, 96},
		{"res/player/D5.bmp", -32, -64, 64, 96},
		{"res/player/D6.bmp", -32, -64, 64, 96},
		{"res/player/D7.bmp", -32, -64, 64, 96},
		{"res/player/D8.bmp", -32, -64, 64, 96}
	},
	{
		{"res/player/L0.bmp", -28, -64, 68, 96},
		{"res/player/L1.bmp", -28, -64, 68, 96},
		{"res/player/L2.bmp", -32, -64, 68, 96},
		{"res/player/L3.bmp", -28, -64, 68, 96},
		{"res/player/L4.bmp", -28, -64, 68, 96},
		{"res/player/L5.bmp", -28, -64, 68, 96},
		{"res/player/L6.bmp", -32, -64, 68, 96},
		{"res/player/L7.bmp", -32, -64, 68, 96},
		{"res/player/L8.bmp", -28, -64, 68, 96}
	},
	{
		{"res/player/U0.bmp", -32, -64, 64, 96},
		{"res/player/U1.bmp", -32, -64, 64, 96},
		{"res/player/U2.bmp", -32, -64, 64, 96},
		{"res/player/U3.bmp", -32, -64, 64, 96},
		{"res/player/U4.bmp", -32, -64, 64, 96},
		{"res/player/U5.bmp", -32, -64, 64, 96},
		{"res/player/U6.bmp", -32, -64, 64, 96},
		{"res/player/U7.bmp", -32, -64, 64, 96},
		{"res/player/U8.bmp", -32, -64, 64, 96}
	}
};

const BumpBox Player_Box[4] =
{
	{-28, -32, 56, 64},
	{-32, -32, 64, 64},
	{-28, -32, 56, 64},
	{-32, -32, 64, 64}
};

class Player:
	public Entity
{
public:
	Player();
	~Player();
	void reactWith(Entity *e);
	void getItem(int tp);
	void getItem(Item *it);
	void useItem();
	void useSword();
	void switchItem();
	bool haveItem(int tp);
	void moveBehavior();
	void turn(int dir);
	void showImg();
	void checkHealth();
private:
	Item *item[PLAYER_MAX_ITEM];
	int holding;
	int lHealthCounter;
	Sword *swd;
};

#endif
