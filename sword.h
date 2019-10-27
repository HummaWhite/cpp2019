#ifndef SWORD_H
#define SWORD_H

#include "acllib.h"
#include "typename.h"
#include "entity.h"

const ImgForm Sword_Img[4] =
{
	{"src/sword/swordR.bmp", 4, -4, 52, 24},
	{"src/sword/swordD.bmp", 0, 12, 24, 52},
	{"src/sword/swordL.bmp", -56, -4, 52, 24},
	{"src/sword/swordU.bmp", -24, -68, 24, 52}
};

const BumpBox Sword_Box[4] =
{
	{4, -4, 52, 24},
	{0, 12, 24, 52},
	{-56, -4, 52, 24},
	{-24, -68, 24, 52}
};

class Sword:
	public Entity
{
public:
	Sword();
	void moveBehavior();
	void reactWith(Entity *e);
};

#endif
