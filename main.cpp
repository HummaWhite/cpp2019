#include <ctime>
#include <cstdio>

#include "acllib.h"
#include "entity.h"
#include "player.h"
#include "moblin.h"
#include "slime.h"
#include "arrow.h"
#include "item.h"
#include "animation.h"
#include "cucco.h"
#include "bari.h"

const int Frame_Rate = 75;

bool keyPressing[200] = {0};
bool DEBUG_SHOWBOX = 0;

Entity *sprite[MAX_SPRITES] = {nullptr};
Player *player;
ACL_Image BG_IMG;
ACL_Sound BGM, TMP, curRegion;
Animation *anim[MAX_ANIM] = {nullptr};

void switchBGM(int id)
{
	stopSound(BGM);
	loadSound(BG_Music[id], &BGM);
	playSound(BGM, -1);
}

int inRegion()
{
	double x = player->getX();
	double y = player->getY();
	if (x < 4096 && y < 4096) return Woods;
	else if (x < 4096 && y >= 6144 && y < 10240) return Village;
	else return Over_World;
}

void newAnim(AnimForm a, double x, double y)
{
	for (int i = 0; i < MAX_ANIM; i++)
	{
		if (anim[i] == nullptr)
		{
			anim[i] = new Animation(a, x, y);
			return;
		}
	}
}

void paintAnim()
{
	for (int i = 0; i < MAX_ANIM; i++)
	{
		if (anim[i] != nullptr)
		{
			anim[i]->show(player->getX(), player->getY());
		}
	}
}

void paintSprite(Entity *e)
{
	if (e == nullptr) return;
	if (DEBUG_SHOWBOX) e->showDebugInfo(player->getX(), player->getY());
	if (abs(e->getX() - player->getX()) > W_Width + 160) return;
	if (abs(e->getY() - player->getY()) > W_Height + 160) return;
	e->showImg(player->getX(), player->getY());
}

void paintEvent()
{
	beginPaint();
	clearDevice();
	putImageScale(
			&BG_IMG,
			W_Width / 2 - player->getX(),
			W_Height / 2 - player->getY(),
			Map_Width,
			Map_Height
			);
	if (sprite[0] != nullptr)
	{
		if (sprite[0]->facing() == UP || sprite[0]->facing() == RIGHT) paintSprite(sprite[0]);
	}
	for (int i = 1; i < MAX_SPRITES; i++)
	{
		if (player->isDead()) continue;
		paintSprite(sprite[i]);
	}
	if (DEBUG_SHOWBOX) player->showDebugInfo(player->getX(), player->getY());
	player->showImg();
	if (sprite[0] != nullptr)
	{
		if (sprite[0]->facing() == DOWN || sprite[0]->facing() == LEFT) paintSprite(sprite[0]);
	}
	paintAnim();
	endPaint();
}

void mouseEvent(int x, int y, int button, int event)
{
}

void keyboardEvent(int key, int event)
{
	if (event == KEY_DOWN)
	{
		switch (key)
		{
			case 'Q':
				newAnim(Explode, player->getX() + rand() % 40 - 20, player->getY() + rand() % 40 - 20);
				player->hurt(8);
				break;
			case 'B':
				DEBUG_SHOWBOX ^= 1;
				break;
			case 'Z':
				player->getItem(I_Heart);
				break;
			case 'C':
				player->useItem();
				break;
			case VK_SPACE:
				if (keyPressing[VK_SPACE] || player->buf != nullptr || sprite[0] != nullptr) break;
				player->useSword();
				break;
			case VK_SHIFT:
				printf("switch\n");
				player->switchItem();
				break;
		}
		keyPressing[key] = 1;
	}
	if (event == KEY_UP) keyPressing[key] = 0;
	if (!keyPressing[VK_SPACE])
	{
		if (sprite[0] != nullptr)
		{
			delete sprite[0];
			sprite[0] = player->buf = nullptr;
		}
	}
}

int ddir = 0, dieCounter = 0, dying = 0;

void diePlayer()
{
	dieCounter++;
	if (dieCounter == 2)
	{
		ddir = (ddir - 1 + 4) % 4;
		player->turn(ddir);
		player->turn(-1);
		dieCounter = 0;
	}
	if (!dying)
	{
		loadSound("src/sound/Link_Dying.wav", &TMP);
		playSound(TMP, 0);
	}
	dying = 1;
}

