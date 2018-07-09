#pragma once
#include "QTreeObject.h"
#include <list>
#include "GroupObject.h"
#include "Camera.h"
using namespace std;
class QNode
{
public:
	QNode *tl, *tr, *bl, *br;
	int nodeID;
	GroupObject* objects;

	int x;
	int y;
	int width;
	int height;

	QNode();
	QNode(int id, int x, int y, int width, int height);
	~QNode();

	// Kiểm tra xem node hiện tại có giao với viewport không
	bool IsIntersectViewPort();

	// Tìm ID của node cha
	int GetParentID();

	// Tìm offset (số thứ tự trong node con) của node hiện tại. Vd: nodeID = 11 -> offset = 11 % 8 = 3
	int GetOffsetID();

	// Gửi những GameObject trong node này đến một GroupObject nếu nằm trong viewport
	void SendObjectsToGroup(GroupObject * target);
};

