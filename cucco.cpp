#include "cucco.h"

Cucco::Cucco():
	Entity(N_Cucco)
{
	setImg(ImgForm{"res/cucco/cucco.bmp", -32, -32, 64, 76});
	setBox(BumpBox{-32, -32, 64, 76});
	hitTime = 0;
	rage = 0;
	moveCounter = 0;
}

void Cucco::reactWith(Entity *e)
{
	if (!judgeCollision(this, e)) return;
	switch (e->category())
	{
		case C_Wall:
			moveDir(e->facing());
			break;
		default:
			avoid(e);
	}
}

void Cucco::moveBehavior()
{
	moveCounter++;
	if (moveCounter == 90)
	{
		dx = rand() % 100 - 50, dy = rand() % 100 - 50;
		moveCounter = 0;
	}
	if (target == nullptr)
	{
		if (moveCounter < 30 && (moveCounter / 2) % 4 != 0) moveDir(dx, dy);
		return;
	}
	if (!rage)
	{
		if (dist(target, this) > 600)
		{
			target = nullptr;
			setSpeed(TP_INFO[N_Cucco].speed);
		}
		else avoid(target);
	}
	else
	{
		clock_t curTime = clock();
		if (curTime - timeStartRage > 15 * CLOCKS_PER_SEC)
		{
			rage = 0;
			return;
		}
		if (moveCounter % 15 == 0) genRageCucco(this, target);
	}
}

void Cucco::attackedBehavior(Entity *e)
{
	Entity *tmp = (e->category() == C_Bullet || e->category() == C_Armor) ? e->user : e;
	if (target == nullptr)
	{
		target = tmp;
		setSpeed(5);
	}
	heal(100);
	if (rage) return;
	if (tmp != target) hitTime = 0;
	else
	{
		hitTime++;
		if (hitTime == 10)
		{
			rage = 1;
			hitTime = 0;
			timeStartRage = clock();
		}
	}
}
