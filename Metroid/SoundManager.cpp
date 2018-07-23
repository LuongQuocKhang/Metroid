#include "SoundManager.h"

SoundManager::SoundManager()
{
	g_pDS = NULL;
}

SoundManager::~SoundManager()
{
}

void SoundManager::LoadSound(HWND _hWnd)
{
	if (!InitDirectSound(_hWnd))
	{
		MessageBox(NULL, L"Unable to init DirectSound", L"ERROR", MB_OK);
	}
	DSBuffer[BACKGROUND_INTRO] = LoadWaveToSoundBuffer(L"Resources\\sound\\background\\Intro.wav");
	DSBuffer[BACKGROUND_APPEARANCE] = LoadWaveToSoundBuffer(L"Resources\\sound\\background\\Appearance.wav");
	DSBuffer[BACKGROUND_MOTHER_BRAIN_BOSS] = LoadWaveToSoundBuffer(L"Resources\\sound\\background\\Brain Mother.wav");
	DSBuffer[BACKGROUND_MAP] = LoadWaveToSoundBuffer(L"Resources\\sound\\background\\Map.wav");
	//No-Use DSBuffer[BACKGROUND_KRAID_LAIR] = LoadWaveToSoundBuffer(L"Resources\\sound\\background\\Kraid's Lair.wav");
	DSBuffer[BACKGROUND_RIDLEY_LAIR] = LoadWaveToSoundBuffer(L"Resources\\sound\\background\\Ridley's Lair.wav");
	DSBuffer[BACKGROUND_ITEM_ACQUIRED] = LoadWaveToSoundBuffer(L"Resources\\sound\\background\\Item acquired.wav");
	DSBuffer[BACKGROUND_SAMUS_DEATH] = LoadWaveToSoundBuffer(L"Resources\\sound\\background\\samus_death.wav");
	DSBuffer[BACKGROUND_MOTHER_BRAIN_DEATH] = LoadWaveToSoundBuffer(L"Resources\\sound\\background\\mother_brain_death.wav");

	DSBuffer[JUMP] = LoadWaveToSoundBuffer(L"Resources\\sound\\sfx\\jump.wav");
	DSBuffer[BULLET_HIT_ENEMY] = LoadWaveToSoundBuffer(L"Resources\\sound\\sfx\\butllet_hit_enemy.wav");
	DSBuffer[SAMUS_HIT_LIFE_POINT] = LoadWaveToSoundBuffer(L"Resources\\sound\\sfx\\samus_hit_life_point.wav");
	DSBuffer[SAMUS_HIT_ENEMY] = LoadWaveToSoundBuffer(L"Resources\\sound\\sfx\\samus_hit_enemy.wav");
	DSBuffer[SHOOT_BULLET] = LoadWaveToSoundBuffer(L"Resources\\sound\\sfx\\bullet.wav");
	DSBuffer[SHOOT_MISSILE] = LoadWaveToSoundBuffer(L"Resources\\sound\\sfx\\missile.wav");

	if (!DSBuffer)
	{
		MessageBox(NULL, L"Unable to load sound", L"ERROR", MB_OK);
	}
}

bool SoundManager::InitDirectSound(HWND hwnd)
{
	HRESULT hr;

	hr = DirectSoundCreate8(NULL, &g_pDS, NULL);
	if FAILED(hr)
		return false;

	// Set DirectSound cooperative level 
	hr = g_pDS->SetCooperativeLevel(hwnd, DSSCL_PRIORITY);
	if FAILED(hr)
		return false;

	return true;
}

void SoundManager::shutdownDirectSound()
{
	if (DSBuffer)
	{

		for (int i = 0; i < 30; i++)
		{
			if (DSBuffer[i] != NULL)
			{
				DSBuffer[i]->Release();
				DSBuffer[i] = NULL;
			}
		}
		//delete DSBuffer;
	}
	if (g_pDS)
	{
		g_pDS->Release();
		g_pDS = NULL;
	}
}

LPDIRECTSOUNDBUFFER SoundManager::LoadWaveToSoundBuffer(LPTSTR filename)
{
	LPDIRECTSOUNDBUFFER apDSBuffer = NULL;
	CWaveFile *wavFile;
	HRESULT hr;

	wavFile = new CWaveFile();
	wavFile->Open(filename, NULL, WAVEFILE_READ);


	DSBUFFERDESC dsbd;
	ZeroMemory(&dsbd, sizeof(DSBUFFERDESC));
	dsbd.dwSize = sizeof(DSBUFFERDESC);
	dsbd.dwFlags = 0;
	dsbd.dwBufferBytes = wavFile->GetSize();
	dsbd.guid3DAlgorithm = GUID_NULL;
	dsbd.lpwfxFormat = wavFile->m_pwfx;

	hr = g_pDS->CreateSoundBuffer(&dsbd, &apDSBuffer, NULL);
	if FAILED(hr)
	{
		MessageBox(NULL, L"unable to create sound buffer", L"ERROR", MB_OK);
		return NULL;
	}

	VOID*   pDSLockedBuffer = NULL; // Pointer to locked buffer memory
	DWORD   dwDSLockedBufferSize = 0;    // Size of the locked DirectSound buffer
	DWORD   dwWavDataRead = 0;    // Amount of data read from the wav file 

	hr = apDSBuffer->Lock(0, wavFile->GetSize(),
		&pDSLockedBuffer, &dwDSLockedBufferSize,
		NULL, NULL, 0L);
	if FAILED(hr)
		return NULL;

	// Reset the wave file to the beginning 
	wavFile->ResetFile();

	// Read the wave file
	hr = wavFile->Read((BYTE*)pDSLockedBuffer,
		dwDSLockedBufferSize,
		&dwWavDataRead);
	// Check to make sure that this was successful
	if FAILED(hr)
		return NULL;

	// Check to make sure the wav file is not empty
	if (dwWavDataRead == 0)
	{
		// Wav is blank, so just fill with silence
		FillMemory((BYTE*)pDSLockedBuffer,
			dwDSLockedBufferSize,
			(BYTE)(wavFile->m_pwfx->wBitsPerSample == 8 ? 128 : 0));
	}
	else if (dwWavDataRead < dwDSLockedBufferSize)
	{
		// Don't repeat the wav file, just fill in silence 
		FillMemory((BYTE*)pDSLockedBuffer + dwWavDataRead,
			dwDSLockedBufferSize - dwWavDataRead,
			(BYTE)(wavFile->m_pwfx->wBitsPerSample == 8 ? 128 : 0));
	}

	// Unlock the buffer, we don't need it anymore.
	apDSBuffer->Unlock(pDSLockedBuffer, dwDSLockedBufferSize, NULL, 0);

	// Clean up
	delete wavFile;

	return apDSBuffer;
}

void SoundManager::playSound(int ID)
{
	DSBuffer[ID]->Play(0, 0, 0);
}

void SoundManager::playSoundLoop(int ID)
{
	DSBuffer[ID]->Play(0, 0, DSBPLAY_LOOPING);
}

void SoundManager::stopSound(int ID)
{
	DSBuffer[ID]->Stop();
}
