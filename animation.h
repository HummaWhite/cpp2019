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
	"res/sound/Enemy_Kill.wav",
	{
		"res/anim/n0.bmp",
		"res/anim/n1.bmp",
		"res/anim/n2.bmp",
		"res/anim/n3.bmp",
		"res/anim/n4.bmp",
		"res/anim/n5.bmp",
		"res/anim/n6.bmp"
	}
};

const AnimForm Explode =
{
	8, 4, 172, 172,
	"res/sound/Bomb_Blow.wav",
	{
		"res/anim/b0.bmp",
		"res/anim/b1.bmp",
		"res/anim/b2.bmp",
		"res/anim/b3.bmp",
		"res/anim/b4.bmp",
		"res/anim/b5.bmp",
		"res/anim/b6.bmp",
		"res/anim/b7.bmp"
	}
};

const AnimForm Micro_Explode =
{
	3, 4, 56, 64,
	nullptr,
	{
		"res/anim/l_explode0.bmp",
		"res/anim/l_explode1.bmp",
		"res/anim/l_explode2.bmp"
	}
};

struct Animation
{
	Animation(AnimForm a, double _x, double _y, bool _sounded = 0);
	double x, y;
	int curFrame, fCounter;
	AnimForm anim;
	void nextFrame();
	bool finished();
	void show();
	bool sounded;
};

extern Animation* anim[MAX_ANIM];

extern void newAnim(AnimForm a, double x, double y, bool sounded = 0);

#endif
