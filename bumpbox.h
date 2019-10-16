#ifndef BUMPBOX_H
#define BUMPBOX_H

struct BumpBox
{
	double x, y;
	double w, h;
};

bool collide(BumpBox a, BumpBox b);

#endif
