#include "bari.h"

Bari::Bari():
	Entity(M_Bari)
{
	setImg(ImgForm{"src/bari.bmp", -32, -32, 64, 64});
	setBox(BumpBox{-32, -32, 64, 64});
	behaveCounter = rand() % 200;
}

void Bari::reactWith(Entity *e)
{
	if (!judgeCollision(this, e))
	{
		if (target == nullptr && dist(this, e) < 400)
		{
			if (e->category() == C_Player)
			{
				target = e;
				setSpeed(6);
			}
		}
		return;
	}
	switch (e->category())
	{
		case C_Wall:
			moveDir(e->facing());
			break;
		default:
			avoid(e);
	}
}

void Bari::moveBehavior()
{
	behaveCounter++;
	if (behaveCounter == 200) behaveCounter = 0;
	if (target == nullptr)
	{
		if (behaveCounter % 100 == 0) setFacingDir(rand() % 4);
		moveDir(facing());
	}
	else
	{
		surround(target);
		if (dist(this, target) > 375) moveToward(target);
		else if (dist(this, target) < 325) avoid(target);
		if (behaveCounter == 0 && buf == nullptr)
		{
			Bullet *tmp = new Bullet(B_FireBall);
			tmp->setImg(ImgForm{"src/fireball/big.bmp", -12, -12, 28, 28});
			tmp->setBox(BumpBox{-12, -12, 28, 28});
			double x = getX(), y = getY(), tx = target->getX(), ty = target->getY();
			double theta = acos(abs(x - tx) / dist(this, target));
			if (ty < y) theta = -theta;
			if (tx < x) theta = Pi - theta;
			tmp->setTrail(theta, 0, 0, TP_INFO[B_FireBall].speed);
			tmp->setCpoint(getX(), getY());
			tmp->setPos(getX(), getY());
			tmp->user = this;
			buf = tmp;
			ACL_Sound bctmp;
			loadSound("src/sound/Zora_Fireball.wav", &bctmp);
			playSound(bctmp, 0);
		}
	}
}

void Bari::surround(Entity *e)
{
	double dx = getX() - e->getX();
	double dy = getY() - e->getY();
	moveDir(-dy, dx);
}
