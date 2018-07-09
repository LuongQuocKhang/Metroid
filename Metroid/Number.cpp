#include "Number.h"
#include "World.h"
#include "GroupObject.h"
#include "Samus.h"
#include "Camera.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "Sprite.h"
using namespace std;

int tce, tde, tcm, tdm;
Number::Number()
{
}

Number::Number(LPD3DXSPRITE spriteHandler, World * manager, NUMBER_PATH_TYPE number_path, NUMBER_TYPE number_type)
{
	this->spriteHandler = spriteHandler;
	this->manager = manager;
	this->numberpath = number_path; //Lấy type path của Number (Chục hoặc đơn vị)
	this->numbertype = number_type; //Lấy type của Number(energy hay missile)
	switch (numbertype)
	{
	case NUMBEROFENERGY:
	{
		this->SetHealth(manager->samus->GetHealth());
	}
	break;
	case NUMBEROFMISSILE:
	{
		this->SetHealth(manager->missiles->getNum());
	}
	break;
	}
	this->isActive = true;
	this->InitSprites();


	collider = new Collider();
}

Number::~Number()
{
	delete(number1);
	delete(number2);
}

void Number::InitSprites()
{
	switch (numbertype)
	{
	case NUMBEROFENERGY:
	{
		if (this->GetHealth() < 0) //Nếu Health <0 thì giá trị Health là 00 (0<=Health<=99)
		{
			switch (numberpath)
			{
			case CHUC:
				Check_C(0);//Số chục là 0
				break;
			case DONVI:
				Check_DV(0);//Số dơn vị là 0
				break;
			}

		}
		if (this->GetHealth() > 0 && this->GetHealth() < 10) //Nếu giá trị Health trong khoảng từ 1-9
		{
			switch (numberpath)
			{
			case CHUC:
				Check_C(0); //Số chục là 0
				break;
			case DONVI:
				Check_DV(this->GetHealth()); //Số đơn vị
				break;
			}


		}
		if (this->GetHealth() >= 10 && this->GetHealth() <= 99) //Nếu health trong khoảng 10-99
		{
			switch (numberpath)
			{
			case CHUC:
			{
				int chuc = this->GetHealth() / 10; //Lấy phần nguyên là số chục 
				Check_C(chuc);
			}
			break;
			case DONVI:
			{
				int dv = this->GetHealth() % 10;//Lấy phần dư là số đơn vị
				Check_DV(dv);
			}
			break;
			}

		}
		if (this->GetHealth() >99) //Nếu Health > 99 thì giá trị Health sẽ là 99  (0<=Health<=99)
		{
			switch (numberpath)
			{
			case CHUC:
				Check_C(9);//Số chục là 9
				break;
			case DONVI:
				Check_DV(9);//Số đơn vị là 9
				break;
			}

		}
	}
	break;
	case NUMBEROFMISSILE:
	{
		if (this->GetHealth() < 0) //Nếu Health <0 thì giá trị Health là 00 (0<=Health<=99)
		{
			switch (numberpath)
			{
			case CHUC:
				Check_C(0);//Số chục là 0
				break;
			case DONVI:
				Check_DV(0);//Số dơn vị là 0
				break;
			}

		}
		if (this->GetHealth() > 0 && this->GetHealth() < 10) //Nếu giá trị Health trong khoảng từ 1-9
		{
			switch (numberpath)
			{
			case CHUC:
				Check_C(0); //Số chục là 0
				break;
			case DONVI:
				Check_DV(this->GetHealth()); //Số đơn vị
				break;
			}


		}
		if (this->GetHealth() >= 10 && this->GetHealth() <= 99) //Nếu health trong khoảng 10-99
		{
			switch (numberpath)
			{
			case CHUC:
			{
				int chuc = this->GetHealth() / 10; //Lấy phần nguyên là số chục 
				Check_C(chuc);
			}
			break;
			case DONVI:
			{
				int dv = this->GetHealth() % 10;//Lấy phần dư là số đơn vị
				Check_DV(dv);
			}
			break;
			}

		}
		if (this->GetHealth() >99) //Nếu Health > 99 thì giá trị Health sẽ là 99  (0<=Health<=99)
		{
			switch (numberpath)
			{
			case CHUC:
				Check_C(9);//Số chục là 9
				break;
			case DONVI:
				Check_DV(9);//Số đơn vị là 9
				break;
			}

		}
	}
	break;
	}
}

