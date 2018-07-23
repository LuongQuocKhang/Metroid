#include "Loader.h"
#include <fstream>
#include <sstream>
#include "trace.h"
#include "Brick.h"
#include <utility>
#include <string.h>
#include "World.h"
#include "Camera.h"
#include "ColliderBrick.h"
#include "Brick.h"
#include "Gate.h"

Loader::Loader()
{
}

Loader::Loader(LPD3DXSPRITE spriteHandler, int room_number, World * manager)
{
	this->spriteHandler = spriteHandler;

	this->room_number = room_number;
	this->manager = manager;
	// Build đường dẫn đến matrix dựa vào room
	this->matrix_path_1 = "map\\matrix_room_1.txt";
	//this->matrix_path = "map\\matrix_room.txt";

	// Build đường dẫn đến quadtree dựa vào room
	this->quadtree_path_1 = "map\\quadtree_room_1.txt";
	//this->quadtree_path = "map\\quadtree_room.txt";

	// Build đường dẫn đến matrix dựa vào room
	this->matrix_path_2 = "map\\matrix_room_2.txt";

	// Build đường dẫn đến quadtree dựa vào room
	this->quadtree_path_2 = "map\\quadtree_room_2.txt";

	// Build đường dẩn đến file info dựa vào room
	//this->info_path = "map\\info_room_" + std::to_string(room_number) + ".txt";
	this->info_path = "map\\info_room.txt";

	// Đọc file matrix
	this->ReadMatrixFromFile(matrix_path_1.c_str(), 1);
	// Đọc file quadtree
	this->ReadQuadTreeFromFile(quadtree_path_1.c_str(), 1);
	this->LinkNodes_1();
	this->mapGameObjects.clear();
	this->mapQNodes.clear();

	// Đọc file matrix
	this->ReadMatrixFromFile(matrix_path_2.c_str(), 2);
	// Đọc file quadtree
	//this->ReadQuadTreeFromFile(quadtree_path_2.c_str(), 2);
	//this->LinkNodes_2();
	//this->mapGameObjects.clear();
	//this->mapQNodes.clear();

	//this->ReadColliderFile("map\\floor_pooling_full.txt");
	this->ReadFloorColliderFile("map\\floor_pooling_full.txt");
	this->ReadGroundColliderFile("map\\ground_collider.txt");

	this->ReadOtherGO("map\\otherobject.txt");

	manager->rootQNode1 = this->rootQNode_1;
	manager->rootQNode2 = this->rootQNode_2;

	// rootGONode tại manager sẽ do ở đây quản lý
	/*switch (room_number)
	{
	case 1:
		manager->rootQNode1 = this->rootQNode;
		break;
	case 2:
		manager->rootQNode2 = this->rootQNode;
	}*/
	
}


Loader::~Loader()
{
}

