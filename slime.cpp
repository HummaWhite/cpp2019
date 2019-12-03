#include "slime.h"

Slime::Slime():
	Entity(M_Slime)
{
	moveCounter = rand() % 60;
	setFacingDir(rand() % 4);
	attentionDist = 200;
	setImg(ImgForm{"res/slime.bmp", -24, -22, 48, 44});
	setBox(BumpBox{-24, -22, 48, 44});
}

void Slime::reactWith(Entity *e)
{
	if (!judgeCollision(this, e))
	{
		if (e->category() == C_Player)
		{
			if (dist(this, e) < attentionDist) target = e;
		}
		return;
	}
	switch(e->category())
	{
		case C_Player:
			attack(e);
			avoid(e);
			break;
		case C_Wall:
			moveDir(e->facing());
			break;
		case C_Bullet:
			avoid(e);
			attack(e);
		default:
			avoid(e);
	}
}

void Slime::moveBehavior()
{
	moveCounter++;
	if (moveCounter == 60)
	{
		moveCounter = 0;
		dx = rand() % 100 - 50, dy = rand() % 100 - 50;
	}
	else if (moveCounter <= 40)
	{
		if (target == nullptr) moveDir(dx, dy);
		else moveToward(target);
	}
}

void Slime::showDebugInfo()
{
	setBrushColor(GREEN);
	ellipse
	(
		getX() - attentionDist - playerPosX + W_Width / 2,
		getY() - attentionDist - playerPosY + W_Height / 2,
		getX() + attentionDist - playerPosX + W_Width / 2,
		getY() + attentionDist - playerPosY + W_Height / 2
	);
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
	showBox();
}

void Slime::die()
{
	newAnim(Explode, getX(), getY());
}
