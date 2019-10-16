#ifndef ARROW_H
#define ARROW_H

#include "acllib.h"
#include "item.h"
#include "bullet.h"
#include "player.h"

const char PIC_Arrow[4][40] =
{
	"src/arrow/arrowR.bmp",
	"src/arrow/arrowU.bmp",
	"src/arrow/arrowL.bmp",
	"src/arrow/arrowD.bmp"
};

class Arrow:
	public Item
{
public:
	Arrow();
	void effect();
};

#endif
