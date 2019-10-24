#include "player.h"
#include "acllib.h"

int animCounter = 0;

Player::Player():
	Entity(P_Player)
{
	holding = 0;
	for (int i = 0; i < PLAYER_MAX_ITEM; i++) item[i] = nullptr;
	setImg(Player_Img[DOWN][0]);
	setBox(Player_Box[DOWN]);
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
		case C_Monster:
			avoid(e);
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

void Player::useSword()
{
	if (buf != nullptr) return;
	Sword *swd = new Sword();
	int dir = facing();
	swd->setImg(Sword_Img[dir]);
	swd->setBox(Sword_Box[dir]);
	swd->setPos(getX(), getY());
	swd->user = this;
	buf = swd;
	ACL_Sound ctmp;
	loadSound("src/sound/Sword.wav", &ctmp);
	playSound(ctmp, 0);
}

void Player::switchItem()
{
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
	if (dir == -1)
	{
		setImg(Player_Img[facing()][0]);
		animCounter = 0;
		return;
	}
	setFacingDir(dir);
	setBox(Player_Box[dir]);
	animCounter++;
	if (animCounter >= 16) animCounter = 0;
	setImg(Player_Img[dir][animCounter / 2 + 1]);
}

ACL_Image itmp;

void Player::showImg()
{
	ImgForm _img = getImg();
	loadImage(_img.path, &itmp);
	putImageTransparent(&itmp, W_Width / 2 + _img.x, W_Height / 2 + _img.y, _img.w, _img.h, BLUE);
	for (int i = 2; i <= 40; i += 2)
	{
		if (getHealth() >= i)
		{
			loadImage("src/heart/heart_full.bmp", &itmp);
		}
		else if (getHealth() == i - 1)
		{
			loadImage("src/heart/heart_half.bmp", &itmp);
		}
		else
		{
			loadImage("src/heart/heart_empty.bmp", &itmp);
		}
		putImageTransparent(&itmp, 40 + 36 * ((i / 2 - 1) % 10), 40 + 32 * (i / 2 > 10), 32, 28, BLUE);
	}
	if (item[holding] != nullptr) item[holding]->display();
}

void Player::checkHealth()
{
	if (getHealth() == 0 || getHealth() > 3) return;
	if (lHealthCounter >= 30 * getHealth())
	{
		lHealthCounter = 0;
		ACL_Sound ctmp;
		loadSound("src/sound/LowHealth.wav", &ctmp);
		playSound(ctmp, 0);
	}
	lHealthCounter++;
}
