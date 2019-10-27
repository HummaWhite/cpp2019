#ifndef ANIMATION_H
#define ANIMATION_H

#include "acllib.h"
#include "typename.h"

struct AnimForm
{
	int len, counter;
	double w, h;
	const char *sound;
	const char *img[20];
};

const AnimForm Monster_Death =
{
	7, 4, 88, 88,
	"src/sound/Enemy_Kill.wav",
	{
		"src/anim/n0.bmp",
		"src/anim/n1.bmp",
		"src/anim/n2.bmp",
		"src/anim/n3.bmp",
		"src/anim/n4.bmp",
		"src/anim/n5.bmp",
		"src/anim/n6.bmp"
	}
};

const AnimForm Explode =
{
	8, 4, 172, 172,
	"src/sound/Bomb_Blow.wav",
	{
		"src/anim/b0.bmp",
		"src/anim/b1.bmp",
		"src/anim/b2.bmp",
		"src/anim/b3.bmp",
		"src/anim/b4.bmp",
		"src/anim/b5.bmp",
		"src/anim/b6.bmp",
		"src/anim/b7.bmp"
	}
};

struct Animation
{
	Animation(AnimForm a, double _x, double _y);
	double x, y;
	int curFrame, fCounter;
	AnimForm anim;
	void nextFrame();
	bool finished();
	void show(double _x, double _y);
	bool sounded;
};

#endif
