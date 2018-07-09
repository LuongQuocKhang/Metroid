#include "Effect.h"
#include "ExplosionEffect.h"


//Effect::Effect()
//{
//}

Effect::Effect(LPD3DXSPRITE spriteHandler, World * manager)
{
	this->spriteHandler = spriteHandler;
	this->manager = manager;
	type = EFFECT;
	time_survive = EFFECT_TIME_SURVIVE;
	isActive = false;

	vx = 0;
	vy = 0;
}


Effect::~Effect()
{
	delete(effectSprite);
}

void Effect::InitSprites(LPDIRECT3DDEVICE9 d3ddv)
{
	if (d3ddv == NULL) return;
	//Create sprite handler
	HRESULT result = D3DXCreateSprite(d3ddv, &spriteHandler);
	if (result != D3D_OK) return;
}

void Effect::Init(int pos_x, int pos_y)
{
	this->isActive = true;
	this->pos_x = pos_x;
	this->pos_y = pos_y;
	time_survive = EFFECT_TIME_SURVIVE;
}

void Effect::Update(const float Deltatime)
{
	DWORD now = GetTickCount();
	if (now - last_time > 1000 / ANIMATE_RATE)
	{
		effectSprite->Next();
		last_time = now;
	}

	// Tính thời gian hiển thị
	time_survive -= Deltatime;
	// Nếu hết thời gian thì không hiển thị nữa
	if (time_survive <= 0)
	{
		isActive = false;
	}
}

void Effect::Render()
{
	if (!isActive)
		return;

	spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
	effectSprite->Render(pos_x, pos_y);
	spriteHandler->End();
}

Effect * Effect::CreateEffect(EFFECT_TYPE effectType, int pos_x, int pos_y, int param, LPD3DXSPRITE spriteHandler, World * manager)
{
	Effect* effect = new Effect(spriteHandler, manager);

	switch (effectType)
	{
		case EXPLOSION :
			effect = new ExplosionEffect(spriteHandler,manager);
			effect->Init(pos_x, pos_y);
			break;
		default :
			break;
	}

	return effect;
}
