#ifndef BARI_H
#define BARI_H

#include "acllib.h"
#include "entity.h"
#include "bullet.h"
#include "typename.h"
#include "sound.h"

const ImgForm Bari_Img[3] =
{
	{"res/bari/bari.bmp", -32, -32, 64, 64},
	{"res/bari/bari_s.bmp", -28, -28, 56, 60},
	{"res/bari/bari_r.bmp", -36, -32, 72, 68}
};

const BumpBox Bari_Box[3] =
{
	{-32, -32, 64, 64},
	{-28, -28, 56, 60},
	{-36, -32, 72, 68}
};

class Bari:
	public Entity
{
public:
	Bari();
	void reactWith(Entity *e);
	void moveBehavior();
	void surround(Entity *e);
	void die();
private:
	int behaveCounter;
	double surroundDist;
	double theta, dt;
	int cdist, crot;
};

#endif
