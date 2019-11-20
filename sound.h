#ifndef SOUND_H
#define SOUND_H

#include "acllib.h"

extern void sound(const char *soundPath, int opt);
extern void switchBGM(int id);

extern ACL_Sound BGM, curRegion;

const char BG_Music[3][40] =
{
	"src/sound/LightWorld.mid",
	"src/sound/Kakariko342.mid",
	"src/sound/LostWoods.mid"
};

#endif