void movePlayer()
{
	bool moving = 0;
	for (int i = 0; i < 4; i++)
	{
		if (keyPressing[arrowKey[i]])
		{
			player->moveDir(i);
			player->turn(i);
			moving = 1;
		}
	}
	if (!moving) player->turn(-1);
}

int lHealthCounter;

int frameCounter = 0, curTime = 0;

void nextEvent(int id)
{
	frameCounter++;
	if (clock() - curTime >= 1000)
	{
		curTime = clock();
		printf("%d\n", frameCounter);
		frameCounter = 0;
	}
	if (inRegion() != curRegion)
	{
		curRegion = inRegion();
		switchBGM(curRegion);
	}
	paintEvent();
	for (int i = 0; i < MAX_ANIM; i++)
	{
		if (anim[i] != nullptr)
		{
			if (anim[i]->finished())
			{
				delete anim[i];
				anim[i] = nullptr;
			}
			else anim[i]->nextFrame();
		}
	}
	if (player->isDead())
	{
		diePlayer();
		return;
	}
	player->checkHealth();
	if (player->buf != nullptr)
	{
		if (player->buf->category() != C_Armor)
		{
			for (int i = 1; i < MAX_SPRITES; i++)
			{
				if (sprite[i] == nullptr)
				{
					sprite[i] = player->buf;
					player->buf = nullptr;
					break;
				}
			}
		}
		else sprite[0] = player->buf;
	}
	for (int i = 0; i < MAX_SPRITES; i++)
	{
		if (sprite[i] == nullptr) continue;
		if (sprite[i]->isDead())
		{
			switch (sprite[i]->getType())
			{
				case M_Moblin:
					newAnim(Monster_Death, sprite[i]->getX(), sprite[i]->getY());
					break;
				case M_Bari:
					newAnim(Monster_Death, sprite[i]->getX(), sprite[i]->getY());
					break;
				case M_Slime:
					newAnim(Explode, sprite[i]->getX(), sprite[i]->getY());
					break;
			}
			delete sprite[i];
			sprite[i] = nullptr;
			continue;
		}
		sprite[i]->reactWith(player);
		player->reactWith(sprite[i]);
		for (int j = i + 1; j < MAX_SPRITES; j++)
		{
			if (sprite[j] == nullptr)
			{
				if (sprite[i]->buf != nullptr)
				{
					sprite[j] = sprite[i]->buf;
					sprite[i]->buf = nullptr;
				}
				continue;
			}
			sprite[i]->reactWith(sprite[j]);
			sprite[j]->reactWith(sprite[i]);
		}
		sprite[i]->moveBehavior();
	}
	movePlayer();
}

void initSprite()
{
	sprite[1] = new Entity(-40, -40, Map_Width + 40, 0, DOWN);
	sprite[2] = new Entity(-40, Map_Height, Map_Width + 40, Map_Height + 40, UP);
	sprite[3] = new Entity(-40, -40, 0, Map_Height + 40, RIGHT);
	sprite[4] = new Entity(Map_Width, -40, Map_Width + 40, Map_Height + 40, LEFT);
	for (int i = 5; i < 35; i++)
	{
		sprite[i] = new Moblin();
		sprite[i]->setPos(rand() % (Map_Width) / 2, rand() % (Map_Height / 2));
	}
	for (int i = 35; i < 65; i++)
	{
		sprite[i] = new Slime();
		sprite[i]->setPos(rand() % (Map_Width) / 2, rand() % (Map_Height / 2));
	}
	for (int i = 65; i < 85; i++)
	{
		sprite[i] = new Cucco();
		sprite[i]->setPos(rand() % (Map_Width) / 2, rand() % (Map_Height / 2));
	}
	for (int i = 85; i < 100; i++)
	{
		sprite[i] = new Bari();
		sprite[i]->setPos(rand() % (Map_Width) / 2, rand() % (Map_Height / 2));
	}
	sprite[99]->setPos(20, 20);
	player = new Player();
	player->setPos(W_Width / 2, W_Height / 2);
	Arrow *tmp = new Arrow();
	player->getItem(tmp);
}

int Setup()
{
	srand(time(NULL));
	initSprite();
	loadImage("src/light_world.jpg", &BG_IMG);
	switchBGM(inRegion());
	curRegion = inRegion();
	initWindow("test02", DEFAULT, DEFAULT, W_Width, W_Height);
	registerTimerEvent(nextEvent);
	registerMouseEvent(mouseEvent);
	registerKeyboardEvent(keyboardEvent);
	startTimer(0, 1000 / Frame_Rate);
	//startTimer(0, 200);
}
