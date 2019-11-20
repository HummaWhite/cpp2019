#include "sword.h"

Sword::Sword(Entity *host):
	Entity(A_Sword)
{
	user = host;
	moveBehavior();
}

void Sword::moveBehavior()
{
	setPos(user->getX(), user->getY());
	int dir = user->facing();
	setImg(Sword_Img[dir]);
	setBox(Sword_Box[dir]);
	setFacingDir(dir);
}

void Sword::reactWith(Entity *e)
{
	if (!judgeCollision(this, e)) return;
	switch (e->category())
	{
		case C_Monster:
			attack(e);
			break;
	}
}
