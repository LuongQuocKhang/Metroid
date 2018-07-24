#include "Metroid.h"
#include <time.h>
#include "trace.h"
#include "utils.h"
#include "BulletManager.h"
#include "World.h"
#include "Samus.h"
#include "MorphItem.h"
#include "ExplosionEffect.h"
#include "BulletObject.h"

void Metroid::_InitBackground()
{
}

void Metroid::_InitSprites(LPDIRECT3DDEVICE9 d3ddv)
{
	world->InitSprites(d3ddv);
	//tiles->InitSprites(d3ddv);
	//intro = new Sprite(spriteHandler, INTRO_FILE, INTRO, 640, 640, 156, 1);
	//tiles->InitSprites(d3ddv);

}

void Metroid::_InitPositions()
{
	world->samus->InitPostition();
	world->morphItem->Init(704, 186);
	//world->hog_yellow->InitPostition(1350, 420);
	//world->hog_pink->InitPostition(1800, 110);
	//world->bird->InitPostition(1500, 410);
	//world->block->InitPostition(1664,32);
	//world->bee->InitPostition(1600, 410);
	//world->sentryLeft->InitPostition(1500, 350);
	//world->sentryTop->InitPostition(1700, 350);
	//world->sentryRight->InitPostition(1900, 350);
	//world->motherBrain->InitPostition(1400, 200);
	//world->ridley->InitPostition(1550, 120);

	//world->morphItem->SetPosX(world->samus->GetPosX());
	//world->morphItem->SetPosY(world->samus->GetPosX());
	//bulletManager->InitPosition(world->samus->GetPosX(), world->samus->GetPosY());
}


DWORD Metroid::GetTickPerFrame()
{
	return tick_per_frame;
}

DWORD Metroid::GetStart_jump()
{
	return this->start_jump;
}

DWORD Metroid::GetNow_jump()
{
	return this->now_jump;
}

void Metroid::SetStart_jump(DWORD startjump)
{
	this->start_jump = startjump;
}
void Metroid::SetNow_jump(DWORD nowjump)
{
	this->now_jump = nowjump;
}

DWORD Metroid::GetStart_shoot()
{
	return this->start_shoot;
}
DWORD Metroid::GetNow_shoot()
{
	return this->now_shoot;
}

void Metroid::SetStart_shoot(DWORD startshoot)
{
	this->start_shoot = startshoot;
}
void Metroid::SetNow_shoot(DWORD nowshoot)
{
	this->now_shoot = nowshoot;
}
void Metroid::_Shoot(BULLET_DIRECTION dir)
{
	now_shoot = GetTickCount();
	if (start_shoot <= 0) //if shooting is active
	{
		start_shoot = GetTickCount();
		world->bullets->Next(dir, world->samus->GetPosX(), world->samus->GetPosY());
	}
	else if ((now_shoot - start_shoot) > SHOOTING_SPEED * tick_per_frame)
	{
		//Reset start_shoot
		start_shoot = 0;
	}
}
void Metroid::_SetBoom(BULLET_DIRECTION dir)
{
	world->boom->Next(dir, world->samus->GetPosX(), world->samus->GetPosY());
}
void Metroid::_ShootMissile(BULLET_DIRECTION dir)
{
	world->missiles->Next(dir, world->samus->GetPosX(), world->samus->GetPosY());
}

Metroid::Metroid(HINSTANCE hInstance, LPWSTR Name, int Mode, int IsFullScreen, int FrameRate) :Game(hInstance, Name, Mode, IsFullScreen, FrameRate)
{
	//tiles = new Tiles();
	tick_per_frame = 1000 / _FrameRate;
	start_shoot = 0;

	time_jump = 3 * _DeltaTime;

	isFreezing = false;
	time_freezing = TIME_FREEZING;
	time_in_game = TIME_IN_GAME;
	isOnFloor = false;
	isInGame = false;

	//bulletManager = new BulletManager();
}


Metroid::~Metroid()
{
	//delete(tiles);

	//delete(bulletManager);

	delete(first_room);
	//delete(second_room);
	delete(room);
	delete(intro);
}

void Metroid::LoadResources(LPDIRECT3DDEVICE9 d3ddv)
{
	//---------Khởi tạo spriteHandler---------------
	if (d3ddv == NULL) return;
	//Create sprite handler
	HRESULT result = D3DXCreateSprite(d3ddv, &spriteHandler);
	if (result != D3D_OK) return;
	//-----------------------
	world = new World(spriteHandler, this);
	srand((unsigned)time(NULL));
	_InitSprites(d3ddv);
	_InitPositions();

	//room = new Loader(spriteHandler, 1, world);
	first_room = new Loader(spriteHandler, 1, world);
	//room->Load();
	//second_room = new Loader(spriteHandler, 2, world);
	first_room->Load();
	//second_room->Load();

	Game::gameSound->playSoundLoop(BACKGROUND_INTRO);
}

