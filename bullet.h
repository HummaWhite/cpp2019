#ifndef BULLET_H
#define BULLET_H

#include <cmath>
#include "typename.h"
#include "entity.h"

class Bullet:
	public Entity
{
public:
	Bullet(int tp);
	void moveBehavior();
	void setCpoint(double _x, double _y);
	void setTrail(double _t, double _dt, double _r, double _dr);
	void attack(Entity *e);
	void reactWith(Entity *e);
private:
	double t, dt, r, dr;
	double cx, cy;
};

#endif
