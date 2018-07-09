#pragma once
#include "BulletObject.h"
#include "Parameters.h"
class SentryBullet : public BulletObject
{
protected:
	Sprite * up;
	Sprite * left;
	Sprite * right;
	Sprite * bottom;
	Sprite * topleft;
	Sprite * topright;
	Sprite * bottomleft;
	Sprite * bottomright;
public:
	SentryBullet(World * manager);
	~SentryBullet();
	void InitSprites(LPDIRECT3DDEVICE9 d3ddv);
	void Update(float t);
	void Render();
	void Shoot(BULLET_DIRECTION dir, float posX, float posY);
};

