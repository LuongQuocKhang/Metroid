#pragma once
/*
Class này dùng để load các thứ trong game
*/
#ifndef _LOADER_H_
#define _LOADER_H_
#include <map>
#include "GameObject.h"
#include "QNode.h"

#include "Parameters.h"

class Loader
{
protected:
	World * manager;
	int room_number;

	QNode* rootQNode;

	LPD3DXSPRITE spriteHandler;

	std::string matrix_path;	// Đường dẫn đến file matrix
	std::string quadtree_path; // Đường dẫn đến file quadtree
	std::string info_path;		// Đường dẫn đến file chứa thông tin room (camera, samus, ...)
public:
	Loader();
	Loader(LPD3DXSPRITE spriteHandler, int room_number, World* manager);
	~Loader();

	std::map<int, GameObject*> mapGameObjects;
	std::map<int, QNode*> mapQNodes;
	//============== LOAD FILE METHOD ====================
	void ReadMatrixFromFile(const char* path);
	void ReadFullMatrixFromFile(const char* path);
	void ReadQuadTreeFromFile(const char* path);
	void ReadInfoFromFile(const char* path);
	void ReadColliderFile(const char* path);
	void ReadOtherGO(const char* path);
	//============== END LOAD FILE METHOD ================

	//Link các node lại với nhau
	void LinkNodes();

	//Load dữ liệu
	void Load();

	//Test load map
	void TestRenderMapGO();
};


#endif // !_LOADER_H_


