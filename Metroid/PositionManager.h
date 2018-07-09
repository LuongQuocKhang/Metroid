#pragma once
#include <vector>
#include "Parameters.h"
/*
Class này quản lý một vector các vị trí xuất hiện của một enemy, dùng cho pooling
*/
using namespace std;
struct PostInfo
{
	float x;
	float y;
	float width;
	float height;
	bool isActive;
	int object_type;
	int detail_type;
};
class PositionManager
{
protected:
	World * manager;
	//std::vector<PosInfo*> list_pos;	// vector chứa các cặp vị trí (x,y)
	vector<vector<PostInfo>> list;
	int size;					// size của vector
	int index_room;
	int index;					// trỏ đến vị trí của một cặp (x,y) trong vector
public:
	PositionManager();
	// Truyền vào world, loại enemy và kích thước của loại enemy đó
	PositionManager(World * manager);
	~PositionManager();

	int GetIndexRoom();

	//-- TO DO: Load từ file vào vector
	void ImportPositionFromFile();

	// Trỏ đến vị trí kế tiếp trong vector
	void Next();

	// Trỏ đến vị trí phía sau trong vector
	void Back();


	//Hàm trả về vị trí, kích thước và loại GameObject xuất hiện trong Camera
	std::vector<PostInfo> GetListInCamera(int object_type);

	// Kiểm tra pos cùng với width height có nằm trong camera hay không
	//bool IsInCamera(PosInfo * target);
};

