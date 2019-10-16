#ifndef ENTITY_H
#define ENTITY_H

#include <cmath>
#include <ctime>
#include <cstdio>
#include "typename.h"
#include "acllib.h"
#include "bumpbox.h"

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
	double getW();
	double getH();
	void setSpeed(double speed);
	void setAtt(int _att);
	void setPos(double _x, double _y);
	void setScale(double _w, double _h);
	void moveDir(double dx, double dy);
	void moveDir(int dir);
	void moveToward(double _x, double _y);
	void moveToward(Entity *e);
	void avoid(Entity *e);
	void setFacingDir(int dir);
	int facing();
	virtual void moveBehavior();
	virtual void reactWith(Entity *e);
	void attack(Entity *e);
	virtual void attackedBehavior(Entity *e);
	void hurt(int att);
	void heal(int recv);
	bool isDead();
	int getHealth();
	virtual void showImg(double _x, double _y);
	virtual void showImg();
	void dispHealth();
	BumpBox getBox();
	void showBox(double _x, double _y);
	ACL_Image* getImgPtr();
	void setImgPtr(const char *path);
	Entity *buf;
	Entity *target;
	Entity *user;
private:
	double moveSpeed;
	double x, y;
	double w, h;
	int type;
	int health, maxHealth;
	int att;
	clock_t lstHurt, lstEffect;
	int facingDir;
	ACL_Image *img;
};

double dist(Entity *a, Entity *b);
bool judgeCollision(Entity *a, Entity *b);

#endif
