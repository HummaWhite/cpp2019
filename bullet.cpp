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

void Bullet::showDebugInfo(double _x, double _y)
{
	setPenColor(RED);
	setPenWidth(2);
	if (user != nullptr)
	{
		line(
				getX() - _x + W_Width / 2,
				getY() - _y + W_Height / 2,
				user->getX() - _x + W_Width / 2,
				user->getY() - _y + W_Height / 2
			);
	}
	showBox(_x, _y);
}