// Tạo các GameObject dựa theo id
void Loader::ReadMatrixFromFile(const char* path, int room)
{
	int row_count = 0;		// index của dòng đang đọc
	int width = 0;			// width của room
	int height = 0;			// height của room
	int counter = 0;		// biến counter để tính key cho map, biến này đếm liên tục từ phải sang trái trên xuống dưới

	//Read file info of file
	ifstream f;
	try
	{
		f.open(path);
		
	}
	catch (std::fstream::failure e)
	{
		trace(L"[Loader class]: Failed to load matrix path");
		return;
	}
	string line;
	while (!f.eof())
	{
		vector<string> pos;		// vector dùng để chứa dữ liệu từng dòng
		int size = 0;				// size của vector
		string split;			// chuỗi sau khi đã tách ra
		getline(f, line);

		istringstream iss(line);

		// Nếu là dòng đầu tiên bỏ qua, vì dòng đầu bị lỗi
		if (row_count == 0)
		{
			row_count++;
			continue;
		}

		// tách từng dòng ra thành các chuỗi dựa vào \t
		while (getline(iss, split, '\t'))
		{
			// gán từng chuỗi trong dòng vào vector
			pos.push_back(split);
			size++;
		}

		// 
		

		// Dòng này chứa width và height của room này
		if (row_count == 1)
		{	
			height = stoi(pos[0]);
			width = stoi(pos[1]);
			row_count++;
			continue;
		}

		// Đây là dòng thứ 3 chứa width và height của tile (mặc định là 32 nên khỏi xét)
		if (row_count == 2)
		{
			row_count++;
			continue;
		}

		// Nếu dòng không có gì thì bỏ qua
		if (size == 0)
		{
			row_count++;
			continue;
		}

		if (pos[0] == "END")
			break;

		// Những dòng còn lại là map
		for (int i = 0; i < size; i++)
		{
			int id = stoi(pos[i]);
			// Xét xem id là loại gì
			// Nếu id là 9 thì bỏ qua (ô trống trong room 1)
			if (room == 1 && id == 9)
			{
				counter++;
				continue;
			}
			// Nếu id là 0 thì bỏ qua (ô trống trong room 2)
			if (room == 2 && id == 0)
			{
				counter++;
				continue;
			}

			

			
			// Tính pos_x và pos_y cho Brick
			if (room == 1)
			{

				int pos_x = i * 32;
				int pos_y = (97) * 32 - (((row_count - 3) + 97 - 15) * 32);	// trừ đi 3 dòng đầu không tính	-- 97 là số height của map 2
				if (id == 99)	// LEFT GATE
				{
					Gate * gate = new Gate(spriteHandler, manager, GATE_TYPE::LEFT);
					gate->SetPosX(pos_x);
					gate->SetPosY(pos_y);

					pair<int, GameObject*> pair_to_add(counter, gate);
					mapGameObjects.insert(pair_to_add);
				}
				else if (id == 98)  // RIGHT GATE
				{
					Gate * gate = new Gate(spriteHandler, manager, GATE_TYPE::RIGHT);
					gate->SetPosX(pos_x);
					gate->SetPosY(pos_y);

					pair<int, GameObject*> pair_to_add(counter, gate);
					mapGameObjects.insert(pair_to_add);
				}
				else   // BRICK
				{
					Brick * brick = new Brick(spriteHandler, manager, GROUND, id, pos_x, pos_y);
					// Nếu gạch ngay cổng thì cho phép băng qua
					if (id == 12)
						brick->SetPassable(true);

					pair<int, GameObject*> pair_to_add(counter, brick);
					mapGameObjects.insert(pair_to_add);
				}
			}
			else if (room == 2)
			{
				int pos_x = (i + 160 - 33) * 32;
				int pos_y = 97 * 32 - ((row_count - 3) * 32) -(15 * 32);

				Brick * brick = new Brick(spriteHandler, manager, FLOOR, id, pos_x, pos_y);
				// Nếu gạch ngay cổng thì cho phép băng qua
				if (id == 19)
					brick->SetPassable(true);

				pair<int, GameObject*> pair_to_add(counter, brick);
				mapGameObjects.insert(pair_to_add);
			}
			// chỗ y trên này tính theo world???

			// cập nhật counter
			counter++;
		}
		row_count++;
	}
	f.close();
}

void Loader::ReadFullMatrixFromFile(const char * path)	// chưa xài!!!
{
	int row_count = 0;		// index của dòng đang đọc
	int width = 0;			// width của room
	int height = 0;			// height của room
	int counter = 0;		// biến counter để tính key cho map, biến này đếm liên tục từ phải sang trái trên xuống dưới

							//Read file info of file
	ifstream f;
	try
	{
		f.open(path);

	}
	catch (std::fstream::failure e)
	{
		trace(L"[Loader class]: Failed to load matrix path");
		return;
	}
	string line;
	while (!f.eof())
	{
		vector<string> pos;		// vector dùng để chứa dữ liệu từng dòng
		int size = 0;				// size của vector
		string split;			// chuỗi sau khi đã tách ra
		getline(f, line);

		istringstream iss(line);

		// Nếu là dòng đầu tiên bỏ qua, vì dòng đầu bị lỗi
		if (row_count == 0)
		{
			row_count++;
			continue;
		}

		// tách từng dòng ra thành các chuỗi dựa vào \t
		while (getline(iss, split, '\t'))
		{
			// gán từng chuỗi trong dòng vào vector
			pos.push_back(split);
			size++;
		}

		// 


		// Dòng này chứa width và height của room này
		if (row_count == 1)
		{
			height = stoi(pos[0]);
			width = stoi(pos[1]);
			row_count++;
			continue;
		}

		// Đây là dòng thứ 3 chứa width và height của tile (mặc định là 32 nên khỏi xét)
		if (row_count == 2)
		{
			row_count++;
			continue;
		}

		// Nếu dòng không có gì thì bỏ qua
		if (size == 0)
		{
			row_count++;
			continue;
		}

		// Những dòng còn lại là map
		for (int i = 0; i < size; i++)
		{
			int id = stoi(pos[i]);
			// Xét xem id là loại gì
			// Nếu id là 0 thì bỏ qua (ô trống)
			if (id == 0)
			{
				counter++;
				continue;
			}

			Brick* brick;
			// Tính pos_x và pos_y cho Brick
			int pos_x = i * 32;
			int pos_y = height * 32 - ((row_count - 3) * 32);	// trừ đi 3 dòng đầu không tính	-- 139 là số height của map 2
			brick = new Brick(spriteHandler, manager, ALL, id, pos_x, pos_y);
			// Nếu gạch ngay cổng thì cho phép băng qua
			if (id == 18)
				brick->SetPassable(true);
			
			// chỗ y trên này tính theo world???

			pair<int, GameObject*> pair_to_add(counter, brick);
			mapGameObjects.insert(pair_to_add);

			// cập nhật counter
			counter++;
		}
		row_count++;
	}
	f.close();
}

