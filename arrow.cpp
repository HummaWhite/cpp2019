#include "arrow.h"

Arrow::Arrow():
	Item(A_Arrow)
{
}

ACL_Sound stmp;

void Arrow::effect()
{
	Entity *host = getOwner();
	if (host == nullptr) return;
	Bullet *tmp = new Bullet(A_Arrow);
	int dir = host->facing();
	tmp->setImg(Arrow_Img[dir]);
	tmp->setBox(Arrow_Box[dir]);
	tmp->setCpoint(host->getX(), host->getY());
	tmp->setTrail(dir * Pi / 2, 0, 0, TP_INFO[A_Arrow].speed);
	tmp->setPos(host->getX(), host->getY());
	tmp->user = host;
	addSprite(tmp);
	sound("res/sound/Arrow_Shoot.wav", 0);
}
