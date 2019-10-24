#include "moblin.h"

Moblin::Moblin():
	Entity(M_Moblin)
{
	moveCounter = rand() % 80;
	setFacingDir(rand() % 4);
	setImg(ImgForm{"src/moblin0.bmp", -32, -32, 64, 64});
	setBox(BumpBox{-32, -32, 64, 64});
}

void Moblin::reactWith(Entity *e)
{
	if (!judgeCollision(this, e)) return;
	switch (e->category())
	{
		case C_Player:
			attack(e);
			avoid(e);
			break;
		case C_Bullet:
			avoid(e);
			break;
		case C_Wall:
			moveDir(e->facing());
			break;
		default:
			avoid(e);
	}
}

void Moblin::moveBehavior()
{
	if (target == nullptr)
	{
		moveCounter++;
		if (moveCounter == 80)
		{
			moveCounter = 0;
			setFacingDir(rand() % 4);
		}
		else if (moveCounter < 40) moveDir(facing());
	}
	else moveToward(target);
}

void Moblin::attackedBehavior(Entity *e)
{
	switch (e->category())
	{
		case C_Bullet:
			avoid(e);
			attack(e);
			if (target != nullptr) break;
			target = e->user;
			setSpeed(3);
			break;
		case C_Armor:
			avoid(e);
			if (target != nullptr) break;
			target = e->user;
			setSpeed(3);
			break;
		default:
			avoid(e);
	}
}

void Moblin::showDebugInfo(double _x, double _y)
{
	if (target != nullptr)
	{
		setPenColor(RED);
		setPenWidth(2);
		line(
				getX() - _x + W_Width / 2,
				getY() - _y + W_Height / 2,
				target->getX() - _x + W_Width / 2,
				target->getY() - _y + W_Height / 2
			);
	}
	showBox(_x, _y);
}
