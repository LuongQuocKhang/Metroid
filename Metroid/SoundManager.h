#pragma once

#ifndef __SOUND_MANAGER__
#define __SOUND_MANAGER__

//#include <dxerr.h>
#include <dsound.h>
#include "dsutil.h"
#include "Parameters.h"
#include <map>

using namespace std;

enum eSoundId
{
	// Nhạc nền intro
	BACKGROUND_INTRO,

	//Nhạc nền Apprearance
	BACKGROUND_APPEARANCE,

	// Nhạc nền map
	BACKGROUND_MAP,

	// Nhạc nền boss MOTHER BRAIN
	BACKGROUND_MOTHER_BRAIN_BOSS,

	//Nhạc nền boss KRAID
	BACKGROUND_KRAID_LAIR,

	//Nhạc nền boss RIDLEY
	BACKGROUND_RIDLEY_LAIR,

	//Nhạc nền nhặt Item
	BACKGROUND_ITEM_ACQUIRED,

	//Nhạc nền Samus chết
	BACKGROUND_SAMUS_DEATH,

	//Nhạc nền Mother Brain chết
	BACKGROUND_MOTHER_BRAIN_DEATH,

	// Nhảy
	JUMP,

	// Bắn đạn thường
	SHOOT_BULLET,

	// Bắn Missile
	SHOOT_MISSILE,

	// Đạn hit enemy
	BULLET_HIT_ENEMY,

	// Samus hit enemy
	SAMUS_HIT_ENEMY,

	// Samus hit life point
	SAMUS_HIT_LIFE_POINT,
};

class SoundManager
{
public:
	LPDIRECTSOUND8        g_pDS;
	//-----Các loại âm thanh
	LPDIRECTSOUNDBUFFER DSBuffer[30];

	SoundManager();
	~SoundManager();
	void LoadSound(HWND hWnd);
	bool InitDirectSound(HWND hwnd);
	void shutdownDirectSound();
	LPDIRECTSOUNDBUFFER LoadWaveToSoundBuffer(LPTSTR wavFilename);
	void playSound(int ID);
	void playSoundLoop(int ID);
	void stopSound(int ID);
};

#endif // !__SOUND_MANAGER__
