#pragma once
#include "GameObject.h"
#include "BulletManager.h"
#include "ExplosionEffect.h"
#include <time.h>
#include "MissileItem.h"
#include "EnergyItem.h"

#define SPRITE_PER_ROW 1
#define ANIMATE_RATE 7
#define ENEMY_FREEZE 500;

class Enemy : public GameObject
{
protected:
	ENEMY_TYPE enemy_type;
	SENTRY_TYPE sentry_type; //NEW
	
public:
	float time_freeze;	// thời gian dừng khi bị hit
	float health;		// Máu của object
	float damage;		// Lượng sát thương gây ra của object
	bool DeathByShoot;
	Enemy();
	Enemy(LPD3DXSPRITE spriteHandler, World * manager);
	~Enemy();
	virtual void InitPostition();
	virtual void InitPostition(int x, int y);
	virtual void InitSprites(LPDIRECT3DDEVICE9 d3ddv);

	ENEMY_TYPE GetEnemyType();
	void SetEnemyType(ENEMY_TYPE enemy_type);
	//============== OVERRIDE VIRTUAL METHOD ===============
	virtual void Render();
	virtual void Update(float t);
	virtual void TakeDamage(float damage);
	void Destroy();
	//virtual void Reset(int x, int y);	-- giữ mặc định không có modify nên không cần override
	//virtual void Destroy();			-- giữ mặc định không có modify nên không cần override
	//============== END OVERRIDE VIRTUAL METHOD ============
	
	//============== COLLISION VIRTUAL METHOD ================
	virtual void HandleCollision();		//-- dùng để handle va chạm với enemy và samus
	//============== END COLLISION VIRTUAL METHOD ===========
};

