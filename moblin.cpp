#include "moblin.h"

Moblin::Moblin():
	Entity(M_Moblin)
{
	moveCounter = rand() % 80;
	setFacingDir(rand() % 4);
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
		case C_Armor:
			avoid(e);
			break;
		case C_Bullet:
			attack(e);
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
			if (target != nullptr) break;
			target = e->user;
			break;
		case C_Armor:
			if (target != nullptr) break;
			target = e->user;
			break;
		default:
			avoid(e);
	}
}
