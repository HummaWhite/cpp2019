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
	if (host->buf != nullptr) return;
	Bullet *tmp = new Bullet(A_Arrow);
	int dir = host->facing();
	tmp->setDir(dir);
	tmp->setPos(host->getX(), host->getY());
	tmp->setImg(Arrow_Img[dir]);
	tmp->setBox(Arrow_Box[dir]);
	tmp->user = host;
	host->buf = tmp;
	loadSound("src/sound/Arrow_Shoot.wav", &stmp);
	playSound(stmp, 0);
}
