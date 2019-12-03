#ifndef ARROW_H
#define ARROW_H

#include "acllib.h"
#include "item.h"
#include "bullet.h"
#include "sound.h"

const ImgForm Arrow_Img[4] =
{
	{"res/arrow/arrowR.bmp", -28, -10, 56, 20},
	{"res/arrow/arrowD.bmp", -10, -28, 20, 56},
	{"res/arrow/arrowL.bmp", -28, -10, 56, 20},
	{"res/arrow/arrowU.bmp", -10, -28, 20, 56},
};

const BumpBox Arrow_Box[4] =
{
	{-28, -10, 56, 20},
	{-10, -28, 20, 56},
	{-28, -10, 56, 20},
	{-10, -28, 20, 56},
};

class Arrow:
	public Item
{
public:
	Arrow();
	void effect();
};

#endif
