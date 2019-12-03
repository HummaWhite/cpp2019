#include "item.h"

Item::Item(int tp)
{
	loadImage(TP_INFO[tp].imgPath, &itImg);
	type = tp;
	owner = nullptr;
}

Item::~Item()
{
}

int Item::getType()
{
	return type;
}

void Item::setOwner(Entity *o)
{
	owner = o;
}

Entity* Item::getOwner()
{
	return owner;
}

void Item::effect()
{
	clock_t curTime = clock();
	Entity *host = getOwner();
	if (host == nullptr) return;
	int ownerType = host->getType();
	host->heal(TP_INFO[type].health);
}

void Item::display()
{
	setPenWidth(4);
	setPenColor(RGB(220, 160, 0));
	setBrushColor(BLACK);
	rectangle(1080, 40, 1096 + TP_INFO[type].w, 56 + TP_INFO[type].h);
	putImageTransparent(&itImg, 1088, 48, TP_INFO[type].w, TP_INFO[type].h, BLUE);
}
