#pragma once
#ifndef _BULLETOBJECT_H_
#define _BULLETOBJECT_H_

#define SPEED 0.6f
#define LIMIT_DISTANCE 150

#include "GameObject.h"
#include "Parameters.h"

class BulletObject : public GameObject
{
protected:
	int pos_x_holder;
	int pos_y_holder;

	int limit_dist_x;		//limit distance of x
	int limit_dist_y;		//limit distance of y;

	World * manager;
	BULLET_TYPE bulletType;

	LPD3DXSPRITE _SpriteHandler;
	BULLET_DIRECTION direction;
public:
	float damage;		// Lượng sát thương gây ra của BulletObject

	BulletObject();
	BulletObject(World * manager);
	~BulletObject();
	
	void InitPosition(int posX, int posY);
	void ResetPosition();
	
	BULLET_DIRECTION GetDirection();
	void SetDirection(BULLET_DIRECTION value);

	BULLET_TYPE getBulletType()
	{
		return this->bulletType;
	}
	void setBulletType(BULLET_TYPE type)
	{
		this->bulletType = type;
	}

	//============ VIRTUAL METHOD =================
	virtual void InitSprites(LPDIRECT3DDEVICE9 d3ddv);
	virtual void Update(float t);
	virtual void Render();
	virtual void Shoot(BULLET_DIRECTION dir);
	virtual void Shoot(BULLET_DIRECTION dir, float posX, float posY);
	virtual void Reset();
	//============ END VIRTUAL METHOD =============
};
#endif

