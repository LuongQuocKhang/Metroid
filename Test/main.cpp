#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <list>
#include <map>
using namespace std;

typedef struct SPRITEINFO
{
	int pos_x;
	int pos_y;
}SpriteInfo;

void main()
{
	map<int, std::string> mapGameObjects;
	int row_count = 0;		// index của dòng đang đọc
	int width = 0;			// width của room
	int height = 0;			// height của room
	int counter = 0;		// biến counter để tính key cho map, biến này đếm liên tục từ phải sang trái trên xuống dưới

							//Read file info of file
	ifstream f;
	try
	{
		f.open("quadtree\\location_enemy_room.txt");
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

		if (pos[0] == "END")
			break;

		for (int i = 0; i < size; i++)
		{

			cout << pos[i] << "  ";

			// cập nhật counter
			counter++;
		}
		cout << "-----------------------------" << endl;
		row_count++;
	}
	f.close();
	//map<int, std::string>::iterator temp;
	//cout << "ROW COUNT: " << row_count << endl;
	//cout << "WIDTH " << width << endl;
	//cout << "HEIGHT: " << height << endl;
	//for (temp = mapGameObjects.begin(); temp != mapGameObjects.end(); temp++)
	//{
	//	cout << "(" << temp->first << " , " << temp->second << ")" << endl;
	//}

	//// Tìm 257
	//map<int, std::string>::iterator t = mapGameObjects.find(800);
	//if ( t == mapGameObjects.end())
	//	cout << "Khong ton tai" << endl;
	//else
	//	cout << "Ton tai" << endl;

	system("pause");

	/*map<int, char*> test;
	pair<int, char*> temp(0, "zero");
	test.insert(temp);
	

	cout << "At 2: " << test[0] << endl;
	system("pause");*/
}