#ifndef SLIME_H
#define SLIME_H

#include "typename.h"
#include "entity.h"

class Slime:
	public Entity
{
public:
	Slime();
	void reactWith(Entity *e);
	void moveBehavior();
	void showDebugInfo();
	void die();
private:
	int moveCounter;
	double dx, dy;
	double attentionDist;
};

#endif