void Number::Update(int t)
{
	switch (numbertype)
	{
	case NUMBEROFENERGY:
	{
		if (manager->samus->GetHealth() != this->GetHealth()) //Nếu Health của samus khác shealth hiện tại thì sẽ update số health
		{
			this->SetHealth(manager->samus->GetHealth());
			this->InitSprites();
		}

		switch (numberpath)
		{
		case CHUC: //Trường hợp số chục
		{
			this->pos_x = Camera::currentCamX + 90;
			this->pos_y = Camera::currentCamY - 60;
		}
		break;
		case DONVI: //Trường hợp số đơn vị 
		{
			this->pos_x = Camera::currentCamX + 110;
			this->pos_y = Camera::currentCamY - 60;
		}
		break;
		}


	}
	break;
	case NUMBEROFMISSILE:
	{

		switch (numberpath)
		{
		case CHUC: //Trường hợp số chục
		{
			this->pos_x = Camera::currentCamX + 90;
			this->pos_y = Camera::currentCamY - 90;
		}
		break;
		case DONVI: //Trường hợp số đơn vị 
		{
			this->pos_x = Camera::currentCamX + 110;
			this->pos_y = Camera::currentCamY - 90;
		}
		break;
		}

	}
	break;
	}
}
void Number::Check_C(int n)
{
	fstream f;
	try
	{
		f.open(NUMBER_PATH);
	}
	catch (std::fstream::failure e)
	{
		trace(L"[Sprite class]--Read sprite info from file failed");
		return;
	}
	string line;
	int id = 0;
	while (!f.eof())
	{
		vector<string> pos;
		string split;
		getline(f, line);
		istringstream iss(line);
		if (n == id) //Kiểm tra số cần tìm có tương ứng với index cần tìm (n=1 thì id=1)
		{
			while (getline(iss, split, ' '))
			{
				pos.push_back(split);
			}

			int x = stoi(pos[0]);
			int y = stoi(pos[1]);
			switch (numbertype)
			{
			case NUMBEROFENERGY:
			{
				number1 = new Sprite(spriteHandler, NUMBER_SPRITE_PATH, x, y, NUMBER_WIDTH, NUMBER_HEIGHT);//Dùng tọa độ x,y để khởi tạo cho number1

			}
			break;
			case NUMBEROFMISSILE:
			{
				number1 = new Sprite(spriteHandler, NUMBER_SPRITE_PATH, x, y, NUMBER_WIDTH, NUMBER_HEIGHT);//Dùng tọa độ x,y để khởi tạo cho number1
			}
			break;
			}
			break;
		}
		id++;
	}
	f.close();
}
void Number::Check_DV(int n)
{
	fstream f;
	try
	{
		f.open(NUMBER_PATH);
	}
	catch (std::fstream::failure e)
	{
		trace(L"[Sprite class]--Read sprite info from file failed");
		return;
	}
	string line;
	int id = 0;
	while (!f.eof())
	{


		vector<string> pos;
		string split;
		getline(f, line);
		istringstream iss(line);
		if (n == id)
		{
			while (getline(iss, split, ' '))
			{
				pos.push_back(split);
			}

			int x = stoi(pos[0]);
			int y = stoi(pos[1]);
			switch (numbertype)
			{
			case NUMBEROFENERGY:
			{
				number2 = new Sprite(spriteHandler, NUMBER_SPRITE_PATH, x, y, NUMBER_WIDTH, NUMBER_HEIGHT);//Dùng tọa độ x,y để khởi tạo cho number1

			}
			break;
			case NUMBEROFMISSILE:
			{
				number2 = new Sprite(spriteHandler, NUMBER_SPRITE_PATH, x, y, NUMBER_WIDTH, NUMBER_HEIGHT);//Dùng tọa độ x,y để khởi tạo cho number1
			}
			break;
			}
			break;
		}
		id++;
	}
	f.close();
}
void Number::SetHealth(int value)
{
	health = value;
}

int Number::GetHealth()
{
	return health;
}

void Number::Render()
{
	// Nếu không active thì không render
	if (!isActive)
		return;

	spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
	switch (numbertype)
	{
	case NUMBEROFENERGY:
	{
		switch (numberpath)
		{
		case CHUC:
			number1->Render(pos_x, pos_y);
			break;
		case DONVI:
			number2->Render(pos_x, pos_y);
			break;
		}
	}
	break;
	case NUMBEROFMISSILE:
	{
		switch (numberpath)
		{
		case CHUC:
			number1->Render(pos_x, pos_y);
			break;
		case DONVI:
			number2->Render(pos_x, pos_y);
			break;
		}
	}
	break;
	}

	spriteHandler->End();
}