#include "PositionManager.h"
#include "Camera.h"
#include <fstream>
#include <sstream>
#include <utility>
#include "PosInfo.h"
using namespace std;

PositionManager::PositionManager()
{
}

PositionManager::PositionManager(World * manager)
{
	this->manager = manager;

	size = 0;
	
	// khởi tạo index;
	index = 0;

	//khởi tạo index_room
	index_room = 0;	// phòng đầu tiên
}


PositionManager::~PositionManager()
{
}

int PositionManager::GetIndexRoom()
{
	return index_room;
}

void PositionManager::ImportPositionFromFile()
{
	int row_count = 0;
	ifstream f;
	try
	{
		f.open("map\\location_enemy_separate.txt");
	}
	catch (std::fstream::failure e)
	{
		return;
	}
	string line;
	vector<PostInfo> infos;	// vecotr dùng để chứa những PostInfo cùng 1 room
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
		{	list.push_back(infos);	// push vào room
			infos.clear();			// clear để add các PostInfo cho room tiếp theo
			row_count++;
			continue;
		}

		// Gặp END thì không đọc nữa
		if (pos[0] == "END")
			break;

		// Đọc info
		PostInfo info;
		info.x = stoi(pos[0]);
		info.y = stoi(pos[1]);
		info.width = stoi(pos[2]);
		info.height = stoi(pos[3]);
		info.object_type = stoi(pos[4]);
		info.detail_type = /*(ENEMY_TYPE)*/stoi(pos[5]);
		info.isActive = false;
		//vector<PostInfo> test;
		//test.push_back(info);
		//list.push_back(test);
		infos.push_back(info);
		this->size++;
		

		row_count++;
	}
	f.close();
}

void PositionManager::Next()
{
	// Kiểm tra xem các pos từ index+1 đến cuối vector xem còn điểm nào chưa xuất hiện trong viewport
	//for (int i = index + 1; i < size; i++)
	//{
	//	// Nếu điểm tiếp theo đã nằm trong camera (đã hiển thị rồi) thì bỏ qua
	//	if (Camera::IsInCamera(list[index], list_pos[i]->y, list_pos[i]->width, list_pos[i]->height));
	//		continue;
	//	// Nếu không thì gán index bằng i rồi nghỉ
	//	index = i;
	//	return;
	//}
	if (index_room + 1 >= list.size())
	{
		return;
	}
	index_room++;
}

void PositionManager::Back()
{
	// Kiểm tra xem các pos từ index-1 đến đầu vector xem còn điểm nào chưa xuất hiện trong viewport
	//for (int i = index - 1; i > 0; i--)
	//{
	//	// Nếu điểm tiếp theo đã nằm trong camera (đã hiển thị rồi) thì bỏ qua
	//	if (Camera::IsInCamera(list_pos[i]->x, list_pos[i]->y, list_pos[i]->width, list_pos[i]->height));
	//		continue;
	//	// Nếu không thì gán index bằng i rồi nghỉ
	//	index = i;
	//	return;
	//}
	if (index_room - 1 < 0)
		return;
	index_room--;
}

std::vector<PostInfo> PositionManager::GetListInCamera(int object_type)
{
	vector<PostInfo> result;
	for (int i = 0; i < list[index_room].size(); i++)
	{
		// Nếu nằm trong camera nhưng chưa active thì active
		if (Camera::IsInCamera(list[index_room][i].x, list[index_room][i].y, list[index_room][i].width, list[index_room][i].height) && list[index_room][i].object_type == object_type)
		{
			// Nếu chưa được active
			if (list[index_room][i].isActive == false)
			{
				list[index_room][i].isActive = true;
				//Thêm vào vector trả về
				result.push_back(list[index_room][i]);
			}
		}
		//Sẵn tiện cập nhật những vị trí nằm ngoài camera thành unactive
		else
		{
			list[index_room][i].isActive = false;
		}
	}
	return result;
}

//bool PositionManager::IsInCamera(PosInfo * target)
//{
//
//	// Kiềm tra bên trái
//	if (target->x + width < Camera::currentCamX)
//		return false;
//	// Kiểm tra phía trên
//	if (target->y + height > Camera::currentCamY)
//		return false;
//	// Kiểm tra bên phải
//	if (target->x > Camera::currentCamX + Camera::width)
//		return false;
//	// Kiểm tra phía dưới
//	if (target->y < Camera::currentCamY - Camera::height)
//		return false;
//
//	return true;
//}