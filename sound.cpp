#include "sound.h"

ACL_Sound BGM, curRegion;

void sound(const char *soundPath, int opt)
{
	if (soundPath == nullptr) return;
	ACL_Sound tmpSound;
	loadSound(soundPath, &tmpSound);
	playSound(tmpSound, opt);
}

void switchBGM(int id)
{
	stopSound(BGM);
	loadSound(BG_Music[id], &BGM);
	playSound(BGM, -1);
}
