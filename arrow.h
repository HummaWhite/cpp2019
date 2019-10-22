#ifndef ARROW_H
#define ARROW_H

#include "acllib.h"
#include "item.h"
#include "bullet.h"

const ImgForm Arrow_Img[4] =
{
	{"src/arrow/arrowR.bmp", -28, -10, 56, 20},
	{"src/arrow/arrowU.bmp", -10, -28, 20, 56},
	{"src/arrow/arrowL.bmp", -28, -10, 56, 20},
	{"src/arrow/arrowD.bmp", -10, -28, 20, 56},
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
