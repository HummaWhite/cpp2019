#ifndef PLAYER_H
#define PLAYER_H

#include <cstdio>
#include <ctime>
#include "typename.h"
#include "entity.h"
#include "item.h"

#define PLAYER_MAX_ITEM 5

const char ANIM_Player[4][2][40] =
{
	{"src/player/walkR.bmp", "src/player/walkR1.bmp"},
	{"src/player/walkU.bmp", "src/player/walkU1.bmp"},
	{"src/player/walkL.bmp", "src/player/walkL1.bmp"},
	{"src/player/walkD.bmp", "src/player/walkD1.bmp"}
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
	void switchItem();
	bool haveItem(int tp);
	void turn(int dir);
	void showImg();
private:
	Item *item[PLAYER_MAX_ITEM];
	int holding;
};

#endif