//Gọi hàm này sau khi gọi hàm ReadMatrixFromFile !!!
void Loader::ReadQuadTreeFromFile(const char* path, int room)
{
	int row_count = 0;
	//Read file info of file
	ifstream f;
	try
	{
		f.open(path);
	}
	catch (std::fstream::failure e)
	{
		trace(L"[Loader class]: Failed to load matrix path");
		return;
	}
	string line;
	while (!f.eof())
	{
		vector<string> pos;		// vector dùng để chứa dữ liệu từng dòng
		int size = 0;				// size của vector
		string split;			// chuỗi sau khi đã tách ra
		getline(f, line);

		istringstream iss(line);

		// Nếu là dòng đầu tiên cũng bỏ qua, vì dòng đầu bị lỗi
		if (row_count == 0)
		{
			row_count++;
			continue;
		}

		// tách từng dòng ra thành các chuỗi dựa vào \t
		while (getline(iss, split, '\t'))
		{
			// gán từng chuỗi trong dòng vào vector
			pos.push_back(split);
			size++;
		}

		// Nếu dòng không có gì thì bỏ qua
		if (size == 0)
		{
			row_count++;
			continue;
		}

		// Đọc dữ liệu mỗi dòng
		// index 0 là nodeID
		const int nodeID = stoi(pos[0]);


		// index 1 và 2 là x và y
		int node_x = stoi(pos[1]);
		int node_y = stoi(pos[2]);

		// index 3 và 4 là width và height
		int node_w = stoi(pos[3]);
		int node_h = stoi(pos[4]);

		// Khởi tạo QNode và gán vào
		QNode* node = new QNode(nodeID, node_x, node_y, node_w, node_h);

		// Nếu không có list GameObject phía sau thì dùng
		if (size <= 5)
		{
			pair<int, QNode*> pair_to_add(nodeID, node);
			mapQNodes.insert(pair_to_add);
			row_count++;
			continue;
		}

		// Những thằng còn lại là index của GameObject trong file matrix
		// Add vào node
		for (int i = 5; i < size; i++)
		{
			int index = stoi(pos[i]);

			// Phải xem trước xem index đó có trong map hay không?
			// (Vì trong map matrix có id = 9 không xét do là nền)
			map<int, GameObject*>::const_iterator temp = mapGameObjects.find(index);
			// Nếu không tồn tại thì bỏ qua
			if (temp == mapGameObjects.end())
				continue;

			switch (mapGameObjects[index]->GetType())
			{
			case BRICK:
			{
				// ép kiểu về Brick
				Brick* brick = (Brick*)mapGameObjects[index];
				node->objects->AddGameObject(brick);
				break;
			}
			case GATE:
			{
				Gate * gate = (Gate*)mapGameObjects[index];
				node->objects->AddGameObject(gate);
				break;
			}
			}
		}
		
		// Insert vào map
		pair<int, QNode*> pair_to_add(nodeID, node);
		mapQNodes.insert(pair_to_add);

		row_count++;
	}
	f.close();
}

void Loader::ReadInfoFromFile(const char * path)
{
	int row_count = 0;
	ifstream f;
	try
	{
		f.open(path);
	}
	catch (std::fstream::failure e)
	{
		return;
	}
	string line;
	while (!f.eof())
	{
		vector<string> pos;		// vector dùng để chứa dữ liệu từng dòng
		int size = 0;				// size của vector
		string split;			// chuỗi sau khi đã tách ra
		getline(f, line);

		istringstream iss(line);

		// Nếu là dòng đầu tiên cũng bỏ qua, vì dòng đầu bị lỗi
		/*if (row_count == 0)
		{
			row_count++;
			continue;
		}*/


		// tách từng dòng ra thành các chuỗi dựa vào \t
		while (getline(iss, split, '\t'))
		{
			// gán từng chuỗi trong dòng vào vector
			pos.push_back(split);
			size++;
		}

		// Nếu dòng không có gì thì bỏ qua
		if (size == 0)
		{
			row_count++;
			continue;
		}

		// Gặp END thì không đọc nữa
		if (pos[0] == "END")
			break;

		//Thông tin camera
		if (row_count >= 0 && row_count <= 3)
		{
			CamInfo info;
			info.min_x = stoi(pos[0]);
			info.max_x = stoi(pos[1]);
			info.min_y = stoi(pos[2]);
			info.max_y = stoi(pos[3]);
			Camera::list.push_back(info);
		}
		else if (row_count == 4) // thông tin samus
		{
			manager->samus->SetPosX(stoi(pos[0]));
			manager->samus->SetPosY(stoi(pos[1]));
		}
		//switch (row_count)
		//{
		//case 0:	//Camera
		//	Camera::min_x = stoi(pos[0]);
		//	Camera::max_x = stoi(pos[1]);
		//	break;
		//case 1:	//Vị trí samus
		//	manager->samus->SetPosX(stoi(pos[0]));
		//	manager->samus->SetPosY(stoi(pos[1]));
		//	break;
		//}

		row_count++;
	}
	f.close();
}

