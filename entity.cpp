#include "entity.h"

Entity::Entity(int tp)
{
	moveSpeed = TP_INFO[tp].speed;
	maxHealth = health = TP_INFO[tp].health;
	att = TP_INFO[tp].att;
	type = tp;
	lstHurt = 0;
	lstEffect = -1000;
	buf = nullptr;
	target = nullptr;
	user = nullptr;
	facingDir = DOWN;
}

Entity::Entity(double x1, double y1, double x2, double y2, int dir)
{
	x = (x1 + x2) / 2, y = (y1 + y2) / 2;
	setBox(BumpBox{x1 - x, y1 - y, x2 - x1, y2 - y1});
	facingDir = dir;
	type = B_Wall;
}

Entity::~Entity()
{
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
	avoid(e);
}

void Entity::hurt(int att)
{
	int curTime = clock();
	if (curTime - lstHurt < 1000) return;
	health -= att;
	if (health < 0) health = 0;
	lstHurt = curTime;
	hurtSound();
}

void Entity::hurtSound()
{
	ACL_Sound stmp;
	switch (category())
	{
		case C_Monster:
			loadSound("src/sound/Enemy_Hit.wav", &stmp);
			break;
		case C_Player:
			loadSound("src/sound/Link_Hurt.wav", &stmp);
			break;
		default:
			loadSound("", &stmp);
	}
	playSound(stmp, 0);
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

ACL_Image tmp;

void Entity::showImg(double _x, double _y)
{
	if (type == B_Wall) return;
	loadImage(img.path, &tmp);
	putImageTransparent(&tmp, x - _x + W_Width / 2 + img.x, y - _y + W_Height / 2 + img.y, img.w, img.h, BLUE);
}

void Entity::showImg()
{
	if (type == B_Wall) return;
	showImg(W_Width / 2, W_Height / 2);
}

void Entity::dispHealth(double _x, double _y)
{
	_x -= W_Width / 2 - 20, _y -= W_Height / 2 - 20;
	setPenColor(BLUE);
	setBrushColor(WHITE);
	setPenWidth(1);
	rectangle(x - 1 - _x, y - 25 - _y, x + 40 + 1 - _x, y - 20 - _y);
	setBrushColor(GREEN);
	setPenColor(GREEN);
	rectangle(x - _x, y - 24 - _y, x + (double)(health > 0 ? health : 0) / maxHealth * 40 - _x, y - 21 - _y);
}

BumpBox Entity::getBox()
{
	return BumpBox{x + box.x, y + box.y, box.w, box.h};
}

ImgForm Entity::getImg()
{
	return img;
}

void Entity::setBox(const BumpBox &_box)
{
	box = _box;
}

void Entity::setImg(const ImgForm &_img)
{
	img = _img;
}

void Entity::showBox(double _x, double _y)
{
	dispHealth(_x, _y);
	setPenColor(YELLOW);
	setBrushColor(YELLOW);
	BumpBox _box = getBox();
	rectangle(
			_box.x - _x + W_Width / 2,
			_box.y - _y + W_Height / 2,
			_box.x - _x + W_Width / 2 + _box.w,
			_box.y - _y + W_Height / 2 + _box.h
			);
}

void Entity::showDebugInfo(double _x, double _y)
{
	showBox(_x, _y);
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
