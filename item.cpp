#include "item.h"

Item::Item(int tp)
{
	img = (ACL_Image*)malloc(sizeof(ACL_Image));
	loadImage(TP_INFO[tp].imgPath, img);
	type = tp;
	owner = nullptr;
}

Item::~Item()
{
	freeImage(img);
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
	//host->setSpeed(TP_INFO[type].speed + TP_INFO[ownerType].speed);
}

void Item::display()
{
	setPenWidth(4);
	setPenColor(RED);
	setBrushColor(WHITE);
	rectangle(420, 40, 436 + TP_INFO[type].w, 56 + TP_INFO[type].h);
	putImageTransparent(img, 428, 48, TP_INFO[type].w, TP_INFO[type].h, BLUE);
}
