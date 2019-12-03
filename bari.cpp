#include "bari.h"

Bari::Bari():
	Entity(M_Bari)
{
	setImg(Bari_Img[0]);
	setBox(Bari_Box[0]);
	behaveCounter = rand() % 200;
	surroundDist = 320 + rand() % 80;
	cdist = rand() % 1200 + 500, crot = rand() % 800 + 1200;
}

void Bari::reactWith(Entity *e)
{
	if (!judgeCollision(this, e))
	{
		if (target == nullptr && dist(this, e) < 300)
		{
			if (e->category() == C_Player)
			{
				target = e;
				double x = getX(), y = getY(), tx = target->getX(), ty = target->getY();
				theta = acos(abs(x - tx) / dist(this, target));
				if (y < ty) theta = -theta;
				if (x < tx) theta = Pi - theta;
				dt = Pi / (80 + rand() % 130) * (rand() % 2 == 1 ? 1 : -1);
				setImg(Bari_Img[1]);
				setBox(Bari_Box[1]);
			}
		}
		return;
	}
	switch (e->category())
	{
		case C_Wall:
			if (target == nullptr) moveDir(e->facing());
			break;
		default:
			if (target == nullptr) avoid(e);
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
		if (behaveCounter == 0)
		{
			Bullet *tmp = new Bullet(B_FireBall);
			tmp->setImg(ImgForm{"res/fireball/big.bmp", -12, -12, 28, 28});
			tmp->setBox(BumpBox{-12, -12, 28, 28});
			tmp->setTrail(theta, -dt * 2, dist(this, target), -TP_INFO[B_FireBall].speed);
			tmp->setCpoint(target->getX(), target->getY());
			tmp->setPos(getX(), getY());
			tmp->user = this;
			addSprite(tmp);
			sound("res/sound/Zora_Fireball.wav", 0);
		}
		if (behaveCounter == 180)
		{
			setImg(Bari_Img[2]);
			setBox(Bari_Box[2]);
		}
		if (behaveCounter == 20)
		{
			setImg(Bari_Img[1]);
			setBox(Bari_Box[1]);
		}
	}
}

void Bari::surround(Entity *e)
{
	double d = surroundDist + 80 * sin((double)(clock() % cdist) / cdist * 2 * Pi);
	setPos(target->getX() + d * cos(theta), target->getY() + d * sin(theta));
	theta += dt + 0.9 * dt * sin((double)(clock() % crot) / crot * Pi * 2);
}

void Bari::die()
{
	genSpreadBullet(this, 12);
	newAnim(Explode, getX(), getY());
}
