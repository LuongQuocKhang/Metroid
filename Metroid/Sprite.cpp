#include "Sprite.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "trace.h"
#include "Camera.h"
using namespace std;

Sprite::Sprite()
{
}

Sprite::Sprite(LPD3DXSPRITE SpriteHandler, LPWSTR ImagePath, char* infoFilePath, int Width, int Height, int Count, int SpritePerRow)
{
	//
	//Init array posSprite
	//
	spriteInfo = new SpriteInfo[Count];

	//Read file info of file
	fstream f;
	try
	{
		f.open(infoFilePath);
	}
	catch (std::fstream::failure e)
	{
		trace(L"[Sprite class]--Read sprite info from file failed");
		return;
	}
	string line;
	int id = 0;
	while (!f.eof() && id < Count)
	{
		vector<string> pos;
		string split;
		getline(f, line);
		istringstream iss(line);
		
		while (getline(iss, split, ' '))
		{
			pos.push_back(split);
		}
		
		spriteInfo[id].pos_x = stoi(pos[0]);
		spriteInfo[id].pos_y = stoi(pos[1]);
		id++;
	}
	f.close();

	//
	//Init sprite with DirectX
	//
	D3DXIMAGE_INFO info;
	HRESULT result;

	_Image = NULL;
	_SpriteHandler = SpriteHandler;
	_Width = Width;
	_Height = Height;
	_Count = Count;
	_SpritePerRow = SpritePerRow;
	_Index = 0;

	result = D3DXGetImageInfoFromFile(ImagePath, &info);
	if (result != D3D_OK)
	{
		trace(L"[ERROR] Failed to get information from image file '%s'", ImagePath);
		return;
	}

	LPDIRECT3DDEVICE9 d3ddv;
	SpriteHandler->GetDevice(&d3ddv);

	result = D3DXCreateTextureFromFileEx(
		d3ddv,
		ImagePath,
		info.Width,
		info.Height,
		1,
		D3DUSAGE_DYNAMIC,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		D3DCOLOR_XRGB(0, 0, 0),
		&info,
		NULL,
		&_Image);

	if (result != D3D_OK)
	{
		trace(L"[ERROR] Failed to create texture from file '%s'", ImagePath);
		return;
	}

}

Sprite::Sprite(LPD3DXSPRITE SpriteHandler, LPWSTR ImagePath, int posX, int posY, int Width, int Height)
{
	spriteInfo = new SpriteInfo[1];
	spriteInfo->pos_x = posX;
	spriteInfo->pos_y = posY;
	//
	//Init sprite with DirectX
	//
	D3DXIMAGE_INFO info;
	HRESULT result;

	_Image = NULL;
	_SpriteHandler = SpriteHandler;
	_Width = Width;
	_Height = Height;
	_Count = 1;
	_Index = 0;

	result = D3DXGetImageInfoFromFile(ImagePath, &info);
	if (result != D3D_OK)
	{
		trace(L"[ERROR] Failed to get information from image file '%s'", ImagePath);
		return;
	}

	LPDIRECT3DDEVICE9 d3ddv;
	SpriteHandler->GetDevice(&d3ddv);
	
	result = D3DXCreateTextureFromFileEx(
		d3ddv,
		ImagePath,
		info.Width,
		info.Height,
		1,
		D3DUSAGE_DYNAMIC,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		D3DCOLOR_XRGB(0, 0, 0),
		&info,
		NULL,
		&_Image);

	if (result != D3D_OK)
	{
		trace(L"[ERROR] Failed to create texture from file '%s'", ImagePath);
		return;
	}
}


Sprite::Sprite(LPD3DXSPRITE SpriteHandler,int posX, int posY, int Width, int Height)
{
	spriteInfo = new SpriteInfo[1];
	spriteInfo->pos_x = posX;
	spriteInfo->pos_y = posY;
	//
	//Init sprite with DirectX
	//
	HRESULT result;

	_Image = NULL;
	_SpriteHandler = SpriteHandler;
	_Width = Width;
	_Height = Height;
	_Count = 1;
	_Index = 0;


	LPDIRECT3DDEVICE9 d3ddv;
	SpriteHandler->GetDevice(&d3ddv);

	result = D3DXCreateTexture(
		d3ddv,
		Width,
		Height,
		1,
		D3DUSAGE_DYNAMIC,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		&_Image);

	if (result != D3D_OK)
	{
		trace(L"[ERROR] Failed to create texture");
		return;
	}
}

Sprite::~Sprite()
{
	delete(spriteInfo);
	_Image->Release();
}

void Sprite::Next()
{
	//_Index = (_Index + _Count - 1) % _Count;
	_Index = (_Index + 1) % _Count;
}

void Sprite::Reset()
{
	_Index = 0;
}

void Sprite::Render(int X, int Y)
{
	RECT rect;
	rect.left = spriteInfo[_Index].pos_x;
	rect.top = spriteInfo[_Index].pos_y;
	rect.right = spriteInfo[_Index].pos_x + _Width;
	rect.bottom = spriteInfo[_Index].pos_y + _Height;

	D3DXVECTOR3 position((float)X, (float)Y, 0);

	//
	// WORLD TO VIEWPORT TRANSFORM USING MATRIX
	//
	
	D3DXMATRIX mt;
	D3DXMatrixIdentity(&mt);
	mt._22 = -1.0f;
	mt._41 = -Camera::currentCamX;
	mt._42 = Camera::currentCamY;	// --TO DO:  Fix lại chỗ này sau
	D3DXVECTOR4 vp_pos;
	D3DXVec3Transform(&vp_pos, &position, &mt);

	D3DXVECTOR3 p(vp_pos.x, vp_pos.y, 0);
	
	D3DXVECTOR3 center((float)_Width / 2, (float)_Height / 2, 0);

	/*D3DXMATRIX mt1;
	D3DXMatrixScaling(&mt1, 1.5, 1.5, 1);
	_SpriteHandler->SetTransform(&mt1);*/

	_SpriteHandler->Draw(
		_Image,
		&rect,
		&center,
		&p,
		D3DCOLOR_XRGB(255, 255, 255)
	);
}

void Sprite::Render(int X, int Y, D3DXCOLOR color)
{
	RECT rect;
	rect.left = spriteInfo[_Index].pos_x;
	rect.top = spriteInfo[_Index].pos_y;
	rect.right = spriteInfo[_Index].pos_x + _Width;
	rect.bottom = spriteInfo[_Index].pos_y + _Height;

	D3DXVECTOR3 position((float)X, (float)Y, 0);

	//
	// WORLD TO VIEWPORT TRANSFORM USING MATRIX
	//

	D3DXMATRIX mt;
	D3DXMatrixIdentity(&mt);
	mt._22 = -1.0f;
	mt._41 = -Camera::currentCamX;
	mt._42 = Camera::currentCamY;	// --TO DO:  Fix lại chỗ này sau
	D3DXVECTOR4 vp_pos;
	D3DXVec3Transform(&vp_pos, &position, &mt);

	D3DXVECTOR3 p(vp_pos.x, vp_pos.y, 0);

	D3DXVECTOR3 center((float)_Width / 2, (float)_Height / 2, 0);

	/*D3DXMATRIX mt1;
	D3DXMatrixScaling(&mt1, 1.5, 1.5, 1);
	_SpriteHandler->SetTransform(&mt1);*/

	_SpriteHandler->Draw(
		_Image,
		&rect,
		&center,
		&p,
		D3DCOLOR_XRGB((int)color.r, (int)color.g, (int)color.b)
	);
}

int Sprite::GetIndex()
{
	return _Index;
}

int Sprite::GetCount()
{
	return _Count;
}
