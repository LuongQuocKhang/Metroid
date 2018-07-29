#pragma once
#include "BulletObject.h"
#include "Parameters.h"
#define BIRD_BULLET_COUNT 5
class BirdBullet : public BulletObject
{
protected:
	Bullet * bullets[BIRD_BULLET_COUNT];
public:
	BirdBullet(World * manager);
	BirdBullet(LPD3DXSPRITE, World*);
	~BirdBullet();

	void InitSprites(LPDIRECT3DDEVICE9 d3ddv);
	void Update(float t);
	void Render();
	void Shoot(BULLET_DIRECTION dir, float posX, float posY);
	void InitSprites(LPDIRECT3DDEVICE9 d3ddv, LPDIRECT3DTEXTURE9 image);
};

