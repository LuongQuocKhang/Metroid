#pragma once
#include "Effect.h"
class ExplosionEffect :
	public Effect
{
public:
	ExplosionEffect(LPD3DXSPRITE spriteHandler, World *manager);
	//ExplosionEffect();
	~ExplosionEffect();

	void InitSprites(LPDIRECT3DDEVICE9 d3ddv);
};

