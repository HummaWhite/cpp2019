#ifndef ANIMATION_H
#define ANIMATION_H

#include "acllib.h"
#include "typename.h"
#include "sound.h"

struct AnimForm
{
	int len, counter;
	double w, h;
	const char *sound;
	const char *img[20];
	~AnimForm();
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

const AnimForm Micro_Explode =
{
	3, 4, 56, 64,
	nullptr,
	{
		"src/anim/l_explode0.bmp",
		"src/anim/l_explode1.bmp",
		"src/anim/l_explode2.bmp"
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
	void show();
	bool sounded;
};

extern Animation* anim[MAX_ANIM];

extern void newAnim(AnimForm a, double x, double y);

#endif
