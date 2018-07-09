#include "ExplosionEffect.h"



//ExplosionEffect::ExplosionEffect() : Effect()
//{
//	effect_type = EXPLOSION;
//}

ExplosionEffect::ExplosionEffect(LPD3DXSPRITE spriteHandler, World *manager) : Effect(spriteHandler, manager)
{
	effect_type = EXPLOSION;
}

ExplosionEffect::~ExplosionEffect()
{
}

void ExplosionEffect::InitSprites(LPDIRECT3DDEVICE9 d3ddv)
{
	Effect::InitSprites(d3ddv);

	effectSprite = new Sprite(spriteHandler, EFFECT_SPRITE_PATH, EFFECT_EXPLOSION, EFFECT_EXPLOSION_WIDTH, EFFECT_EXPLOSION_HEIGHT, EFFECT_EXPLOSION_COUNT, 1);
}
