#include "player.h"
#include "acllib.h"

int animCounter = 0;

Player::Player():
	Entity(P_Player)
{
	holding = 0;
	for (int i = 0; i < PLAYER_MAX_ITEM; i++) item[i] = nullptr;
}

Player::~Player()
{
	for (int i = 0; i < PLAYER_MAX_ITEM; i++)
	{
		delete item[i];
		item[i] = nullptr;
	}
}

void Player::reactWith(Entity *e)
{
	if (!judgeCollision(this, e)) return;
	switch (e->category())
	{
		case C_Bullet:
			if (e->user == this) break;
			else attack(e);
			break;
		case C_Armor:
			if (e->user == this) break;
			else avoid(e);
			break;
		case C_Wall:
			moveDir(e->facing());
			break;
		default:
			avoid(e);
	}
}

void Player::getItem(int tp)
{
	for (int i = 0; i < PLAYER_MAX_ITEM; i++)
	{
		if (item[i] == nullptr)
		{
			item[i] = new Item(tp);
			item[i]->setOwner(this);
			break;
		}
	}
}

void Player::getItem(Item *it)
{
	if (it == nullptr) return;
	for (int i = 0; i < PLAYER_MAX_ITEM; i++)
	{
		if (item[i] == nullptr)
		{
			item[i] = it;
			it->setOwner(this);
			break;
		}
	}
}

void Player::useItem()
{
	if (item[holding] == nullptr) return;
	item[holding]->effect();
	if (item[holding]->getType() != A_Arrow)
	{
		delete item[holding];
		item[holding] = nullptr;
	}
}

void Player::switchItem()
{
	/*int tmp = (holding - 1 + PLAYER_MAX_ITEM) % PLAYER_MAX_ITEM;
	while (holding != tmp && item[holding] == nullptr)
	{
		holding++;
		if (holding == PLAYER_MAX_ITEM) holding = 0;
	}*/
	holding = (holding + 1) % PLAYER_MAX_ITEM;
	for (int i = 0; i < PLAYER_MAX_ITEM; i++) printf("%d ", item[i] == nullptr ? 0 : item[i]->getType());
	printf("\n");
	for (int i = 0; i < PLAYER_MAX_ITEM; i++) printf("%c ", i == holding ? '^' : ' ');
	printf("\n");
}

bool Player::haveItem(int tp)
{
	for (int i = 0; i < PLAYER_MAX_ITEM; i++)
	{
		if (item[i] != nullptr)
		{
			if (item[i]->getType() == tp)
			{
				return 1;
			}
		}
	}
	return 0;
}

void Player::turn(int dir)
{
	setFacingDir(dir);
	animCounter = (animCounter + 1) % 16;
	setImgPtr(ANIM_Player[dir][animCounter > 8]);
}

void Player::showImg()
{
	putImageTransparent(getImgPtr(), (W_Width - getW()) / 2, (W_Height - getH()) / 2, getW(), getH(), BLUE);
	ACL_Image tmp;
	for (int i = 1; i <= 20; i++)
	{
		if (getHealth() >= i)
		{
			loadImage("src/heart/heart_full.bmp", &tmp);
			putImageTransparent(&tmp, 40 + 36 * ((i - 1) % 10), 40 + 32 * (i > 10), 32, 28, BLUE);
		}
		else
		{
			loadImage("src/heart/heart_empty.bmp", &tmp);
			putImageTransparent(&tmp, 40 + 36 * ((i - 1) % 10), 40 + 32 * (i > 10), 32, 28, BLUE);
		}
	}
	if (item[holding] != nullptr) item[holding]->display();
}
