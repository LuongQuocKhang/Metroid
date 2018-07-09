#pragma once
#include "GameObject.h"
class QTreeObject
{
public:
	int x1, y1;
	int x2, y2;
	GameObject *target;

	QTreeObject();
	~QTreeObject();
};