void Loader::ReadFloorColliderFile(const char * path)
{

	int row_count = 0;
	ifstream f;
	try
	{
		f.open(path);
	}
	catch (std::fstream::failure e)
	{
		return;
	}
	string line;
	while (!f.eof())
	{
		vector<string> pos;		// vector dùng để chứa dữ liệu từng dòng
		int size = 0;				// size của vector
		string split;			// chuỗi sau khi đã tách ra
		getline(f, line);

		istringstream iss(line);

		// Nếu là dòng đầu tiên cũng bỏ qua, vì dòng đầu bị lỗi
		/*if (row_count == 0)
		{
		row_count++;
		continue;
		}*/


		// tách từng dòng ra thành các chuỗi dựa vào \t
		while (getline(iss, split, '\t'))
		{
			// gán từng chuỗi trong dòng vào vector
			pos.push_back(split);
			size++;
		}

		// Nếu dòng không có gì thì push vào vector và tiếp tục
		if (size == 0)
		{
			row_count++;
			continue;
		}

		// Gặp END thì không đọc nữa
		if (pos[0] == "END")
			break;

		// Đọc info
		//for (int i = 0; i < size; i++)
		//{
			//int pos_x = (i + 160 - 33) * 32;
			//int pos_y = 97 * 32 - ((row_count - 3) * 32) - (15 * 32);

			float x = stoi(pos[0]) + (160 - 33) * 32;
			float y = (97 * 32) - stoi(pos[1]) -(15 * 32);
			float w = stoi(pos[2]);
			float h = stoi(pos[3]);
			ColliderBrick *cbrick = new ColliderBrick(spriteHandler, this->manager, x, y, w, h);
			
			//Cổng
			if (row_count >= 60 && row_count <= 62)
			{
				cbrick->isPassable = true;
			}
			manager->colFloorBrick->AddGameObject(cbrick);
			
		//}
		row_count++;
	}
	f.close();

}

void Loader::ReadGroundColliderFile(const char * path)
{
	int row_count = 0;
	ifstream f;
	try
	{
		f.open(path);
	}
	catch (std::fstream::failure e)
	{
		return;
	}
	string line;
	while (!f.eof())
	{
		vector<string> pos;		// vector dùng để chứa dữ liệu từng dòng
		int size = 0;				// size của vector
		string split;			// chuỗi sau khi đã tách ra
		getline(f, line);

		istringstream iss(line);

		// Nếu là dòng đầu tiên cũng bỏ qua, vì dòng đầu bị lỗi
		/*if (row_count == 0)
		{
		row_count++;
		continue;
		}*/


		// tách từng dòng ra thành các chuỗi dựa vào \t
		while (getline(iss, split, '\t'))
		{
			// gán từng chuỗi trong dòng vào vector
			pos.push_back(split);
			size++;
		}

		// Nếu dòng không có gì thì push vào vector và tiếp tục
		if (size == 0)
		{
			row_count++;
			continue;
		}

		// Gặp END thì không đọc nữa
		if (pos[0] == "END")
			break;

		// Đọc info
		//for (int i = 0; i < size; i++)
		//{
		//int pos_x = (i + 160 - 33) * 32;
		//int pos_y = 97 * 32 - ((row_count - 3) * 32) - (15 * 32);

		float x = stoi(pos[0]);
		float y = (15 * 32) - stoi(pos[1]);
		float w = stoi(pos[2]);
		float h = stoi(pos[3]);
		ColliderBrick *cbrick = new ColliderBrick(spriteHandler, this->manager, x, y, w, h);

		//Cổng
		if (row_count >= 0 && row_count <= 2)
		{
			cbrick->isPassable = true;
		}
		manager->colGroundBrick->AddGameObject(cbrick);

		//}
		row_count++;
	}
	f.close();
}

