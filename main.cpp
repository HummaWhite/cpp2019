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
#include "sound.h"

const int Frame_Rate = 75;

bool keyPressing[200];
bool DEBUG_SHOWBOX = 0;
bool DEBUG_FREEZE = 0;


Player *player;
ACL_Image BG_IMG, tmpImg;

double playerPosX, playerPosY;

int inRegion()
{
	double x = player->getX();
	double y = player->getY();
	if (x < 4096 && y < 4096) return Woods;
	else if (x < 4096 && y >= 6144 && y < 10240) return Village;
	else return Over_World;
}

void paintAnim()
{
	for (int i = 0; i < MAX_ANIM; i++)
	{
		if (anim[i] != nullptr)
		{
			anim[i]->show();
		}
	}
}

void paintSprite(Entity *e)
{
	if (e == nullptr) return;
	if (DEBUG_SHOWBOX) e->showDebugInfo();
	if (abs(e->getX() - player->getX()) > W_Width + 160) return;
	if (abs(e->getY() - player->getY()) > W_Height + 160) return;
	e->showImg();
}

void paintEvent()
{
	beginPaint();
	clearDevice();
	putImageScale
	(
		&BG_IMG,
		W_Width / 2 - playerPosX,
		W_Height / 2 - playerPosY,
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
	if (DEBUG_SHOWBOX) player->showDebugInfo();
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
			case 'E':
				genSpreadBullet(player, 120);
				break;
			case 'Q':
				newAnim(Explode, player->getX() + rand() % 40 - 20, player->getY() + rand() % 40 - 20);
				player->hurt(8);
				break;
			case 'B':
				DEBUG_SHOWBOX ^= 1;
				break;
			case 'P':
				DEBUG_FREEZE ^= 1;
				break;
			case 'Z':
				player->getItem(I_Heart);
				break;
			case 'C':
				player->useItem();
				break;
			case VK_SHIFT:
				printf("switch\n");
				player->switchItem();
				break;
		}
		keyPressing[key] = 1;
	}
	if (event == KEY_UP) keyPressing[key] = 0;
}

void animEvent()
{
	if (DEBUG_FREEZE) return;
	for (int i = 0; i < MAX_ANIM; i++)
	{
		if (anim[i] != nullptr)
		{;
			if (anim[i]->finished())
			{
				delete anim[i];
				anim[i] = nullptr;
			}
			else anim[i]->nextFrame();
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
	if (!dying) sound("res/sound/Link_Dying.wav", 0);
	dying = 1;
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
	animEvent();
	if (player->isDead())
	{
		diePlayer();
		return;
	}
	player->checkHealth();
	for (int i = 0; i < MAX_SPRITES; i++)
	{
		if (sprite[i] == nullptr) continue;
		if (sprite[i]->isDead())
		{
			sprite[i]->die();
			delete sprite[i];
			sprite[i] = nullptr;
			continue;
		}
		sprite[i]->reactWith(player);
		player->reactWith(sprite[i]);
		for (int j = i + 1; j < MAX_SPRITES; j++)
		{
			if (sprite[j] == nullptr) continue;
			sprite[i]->reactWith(sprite[j]);
			sprite[j]->reactWith(sprite[i]);
		}
		if (DEBUG_FREEZE) continue;
		sprite[i]->moveBehavior();
	}
	player->moveBehavior();
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
	loadImage("res/light_world.jpg", &BG_IMG);
	switchBGM(inRegion());
	curRegion = inRegion();
	initWindow("test02", DEFAULT, DEFAULT, W_Width, W_Height);
	registerTimerEvent(nextEvent);
	registerMouseEvent(mouseEvent);
	registerKeyboardEvent(keyboardEvent);
	startTimer(0, 1000 / Frame_Rate);
}
