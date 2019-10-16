#include "arrow.h"

Arrow::Arrow():
	Item(A_Arrow)
{
}

void Arrow::effect()
{
	Entity *host = getOwner();
	if (host->buf != nullptr) return;
	Bullet *tmp = new Bullet(A_Arrow);
	int dir = host->facing();
	tmp->setDir(dir);
	tmp->setPos(host->getX(), host->getY());
	if (dir == LEFT || dir == RIGHT) tmp->setScale(TP_INFO[A_Arrow].h, TP_INFO[A_Arrow].w);
	tmp->setImgPtr(PIC_Arrow[dir]);
	tmp->user = host;
	host->buf = tmp;
}
