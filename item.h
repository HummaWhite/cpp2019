#ifndef ITEM_H
#define ITEM_H

#include <ctime>
#include <cstdio>

#include "acllib.h"
#include "typename.h"
#include "entity.h"

class Item
{
public:
	Item(int tp);
	~Item();
	int getType();
	void setOwner(Entity *o);
	Entity* getOwner();
	virtual void effect();
	void display();
private:
	int type;
	Entity *owner;
	ACL_Image itImg;
};

#endif
