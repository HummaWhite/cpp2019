#include "bumpbox.h"

bool collide(BumpBox a, BumpBox b)
{
	if (b.x > a.x)
	{
		if (a.x + a.w <= b.x) return 0;
		else
		{
			if (b.y > a.y) return a.y + a.h > b.y;
			else return b.y + b.h > a.y;
		}
	}
	else
	{
		if (b.x + b.w <= a.x) return 0;
		else
		{
			if (b.y > a.y) return a.y + a.h > b.y;
			else return b.y + b.h > a.y;
		}
	}
}
