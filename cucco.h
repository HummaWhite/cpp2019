#ifndef CUCCO_H
#define CUCCO_H

#include "acllib.h"
#include "typename.h"
#include "entity.h"
#include "bullet.h"

class Cucco:
	public Entity
{
public:
	Cucco();
	void reactWith(Entity *e);
	void moveBehavior();
	void attackedBehavior(Entity *e);
private:
	double dx, dy;
	int moveCounter;
	int hitTime;
	bool rage;
	clock_t timeStartRage;
};

#endif
