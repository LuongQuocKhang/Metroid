#ifndef _EFFECT_H_
#define _EFFECT_H_

#include "GameObject.h"
#include "Parameters.h"

class Effect :
	public GameObject
{
protected :
	EFFECT_TYPE effect_type;
	float time_survive;
	Sprite * effectSprite;
public:
	//Effect();
	Effect(LPD3DXSPRITE spriteHandler, World *manager);
	~Effect();

	void InitSprites(LPDIRECT3DDEVICE9 d3ddv);
	void Init(int pos_x, int pos_y);

	virtual void Update(const float Deltatime);
	virtual void Render();

	// create new effect
	static Effect* CreateEffect(EFFECT_TYPE effectType, int pos_x, int pos_y, int heso, LPD3DXSPRITE spriteHandler, World *_manager);
};
#endif // !_EFFECT_H_

