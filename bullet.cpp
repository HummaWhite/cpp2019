#include "bullet.h"

Bullet::Bullet(int tp):
	Entity(tp)
{
}

void Bullet::moveBehavior()
{
	setPos(cx + r * cos(t), cy + r * sin(t));
	t += dt, r += dr;
	if (dist(this, user) > 2000) hurt(1000);
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
		case C_Armor:
			hurt(1000);
			avoid(e);
			break;
		case C_Wall:
			hurt(1000);
			avoid(e);
			break;
	}
}

void Bullet::die()
{
	switch(getType())
	{
		case B_FireBall:
			newAnim(Micro_Explode, getX(), getY());
			break;
	}
}
