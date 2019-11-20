#include "animation.h"

Animation* anim[MAX_ANIM] = {nullptr};

AnimForm::~AnimForm()
{
}

Animation::Animation(AnimForm a, double _x, double _y)
{
	anim = a;
	curFrame = fCounter = 0;
	x = _x, y = _y;
	sounded = 0;
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

void Animation::show()
{
	if (curFrame == anim.len) return;
	loadImage(anim.img[curFrame], &atmp);
	putImageTransparent(
			&atmp,
			x - anim.w / 2 - playerPosX + W_Width / 2,
			y - anim.h / 2 - playerPosY + W_Height / 2,
			anim.w,
			anim.h,
			BLUE
			);
	if (sounded) return;
	sound(anim.sound, 0);
	sounded = 1;
}

void newAnim(AnimForm a, double x, double y)
{
	for (int i = 0; i < MAX_ANIM; i++)
	{
		if (anim[i] == nullptr)
		{
			anim[i] = new Animation(a, x, y);
			return;
		}
	}
}
