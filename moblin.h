#ifndef MOBLIN_H
#define MOBLIN_H

#include "entity.h"

class Moblin:
	public Entity
{
public:
	Moblin();
	void reactWith(Entity *e);
	void moveBehavior();
	void attackedBehavior(Entity *e);
	void showDebugInfo(double _x, double _y);
private:
	int moveCounter;
};

#endif
