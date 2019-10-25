#include "animation.h"

Animation::Animation(AnimForm a, double _x, double _y)
{
	anim = a;
	curFrame = fCounter = 0;
	x = _x, y = _y;
}

void Animation::nextFrame()
{
	fCounter++;
	if (fCounter == anim.counter)
	{
		fCounter = 0;
		curFrame++;
	}
}

bool Animation::finished()
{
	return curFrame == anim.len;
}

ACL_Image atmp;

void Animation::show(double _x, double _y)
{
	if (curFrame == anim.len) return;
	loadImage(anim.img[curFrame], &atmp);
	putImageTransparent(
			&atmp,
			x - anim.w / 2 - _x + W_Width / 2,
			y - anim.h / 2 - _y + W_Height / 2,
			anim.w,
			anim.h,
			BLUE
			);
}
