#ifndef ANIMATION_H
#define ANIMATION_H

#include "acllib.h"
#include "typename.h"

struct AnimForm
{
	int len, counter;
	double w, h;
	const char *img[20];
};

const AnimForm Monster_Death =
{
	7, 4, 88, 88,
	{
		"src/death/n0.bmp",
		"src/death/n1.bmp",
		"src/death/n2.bmp",
		"src/death/n3.bmp",
		"src/death/n4.bmp",
		"src/death/n5.bmp",
		"src/death/n6.bmp"
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
};

#endif
