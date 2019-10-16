#include "bullet.h"

Bullet::Bullet(int tp):
	Entity(tp)
{
}

void Bullet::moveBehavior()
{
	moveDir(dir);
}

void Bullet::setDir(int d)
{
	dir = d;
}

void Bullet::reactWith(Entity *e)
{
	if (!judgeCollision(this, e)) return;
	if (user == nullptr) return;
	switch (e->category())
	{
		case C_Player:
			if (user->category() == C_Player) break;
			attack(e);
			break;
		case C_Monster:
			if (user->category() == C_Monster) break;
			attack(e);
			break;
		case C_Wall:
			avoid(e);
			hurt(TP_INFO[getType()].health);
			break;
	}
}
