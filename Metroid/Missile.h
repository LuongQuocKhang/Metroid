#pragma once
#ifndef _MISSILE_H_
#define _MISSILE_H_

#include "GameObject.h"
#include "Sprite.h"
#include "Parameters.h"
#include "BulletObject.h"

#define MISSILE_SPRITE_PATH L"sprites\\bullet\\missile.png"
#define MISSILE_UP_SPRITE "sprites\\bullet\\MISSILE_UP.txt"
#define MISSILE_LEFT_SPRITE "sprites\\bullet\\MISSILE_LEFT.txt"
#define MISSILE_RIGHT_SPRITE "sprites\\bullet\\MISSILE_RIGHT.txt"


#define MISSILE_WIDTH 26
#define MISSILE_HEIGHT 20


#define MISSILE_UP_WIDTH 20
#define MISSILE_UP_HEIGHT 26

#define MISSILE_COUNT 1
#define SPRITE_PER_ROW 1

#define SPEED 0.3f
#define LIMIT_DISTANCE 200


class Missile : public BulletObject
{
private:
	
	Sprite * missile_up;
	Sprite * missile_left;
	Sprite * missile_right;

public:

	Missile(World * manager);
	Missile(World * manager, int x_holder, int y_holder);
	~Missile();

	void InitSprites(LPDIRECT3DDEVICE9 d3ddv);
	
	void Render();
};

#endif // !_BULLET_H

