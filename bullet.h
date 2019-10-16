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
	void reactWith(Entity *e);
private:
	int dir;
};

#endif
