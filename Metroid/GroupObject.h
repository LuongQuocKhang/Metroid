#pragma once
#ifndef _GROUPOBJECT_H_
#define _GROUPOBJECT_H_

#include <vector>
#include "Parameters.h"
#include "Enemy.h"

/*
	Class này có tác dụng gom nhóm các GameObject cùng loại lại để quản lý cho dễ
	Vd: Các loại enemy khác nhau gom chung vào để dễ quản lý
*/
class GroupObject
{
protected:
	World* manager;
public:
	std::vector<GameObject*> objects;	// vector quản lý list các GameObject cùng loại
	int size;							// số lượng GameObject trong vector (tránh moi từ vector vì không tối ưu thời gian)

	GroupObject();
	GroupObject(World* manager);
	~GroupObject();

	//==================== GET - SET METHOD ====================
	// Trả về mảng vector chứa GameObject
	std::vector<GameObject*> GetListGO();

	// Trả về số lượng GameObject trong vector
	int GetSize();
	//==================== END GET - SET METHOD ================


	void AddGameObject(GameObject* target);

	// Hàm update các GameObject có trong vector (dùng cho SpecialCollision và QuadtreeCollision)
	void Update(float t);

	// Hàm update các GameObject có trong vector (dùng cho Projectile, Enemy, ...)
	void UpdateActive(float t);

	// Hàm render các GameObject có trong vector (dùng cho SpecialCollision và QuadtreeCollision)
	void Render();

	
	// Lấy GroupGameObject khác bỏ vào vector này
	void GetGroupObjectFrom(GroupObject* group);

	//Lấy ra những GameObject trong quadtree nằm trong viewport
	void GetCollisionObjectQTree(int root_num);	//--TO-DO: Hoàn thành hàm này sau khi code QNode
	
	//Lấy ra những GameObject cần xử lý va chạm (không nằm trong quadtree)
	void GetCollisionObjects();

	//Set active enemy
	void SetEnemyActive(int object_type, int detail_type, float posX, float posY);	// chưa xài !!!

	//void SetObjectActive()


	void SetOtherGOActive();

	//===================== STATIC METHOD =================================================
	//Hàm static trả về một Enemy đang unactive
	static Enemy* GetUnActiveEnemy(GroupObject * enemygroup, ENEMY_TYPE enemy_type);

	//Hàm static trả về một Item đang unactive
	static Item* GetUnActiveItem(GroupObject * itemgroup, ITEM_TYPE item_type);

	static void SetGameObjectActive(GroupObject * groupObject, int object_type, int detail_type, float posX, float posY);
	//===================== END STATIC METHOD ==============================================

	static void LoadOtherGO(char * path);
};
#endif // !_GROUPOBJECT_H_

