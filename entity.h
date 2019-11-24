#ifndef ENTITY_H
#define ENTITY_H

#include <cmath>
#include <ctime>
#include <cstdio>
#include "typename.h"
#include "acllib.h"
#include "bumpbox.h"
#include "sound.h"
#include "animation.h"

class Entity
{
public:
	Entity(int tp);
	Entity(double x1, double y1, double x2, double y2, int dir);
	~Entity();
	int getType();
	int category();
	double getX();
	double getY();
	void setSpeed(double speed);
	void setAtt(int _att);
	void setPos(double _x, double _y);
	void moveDir(double dx, double dy);
	void moveDir(int dir);
	void moveToward(double _x, double _y);
	void moveToward(Entity *e);
	void avoid(Entity *e);
	void setFacingDir(int dir);
	int facing();
	virtual void moveBehavior();
	virtual void reactWith(Entity *e);
	virtual void attack(Entity *e);
	virtual void attackedBehavior(Entity *e);
	void hurt(int att);
	virtual void hurtSound();
	virtual void heal(int recv);
	bool isDead();
	int getHealth();
	virtual void die();
	virtual void showImg();
	void dispHealth();
	BumpBox getBox();
	ImgForm getImg();
	void setBox(const BumpBox &_box);
	void setImg(const ImgForm &_img);
	void showBox();
	virtual void showDebugInfo();
	Entity *target;
	Entity *user;
private:
	double moveSpeed;
	double x, y;
	int type;
	int health, maxHealth;
	int att;
	int lstHurt, lstEffect;
	int facingDir;
	ImgForm img;
	BumpBox box;
};

double dist(Entity *a, Entity *b);
bool judgeCollision(Entity *a, Entity *b);
extern Entity* addSprite(Entity *spr);

extern Entity *sprite[MAX_SPRITES];

#endif
