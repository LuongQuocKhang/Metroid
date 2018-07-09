//#include "GameObjectManager.h"
//#include "Sprite.h"
//#include <fstream>
//#include <sstream>
//#include "trace.h"
//#include <vector>
//#include <map>
//using namespace std;
//
//GameObjectManager::GameObjectManager()
//{
//	
//}
//
//
//GameObjectManager::~GameObjectManager()
//{
//}
//
//void GameObjectManager::LoadGameObjectFromFile(char * file_path)
//{
//	//Doc tu file map
//	fstream f;
//	try
//	{
//		f.open(file_path);
//	}
//	catch (std::fstream::failure e)
//	{
//		trace(L"[GameObjectManager class]--Read info from file map failed");
//		return;
//	}
//	string line;
//	int row = 0;
//	int counter = 0;
//	while (!f.eof())
//	{
//		vector<string> file_info;
//		string split;
//		getline(f, line);
//		istringstream iss(line);
//
//		while (getline(iss, split, '\t'))
//		{
//			file_info.push_back(split);
//		}
//		//Doc width va height dung 1
//		if (row == 1)
//		{
//			width = stoi(file_info[0]);
//			height = stoi(file_info[1]);
//			continue;
//		}
//
//		//Doc GameObject tu dong 2
//		if (row >= 2)
//		{
//			for (int i = 0; i < file_info.size(); i++)
//			{
//				
//				GameObject* temp_gameobject = new GameObject();
//				temp_gameobject->SetPosX(i * width);
//				temp_gameobject->SetPosX((row - 2)*height);
//
//				int pos_of_sprite = stoi(file_info[i]);
//				SpriteInfo* info = new SpriteInfo[1];
//				info->pos_x = (pos_of_sprite % SPRITE_PER_ROW) * width;
//				info->pos_y = (pos_of_sprite / SPRITE_PER_ROW) * height;
//				
//				pair<int, GameObject*> temp_pair;
//				temp_pair.first = counter;
//				temp_pair.second = temp_gameobject;
//
//				first_room.insert(temp_pair);
//
//				counter++;
//			}
//			
//		}
//
//		
//		row++;
//	}
//	f.close();
//}
