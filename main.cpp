#include <ctime>
#include <cstdio>

#include "acllib.h"
#include "entity.h"
#include "player.h"
#include "moblin.h"
#include "slime.h"
#include "arrow.h"
#include "item.h"

const int Frame_Rate = 75;

bool keyPressing[200] = {0};
bool DEBUG_SHOWBOX = 0;

Entity *sprite[MAX_SPRITES];
Player *player;
ACL_Image BG_IMG;
ACL_Sound BGM, TMP;

void printItemBox()
{
	setPenColor(RGB(103, 136, 168));
	setPenWidth(20);
	setBrushColor(WHITE);
	rectangle(40, 520, 200, 680);
}

void printEvent()
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
	for (int i = 0; i < MAX_SPRITES; i++)
	{
		if (player->isDead()) continue;
		if (sprite[i] == nullptr) continue;
		sprite[i]->showImg(player->getX(), player->getY());
		if (DEBUG_SHOWBOX) sprite[i]->showDebugInfo(player->getX(), player->getY());
	}
	player->showImg();
	if (DEBUG_SHOWBOX) player->showDebugInfo(player->getX(), player->getY());
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
			case 'K':
				player->hurt(20);
				break;
			case 'B':
				DEBUG_SHOWBOX ^= 1;
				break;
			case 'Z':
				printf("get heart\n");
				player->getItem(I_Heart);
				break;
			case 'C':
				printf("use\n");
				player->useItem();
				break;
			case VK_SHIFT:
				printf("switch\n");
				player->switchItem();
				break;
			case 'X':
				printf("get arrow\n");
				if (player->haveItem(A_Arrow)) break;
				Arrow *tmp = new Arrow();
				player->getItem(tmp);
				break;
		}
		keyPressing[key] = 1;
	}
	if (event == KEY_UP) keyPressing[key] = 0;
}

int ddir = 0, dieCounter = 0, dying = 0;

void diePlayer()
{
	dieCounter++;
	if (dieCounter == 2)
	{
		dieCounter = 0;
		ddir = (ddir - 1 + 4) % 4;
		player->turn(ddir);
		player->turn(-1);
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

void nextEvent(int id)
{
	printEvent();
	if (player->isDead())
	{
		diePlayer();
		return;
	}
	player->checkHealth();
	if (player->buf != nullptr)
	{
		for (int i = 0; i < MAX_SPRITES; i++)
		{
			if (sprite[i] == nullptr)
			{
				sprite[i] = player->buf;
				player->buf = nullptr;
			}
		}
	}
	for (int i = 0; i < MAX_SPRITES; i++)
	{
		if (sprite[i] == nullptr) continue;
		if (sprite[i]->isDead())
		{
			switch (sprite[i]->category())
			{
				case C_Monster:
					loadSound("src/sound/Enemy_Kill.wav", &TMP);
					break;
				default:
					loadSound("", &TMP);
			}
			playSound(TMP, 0);
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
		sprite[i]->moveBehavior();
	}
	movePlayer();
}

void initSprite()
{
	sprite[0] = new Entity(-40, -40, Map_Width + 40, 0, DOWN);
	sprite[1] = new Entity(-40, Map_Height, Map_Width + 40, Map_Height + 40, UP);
	sprite[2] = new Entity(-40, -40, 0, Map_Height + 40, RIGHT);
	sprite[3] = new Entity(Map_Width, -40, Map_Width + 40, Map_Height + 40, LEFT);
	for (int i = 4; i < 60; i++)
	{
		sprite[i] = new Moblin();
		sprite[i]->setPos(rand() % (Map_Width) / 2, rand() % (Map_Height / 2));
	}
	for (int i = 60; i < 100; i++)
	{
		sprite[i] = new Slime();
		sprite[i]->setPos(rand() % (Map_Width) / 2, rand() % (Map_Height / 2));
	}
	player = new Player();
	player->setPos(W_Width / 2, W_Height / 2);
}

int Setup()
{
	initSprite();
	loadImage("src/light_world.jpg", &BG_IMG);
	loadSound("src/sound/LightWorld.mid", &BGM);
	playSound(BGM, 100);
	initWindow("test02", DEFAULT, DEFAULT, W_Width, W_Height);
	registerTimerEvent(nextEvent);
	registerMouseEvent(mouseEvent);
	registerKeyboardEvent(keyboardEvent);
	startTimer(0, 1000 / Frame_Rate);
	//startTimer(0, 200);
}
