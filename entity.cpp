#include "entity.h"

Entity *sprite[MAX_SPRITES] = {nullptr};

Entity::Entity(int tp)
{
	moveSpeed = TP_INFO[tp].speed;
	maxHealth = health = TP_INFO[tp].health;
	att = TP_INFO[tp].att;
	type = tp;
	lstHurt = 0;
	lstEffect = -1000;
	target = nullptr;
	user = nullptr;
	facingDir = DOWN;
}

Entity::Entity(double x1, double y1, double x2, double y2, int dir)
{
	x = (x1 + x2) / 2, y = (y1 + y2) / 2;
	setBox(BumpBox{x1 - x, y1 - y, x2 - x1, y2 - y1});
	facingDir = dir;
	type = M_Wall;
	target = user = nullptr;
	maxHealth = health = 1000;
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
	moveDir(!(dir & 1) ? 1 - dir : 0, dir & 1 ? 2 - dir : 0);
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
			if (getType() != N_Cucco) sound("res/sound/Enemy_Hit.wav", 0);
			else sound("res/sound/Cucco.wav", 0);
			break;
		case C_Player:
			sound("res/sound/Link_Hurt.wav", 0);
			break;
	}
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

void Entity::die()
{
}

void Entity::showImg()
{
	if (type == M_Wall) return;
	loadImage(img.path, &tmpImg);
	putImageTransparent(&tmpImg, x - playerPosX + W_Width / 2 + img.x, y - playerPosY + W_Height / 2 + img.y, img.w, img.h, BLUE);
}

void Entity::dispHealth()
{
	double relX = playerPosX + 20 - W_Width / 2;
	double relY = playerPosY + 20 - W_Height / 2;
	setPenColor(BLUE);
	setBrushColor(WHITE);
	setPenWidth(1);
	rectangle(x - 1 - relX, y - 25 - relY, x + 40 + 1 - relX, y - 20 - relY);
	setBrushColor(GREEN);
	setPenColor(GREEN);
	rectangle(x - relX, y - 24 - relY, x + (double)(health > 0 ? health : 0) / maxHealth * 40 - relX, y - 21 - relY);
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

void Entity::showBox()
{
	dispHealth();
	setPenColor(YELLOW);
	setBrushColor(YELLOW);
	BumpBox _box = getBox();
	rectangle
	(
		_box.x - playerPosX	+ W_Width / 2,
		_box.y - playerPosY + W_Height / 2,
		_box.x - playerPosX + W_Width / 2 + _box.w,
		_box.y - playerPosY + W_Height / 2 + _box.h
	);
}

void Entity::showDebugInfo()
{
	if (target != nullptr)
	{
		setPenColor(RED);
		setPenWidth(2);
		line
		(
			getX() - playerPosX + W_Width / 2,
			getY() - playerPosY + W_Height / 2,
			target->getX() - playerPosX + W_Width / 2,
			target->getY() - playerPosY + W_Height / 2
		);
	}
	setPenColor(BLUE);
	if (user != nullptr)
	{
		line
		(
			getX() - playerPosX + W_Width / 2,
			getY() - playerPosY + W_Height / 2,
			user->getX() - playerPosX + W_Width / 2,
			user->getY() - playerPosY + W_Height / 2
		);
	}
	showBox();
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

Entity* addSprite(Entity *spr)
{
	if (spr == nullptr) return nullptr;
	bool added = 0;
	for (int i = 1; i < MAX_SPRITES; i++)
	{
		if (sprite[i] == nullptr)
		{
			sprite[i] = spr;
			added = 1;
			return sprite[i];
		}
	}
	if (!added) return nullptr;
}
