﻿#pragma once
#include <map>
#include "QNode.h"

#define QUADTREE_FILE "quadtree\\map.txt";

/*
CLASS KHÔNG SỬ DỤNG
*/

using namespace std;
class QuadTree
{
public:
	map<int, QNode*> mapQuadtree;

	QuadTree();
	~QuadTree();

	void LoadNodeFromFile(char* file_path);
	void CreateQuadTree();
};

