#include "QNode.h"



QNode::QNode()
{
	nodeID = 0;
	x = 0;
	y = 0;
	width = 0;
	height = 0;

	//Gán bằng NULL cho chắc
	tl = NULL;
	tr = NULL;
	bl = NULL;
	br = NULL;

	//Khởi tạo GroupbObject rỗng 
	objects = new GroupObject(nullptr);
}

QNode::QNode(int id, int x, int y, int width, int height)
{
	this->nodeID = id;
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;

	//Gán bằng NULL cho chắc
	tl = NULL;
	tr = NULL;
	bl = NULL;
	br = NULL;

	//Khởi tạo GroupbObject rỗng 
	objects = new GroupObject(nullptr);
}


QNode::~QNode()
{
}

bool QNode::IsIntersectViewPort()
{

	// Kiểm tra phía trên viewport
	/*if (y > Camera::currentCamY)
		return false;*/
	if (y - height > Camera::currentCamY)
		return false;

	// Kiểm tra bên phải viewport
	if (x > Camera::currentCamX + Camera::width)
		return false;

	// Kiểm tra phía dưới viewport
	/*if (y + height < Camera::currentCamY - Camera::height)
		return false;*/
	if (y < Camera::currentCamY - Camera::height)
		return false;

	// Kiểm tra phía bên trái viewport
	if (x + width < Camera::currentCamX)
		return  false;

	return true;
}

int QNode::GetParentID()
{
	// Do tool MapEditor tính theo hệ 8
	return nodeID / NODE_FACTOR;
}

int QNode::GetOffsetID()
{
	return nodeID % NODE_FACTOR;
}

void QNode::SendObjectsToGroup(GroupObject * target)
{
	// Nếu node này không giao với viewport thì dừng
	if (!this->IsIntersectViewPort())
		return;

	// Nếu node này không phải là node lá thì xét tiếp
	if (this->tl != NULL)
	{
		this->tl->SendObjectsToGroup(target);
		this->tr->SendObjectsToGroup(target);
		this->bl->SendObjectsToGroup(target);
		this->br->SendObjectsToGroup(target);
	}
	else // Nếu là node lá thì target sẽ lấy object về
	{
		target->GetGroupObjectFrom(this->objects);
	}
}
