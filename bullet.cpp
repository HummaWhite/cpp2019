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
		case N_Cucco:
			newAnim(Monster_Death, getX(), getY(), 1);
			break;
	}
}

void genSpreadBullet(Entity *user, int num)
{
	if (user == nullptr) return;
	for (int i = 0; i < num; i++)
	{
		Bullet *tmp = new Bullet(B_FireBall);
		tmp->setImg(ImgForm{"res/fireball/mid.bmp", -8, -8, 16, 16});
		tmp->setBox(BumpBox{-8, -8, 16, 16});
		tmp->setTrail((double)(2 * Pi / num * i), 0, 0, TP_INFO[B_FireBall].speed);
		tmp->setCpoint(user->getX(), user->getY());
		tmp->setPos(user->getX(), user->getY());
		tmp->user = user;
		tmp->target = nullptr;
		addSprite(tmp);
	}
}

void genRageCucco(Entity *rager, Entity *target)
{
	if (rager == nullptr || target == nullptr) return;
	Bullet *tmp = new Bullet(N_Cucco);
	tmp->setImg(ImgForm{"res/cucco/cucco_fR.bmp", -28, -32, 60, 64});
	tmp->setBox(BumpBox{-28, -32, 60, 64});
	double theta = 2 * Pi * ((double)(rand() % 300) / 300);
	if (theta < Pi / 2 || theta > Pi * 3 / 2 )
	{
		tmp->setImg(ImgForm{"res/cucco/cucco_fL.bmp", -28, -32, 60, 64});
	}
	tmp->setTrail(theta, 0, 800, -10);
	tmp->setCpoint(target->getX(), target->getY());
	tmp->setPos(target->getX() + 800 * cos(theta), target->getY() + 800 * sin(theta));
	tmp->user = rager;
	addSprite(tmp);
	sound("res/sound/Cucco_Fly.wav", 0);
}
