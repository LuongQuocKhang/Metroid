#pragma once
#include "GameObject.h"
#include "Parameters.h"
class Brick: public GameObject
{
protected:
	int id;		// id của gạch trong spritesheet lấy ra từ MapEditor
	BRICK_TYPE brick_type;	// type của gạch. ví dụ: type = "1" -> generate ra BRICK_1_PATH, ...
	int width_count;
	int height_count;
	LPWSTR sprite_path;
	bool isPassable;	// có khả năng băng qua
public:
	Brick();
	Brick(LPD3DXSPRITE spriteHandler, World* manager, BRICK_TYPE type, int id, int posX, int posY);
	~Brick();

	void InitSprite();
	//============= GET - SET METHOD ======================
	int GetId();
	void SetId(int id);
	BRICK_TYPE GetBrickType();
	void SetPassable(bool value);
	bool IsPassable();
	//============= END GET - SET METHOD ==================

	//============= OVERRIDE VIRTUAL METHOD ===============
	void Update(float t);
	void Render();
	//============= END OVERRIDE VIRTUAL METHOD ===========
};

