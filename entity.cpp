#include "entity.h"

Entity::Entity(int tp)
{
	img = (ACL_Image*)malloc(sizeof(ACL_Image));
	loadImage(TP_INFO[tp].imgPath, img);
	w = TP_INFO[tp].w;
	h = TP_INFO[tp].h;
	moveSpeed = TP_INFO[tp].speed;
	maxHealth = health = TP_INFO[tp].health;
	att = TP_INFO[tp].att;
	type = tp;
	lstHurt = 0;
	lstEffect = clock() - (clock_t)100 * CLOCKS_PER_SEC;
	buf = nullptr;
	target = nullptr;
	facingDir = DOWN;
}

Entity::Entity(double x1, double y1, double x2, double y2, int dir)
{
	img = nullptr;
	x = (x1 + x2) / 2, y = (y1 + y2) / 2;
	w = x2 - x1, h = y2 - y1;
	facingDir = dir;
	type = B_Wall;
}

Entity::~Entity()
{
	freeImage(img);
}

int Entity::getType()
{
	return type;
}

int Entity::category()
{
	return TP_INFO[type].category;
}

double Entity::getX()
{
	return x;
}

double Entity::getY()
{
	return y;
}

double Entity::getW()
{
	return w;
}

double Entity::getH()
{
	return h;
}

void Entity::setSpeed(double speed)
{
	moveSpeed = speed;
}

void Entity::setAtt(int _att)
{
	att = _att;
}

void Entity::setPos(double _x, double _y)
{
	x = _x, y = _y;
}

void Entity::setScale(double _w, double _h)
{
	w = _w, h = _h;
}

void Entity::moveDir(double dx, double dy)
{
	double dl = sqrt(dx * dx + dy * dy);
	if (abs(dl) < EPS) return;
	x += moveSpeed / dl * dx;
	y += moveSpeed / dl * dy;
}

void Entity::moveDir(int dir)
{
	moveDir(!(dir & 1) ? 1 - dir : 0, dir & 1 ? dir - 2 : 0);
}

void Entity::moveToward(double _x, double _y)
{
	moveDir(_x - x, _y - y);
}

void Entity::moveToward(Entity *e)
{
	if (e == nullptr) return;
	moveToward(e->getX(), e->getY());
}

void Entity::avoid(Entity *e)
{
	if (e == nullptr) return;
	moveDir(x - e->getX(), y - e->getY());
}

void Entity::setFacingDir(int dir)
{
	facingDir = dir;
}

int Entity::facing()
{
	return facingDir;
}

void Entity::moveBehavior()
{
}

void Entity::reactWith(Entity *e)
{
}

void Entity::attack(Entity *e)
{
	if (e == nullptr) return;
	e->hurt(att);
	e->attackedBehavior(this);
}

void Entity::attackedBehavior(Entity *e)
{
}

void Entity::hurt(int att)
{
	clock_t curTime = clock();
	if ((double)(curTime - lstHurt) / CLOCKS_PER_SEC < 1.0) return;
	health -= att;
	lstHurt = curTime;
}

void Entity::heal(int recv)
{
	health += recv;
	if (health > maxHealth) health = maxHealth;
}

bool Entity::isDead()
{
	return health <= 0;
}

int Entity::getHealth()
{
	return health;
}

void Entity::showImg(double _x, double _y)
{
	if (type == B_Wall) return;
	putImageTransparent(img, x - _x + (W_Width - w) / 2, y - _y + (W_Height - h) / 2, w, h, BLUE);
}

void Entity::showImg()
{
	if (type == B_Wall) return;
	showImg(W_Width / 2, W_Height / 2);
}

void Entity::dispHealth()
{
	setPenColor(BLUE);
	setBrushColor(WHITE);
	setPenWidth(1);
	rectangle(x - 1, y - 25, x + w + 1, y - 20);
	setBrushColor(GREEN);
	setPenColor(GREEN);
	rectangle(x, y - 24, x + (double)(health > 0 ? health : 0) / maxHealth * w, y - 21);
}

BumpBox Entity::getBox()
{
	return BumpBox{x - w / 2, y - h / 2, w, h};
}

void Entity::showBox(double _x, double _y)
{
	setPenColor(BLUE);
	setBrushColor(BLUE);
	rectangle(x - _x + (W_Width - w) / 2, y - _y + (W_Height - h) / 2, x - _x + (W_Width + w) / 2, y - _y + (W_Height + h) / 2);
}

ACL_Image* Entity::getImgPtr()
{
	return img;
}

void Entity::setImgPtr(const char *path)
{
	loadImage(path, img);
}

double dist(Entity *a, Entity *b)
{
	if (a == nullptr || b == nullptr) return -1;
	return sqrt((a->getX() - b->getX()) * (a->getX() - b->getX()) + (a->getY() - b->getY()) * (a->getY() - b->getY()));
}

bool judgeCollision(Entity *a, Entity *b)
{
	if (a == nullptr || b == nullptr) 0;
	return collide(a->getBox(), b->getBox());
}
