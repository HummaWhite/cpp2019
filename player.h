#ifndef PLAYER_H
#define PLAYER_H

#include <cstdio>
#include <ctime>
#include "typename.h"
#include "entity.h"
#include "item.h"
#include "sword.h"

#define PLAYER_MAX_ITEM 5

const ImgForm Player_Img[4][9] =
{
	{
		{"src/player/R0.bmp", -40, -64, 68, 96},
		{"src/player/R1.bmp", -40, -64, 68, 96},
		{"src/player/R2.bmp", -36, -64, 68, 96},
		{"src/player/R3.bmp", -40, -64, 68, 96},
		{"src/player/R4.bmp", -40, -64, 68, 96},
		{"src/player/R5.bmp", -40, -64, 68, 96},
		{"src/player/R6.bmp", -36, -64, 68, 96},
		{"src/player/R7.bmp", -36, -64, 68, 96},
		{"src/player/R8.bmp", -40, -64, 68, 96}
	},
	{
		{"src/player/U0.bmp", -32, -64, 64, 96},
		{"src/player/U1.bmp", -32, -64, 64, 96},
		{"src/player/U2.bmp", -32, -64, 64, 96},
		{"src/player/U3.bmp", -32, -64, 64, 96},
		{"src/player/U4.bmp", -32, -64, 64, 96},
		{"src/player/U5.bmp", -32, -64, 64, 96},
		{"src/player/U6.bmp", -32, -64, 64, 96},
		{"src/player/U7.bmp", -32, -64, 64, 96},
		{"src/player/U8.bmp", -32, -64, 64, 96}
	},
	{
		{"src/player/L0.bmp", -28, -64, 68, 96},
		{"src/player/L1.bmp", -28, -64, 68, 96},
		{"src/player/L2.bmp", -32, -64, 68, 96},
		{"src/player/L3.bmp", -28, -64, 68, 96},
		{"src/player/L4.bmp", -28, -64, 68, 96},
		{"src/player/L5.bmp", -28, -64, 68, 96},
		{"src/player/L6.bmp", -32, -64, 68, 96},
		{"src/player/L7.bmp", -32, -64, 68, 96},
		{"src/player/L8.bmp", -28, -64, 68, 96}
	},
	{
		{"src/player/D0.bmp", -32, -64, 64, 96},
		{"src/player/D1.bmp", -32, -64, 64, 96},
		{"src/player/D2.bmp", -32, -64, 64, 96},
		{"src/player/D3.bmp", -32, -64, 64, 96},
		{"src/player/D4.bmp", -32, -64, 64, 96},
		{"src/player/D5.bmp", -32, -64, 64, 96},
		{"src/player/D6.bmp", -32, -64, 64, 96},
		{"src/player/D7.bmp", -32, -64, 64, 96},
		{"src/player/D8.bmp", -32, -64, 64, 96}
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
	void turn(int dir);
	void showImg();
	void checkHealth();
private:
	Item *item[PLAYER_MAX_ITEM];
	int holding;
	int lHealthCounter;
};

#endif