void Metroid::Update(float Delta)
{
	switch (screenMode)
	{
		// intro
	case GAMEMODE_INTRO:
		UpdateIntro(_DeltaTime);
		break;
		// start screen
	case GAMEMODE_START:
		break;
		// game running
	case GAMEMODE_GAMERUN:
		UpdateFrame(_DeltaTime);
		break;
		// game over
	case GAMEMODE_GAMEOVER:
	default:
		break;
	}
}

void Metroid::UpdateIntro(float Delta)
{
	//DWORD now = GetTickCount();
	//if (now - Delta  > 1000 / 100)
	//{
	//	intro->Next();
	//	Delta = now;
	//}
}

void Metroid::UpdateFrame(float Delta)
{
	if (isInGame)
	{
		for (int i = 0; i < 4; i++)
			world->hogs_yellow[i]->SetActive(true);
		time_in_game -= Delta;
		if (time_in_game <= 0)
		{
			Game::gameSound->stopSound(BACKGROUND_APPEARANCE);
			Game::gameSound->playSoundLoop(BACKGROUND_MAP);
			isInGame = false;
		}
	}

	if (isFreezing)
	{
		time_freezing -= Delta;
		if (time_freezing <= 0)
		{
			Game::gameSound->playSoundLoop(BACKGROUND_MAP);
			isFreezing = false;
			time_freezing = TIME_FREEZING;
		}
		return;
	}

	world->Update(Delta);
	//Camera::MoveCameraX(0.05f, Delta);
	//bulletManager->Update(Delta, world->samus->GetPosX(), world->samus->GetPosY());
	if (world->samus->isSamusDeath() == true)
	{
		screenMode = GAMEMODE_GAMEOVER;
		return;
	}
}

void Metroid::Render(LPDIRECT3DDEVICE9 d3ddv)
{
	switch (screenMode)
	{
		// intro
	case GAMEMODE_INTRO:
		RenderIntro(d3ddv);
		break;
		// start screen
	case GAMEMODE_START:
		RenderStartScreen(d3ddv);
		break;
		// game running
	case GAMEMODE_GAMERUN:
		RenderFrame(d3ddv);
		break;
		// game over
	case GAMEMODE_GAMEOVER:
		RenderGameOver(d3ddv);
	default:
		break;
	}
}

void Metroid::RenderStartScreen(LPDIRECT3DDEVICE9 d3ddv)
{
	// Background
	d3ddv->StretchRect(
		startscreen,		// from 
		NULL,				// which portion?
		_BackBuffer,		// to 
		NULL,				// which portion?
		D3DTEXF_NONE);
	startscreen = CreateSurfaceFromFile(_d3ddv, STARTSCREEN_FILE);
}

void Metroid::RenderIntro(LPDIRECT3DDEVICE9 d3ddv)
{
	//Camera::currentCamX = -310;
	//Camera::currentCamY = 250;
	//spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
	//intro->Render(0, 0);
	//spriteHandler->End();
	// Background
	d3ddv->StretchRect(
		introscreen,		// from 
		NULL,				// which portion?
		_BackBuffer,		// to 
		NULL,				// which portion?
		D3DTEXF_NONE);
	introscreen = CreateSurfaceFromFile(_d3ddv, INTROSCREEN_FILE);
}

void Metroid::RenderFrame(LPDIRECT3DDEVICE9 d3ddv)
{
	world->Render(d3ddv);

	if (isOnFloor)
		//second_room->TestRenderMapGO();
		first_room->TestRenderMapGO();
	//room->TestRenderMapGO();
	//first_room->TestRenderMapGO();
	//bulletManager->Render();
	//tiles->_Render(xc, world->samus->GetPosX());	
}

void Metroid::RenderGameOver(LPDIRECT3DDEVICE9 d3ddv)
{
	d3ddv->StretchRect(
		gameoverscreen,		// from 
		NULL,				// which portion?
		_BackBuffer,		// to 
		NULL,				// which portion?
		D3DTEXF_NONE);
	gameoverscreen = CreateSurfaceFromFile(_d3ddv, GAMEOVERSCREEN_FILE);
}

void Metroid::ProcessInput(LPDIRECT3DDEVICE9 d3ddv, float Delta)
{
	world->samus->ProcessInput(d3ddv, Delta, this);
}

void Metroid::OnKeyDown(int KeyCode)
{
	world->samus->OnkeyDown(KeyCode, this, screenMode);
}

void Metroid::OnKeyUp(int KeyCode)
{
	world->samus->OnKeyUp(KeyCode, this);
}