#include "animation.h"

Animation* anim[MAX_ANIM] = {nullptr};

AnimForm::~AnimForm()
{
}

Animation::Animation(AnimForm a, double _x, double _y, bool _sounded)
{
	anim = a;
	curFrame = fCounter = 0;
	x = _x, y = _y;
	sounded = _sounded;
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

void Animation::show()
{
	if (curFrame == anim.len) return;
	loadImage(anim.img[curFrame], &tmpImg);
	putImageTransparent
	(
		&tmpImg,
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

void newAnim(AnimForm a, double x, double y, bool sounded)
{
	for (int i = 0; i < MAX_ANIM; i++)
	{
		if (anim[i] == nullptr)
		{
			anim[i] = new Animation(a, x, y, sounded);
			return;
		}
	}
}
