#include "QuadTree.h"
#include <fstream>
#include <sstream>
#include "trace.h"
#include <vector>

QuadTree::QuadTree()
{
}


QuadTree::~QuadTree()
{
}

void QuadTree::LoadNodeFromFile(char * file_path)
{
	//Doc tu file map
	fstream f;
	try
	{
		f.open(file_path);
	}
	catch (std::fstream::failure e)
	{
		trace(L"[Quadtree class]--Read node info from file map failed");
		return;
	}
	string line;
	int id = 0;
	while (!f.eof())
	{
		vector<string> file_info;
		string split;
		getline(f, line);
		istringstream iss(line);

		while (getline(iss, split, '\t'))
		{
			file_info.push_back(split);
		}
		if (file_info.size() <= 1)
			continue;

		int node_id = stoi(file_info[0]);
		
		if (file_info.size() > 5)
			for (int i = 5; i < file_info.size(); i++)
			{
				QNode* node = new QNode();
				node->nodeID = stoi(file_info[0]);
			}

	}
	f.close();
}
