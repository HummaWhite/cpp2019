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
	void setDir(int d);
	void attack(Entity *e);
	void reactWith(Entity *e);
	void showDebugInfo(double _x, double _y);
private:
	int dir;
};

#endif