void Loader::ReadOtherGO(const char * path)
{
	int row_count = 0;
	ifstream f;
	try
	{
		f.open(path);
	}
	catch (std::fstream::failure e)
	{
		return;
	}
	string line;
	while (!f.eof())
	{
		vector<string> pos;		// vector dùng để chứa dữ liệu từng dòng
		int size = 0;				// size của vector
		string split;			// chuỗi sau khi đã tách ra
		getline(f, line);

		istringstream iss(line);

		// tách từng dòng ra thành các chuỗi dựa vào \t
		while (getline(iss, split, '\t'))
		{
			// gán từng chuỗi trong dòng vào vector
			pos.push_back(split);
			size++;
		}

		// Nếu dòng không có gì thì push vào vector và tiếp tục
		if (size == 0)
		{
			row_count++;
			continue;
		}

		// Gặp END thì không đọc nữa
		if (pos[0] == "END")
			break;

		// Đọc info
		//for (int i = 0; i < size; i++)
		//{
		//int pos_x = (i + 160 - 33) * 32;
		//int pos_y = 97 * 32 - ((row_count - 3) * 32) - (15 * 32);

		/*float x = stoi(pos[0]) + (160 - 33) * 32;
		float y = (97 * 32) - stoi(pos[1]) - (15 * 32);
		float w = stoi(pos[2]);
		float h = stoi(pos[3]);
		int type = stoi(pos[4]);*/

		float x = stoi(pos[0]);
		float y = stoi(pos[1]);
		float w = stoi(pos[2]);
		float h = stoi(pos[3]);
		int object_type = stoi(pos[4]);
		int detail_type = stoi(pos[5]);

		if (object_type == 9)	//SENTRY
		{
			Sentry *sentry = new Sentry(spriteHandler, manager, (SENTRY_TYPE)detail_type);
			sentry->Init(x, y);
			manager->otherGO->AddGameObject(sentry);
		}
		else if (object_type == 8)	//GATE
		{
			Gate * gate = new Gate(spriteHandler, manager, (GATE_TYPE)detail_type);
			gate->SetPosX(x);
			gate->SetPosY(y);
			manager->otherGO->AddGameObject(gate);
		}

		//}
		row_count++;
	}
	f.close();
}

void Loader::LinkNodes_1()
{
	map<int, QNode*>::iterator it;
	for (it = mapQNodes.begin(); it != mapQNodes.end(); it++)
	{
		// Trong map được sắp xếp tăng dần theo nodeID nên khỏi cần lo

		// Nếu là node Gốc thì gán vào rootQNode
		if (it->first == 1)
		{
			rootQNode_1 = it->second;
			continue;
		}

		// Tính id của node cha và offset của node hiện tại
		const int parent_id = it->second->GetParentID();
		const int offset = it->second->GetOffsetID();

		// Xét offset rồi lấy node cha trỏ vào
		switch (offset)
		{
		case 1:
			mapQNodes[parent_id]->tl = it->second;
			break;
		case 2:
			mapQNodes[parent_id]->tr = it->second;
			break;
		case 3:
			mapQNodes[parent_id]->bl = it->second;
			break;
		case 4:
			mapQNodes[parent_id]->br = it->second;
			break;
		}
	}
}

void Loader::LinkNodes_2()
{
	map<int, QNode*>::iterator it;
	for (it = mapQNodes.begin(); it != mapQNodes.end(); it++)
	{
		// Trong map được sắp xếp tăng dần theo nodeID nên khỏi cần lo

		// Nếu là node Gốc thì gán vào rootQNode
		if (it->first == 1)
		{
			rootQNode_2 = it->second;
			continue;
		}

		// Tính id của node cha và offset của node hiện tại
		const int parent_id = it->second->GetParentID();
		const int offset = it->second->GetOffsetID();

		// Xét offset rồi lấy node cha trỏ vào
		switch (offset)
		{
		case 1:
			mapQNodes[parent_id]->tl = it->second;
			break;
		case 2:
			mapQNodes[parent_id]->tr = it->second;
			break;
		case 3:
			mapQNodes[parent_id]->bl = it->second;
			break;
		case 4:
			mapQNodes[parent_id]->br = it->second;
			break;
		}
	}
}

void Loader::Load()
{
	this->ReadInfoFromFile(info_path.c_str());
}

void Loader::TestRenderMapGO()
{
	map<int, GameObject*>::iterator i;
	for (i = mapGameObjects.begin(); i != mapGameObjects.end(); i++)
	{
		i->second->Render();
	}
}


