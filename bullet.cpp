#include "bullet.h"

Bullet::Bullet(int tp):
	Entity(tp)
{
}

void Bullet::moveBehavior()
{
	setPos(cx + r * cos(t), cy - r * sin(t));
	t += dt, r += dr;
}

void Bullet::setCpoint(double _x, double _y)
{
	cx = _x, cy = _y;
}

void Bullet::setTrail(double _t, double _dt, double _r, double _dr)
{
	t = _t, dt = _dt;
	r = _r, dr = _dr;
}

void Bullet::attack(Entity *e)
{
	if (e == nullptr) return;
	e->hurt(TP_INFO[getType()].att);
	hurt(1000);
	e->attackedBehavior(this);
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
			hurt(1000);
			avoid(e);
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
