#pragma once
#include "Parameters.h"

class PosInfo
{
public:
	float x;
	float y;
	float width;
	float height;
	bool isActive;
	ENEMY_TYPE enemy_type;

	PosInfo();
	~PosInfo();
};

