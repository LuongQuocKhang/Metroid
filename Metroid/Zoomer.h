#pragma once
#include "Enemy.h"

#define ENEMY_SHEET_PATH L"sprites\\enemy\\metroid_enemies_sheet.png"

#define ZOOMER_UP "sprites\\enemy\\ZOOMER_UP.txt"
#define ZOOMER_LEFT "sprites\\enemy\\ZOOMER_LEFT.txt"
#define ZOOMER_RIGHT "sprites\\enemy\\ZOOMER_RIGHT.txt"
#define ZOOMER_BOTTOM "sprites\\enemy\\ZOOMER_BOTTOM.txt"

#define ZOOMER_BOTTOM_WIDTH 64
#define ZOOMER_BOTTOM_HEIGHT 64
#define ZOOMER_RIGHT_WIDTH 64
#define ZOOMER_RIGHT_HEIGHT 64
#define ZOOMER_LEFT_WIDTH 64
#define ZOOMER_LEFT_HEIGHT 64
#define ZOOMER_UP_WIDTH 40
#define ZOOMER_UP_HEIGHT 32

#define ZOOMER_COUNT 2

class Zoomer :
	public Enemy
{
	Sprite* zoomer_up;
	Sprite* zoomer_left;
	Sprite* zoomer_right;
	Sprite* zoomer_bottom;
public:
	Zoomer();
	Zoomer(LPD3DXSPRITE spriteHandler, World * manager);
	~Zoomer();

	void InitSprites(LPDIRECT3DDEVICE9 d3ddv);
	void InitPostition();
	void InitPostition(int x , int y);

	void Render();
	void Update(int t);


	void HandleCollision();
};

