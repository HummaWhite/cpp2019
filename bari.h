#ifndef BARI_H
#define BARI_H

#include "acllib.h"
#include "entity.h"
#include "bullet.h"
#include "typename.h"

class Bari:
	public Entity
{
public:
	Bari();
	void reactWith(Entity *e);
	void moveBehavior();
	void surround(Entity *e);
private:
	int behaveCounter;
};

#endif
