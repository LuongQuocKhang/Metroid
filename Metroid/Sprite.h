#pragma once
#ifndef _SPRITE_H_
#define _SPRITE_H_

#include <d3d9.h>
#include <d3dx9.h>
typedef struct SPRITEINFO
{
	int pos_x;
	int pos_y;
}SpriteInfo;

class Sprite
{
protected:
	LPDIRECT3DTEXTURE9 _Image;				// The container of all the sprites
	LPD3DXSPRITE _SpriteHandler;
		
	int _Index;								// Current sprite index
	int _Width;								// Sprite width
	int _Height;							// Sprite height
	int _Count;								// Number of sprites
	int _SpritePerRow;						// Number of sprites per row
	SpriteInfo* spriteInfo;				    // Array contain position of each sprite
public:
	Sprite();

	//Constructor cho những GameObject có animation, nhiều sprite
	Sprite(LPD3DXSPRITE SpriteHandler, LPWSTR ImagePath, char* infoFilePath, int Width, int Height, int Count, int SpritePerRow);
	
	//Constructor cho những GameObject chỉ có duy nhất 1 sprite (đỡ dài dòng)
	Sprite(LPD3DXSPRITE SpriteHandler, LPWSTR ImagePath, int posX, int posY, int Width, int Height);

	Sprite(LPD3DXSPRITE SpriteHandler, int posX, int posY, int Width, int Height);
	~Sprite();

	void Next();
	void Reset();

	// Render current sprite at location (X,Y)
	void Render(int X, int Y);

	//============== GET METHOD ======================
	int GetIndex();
	int GetCount();
	//============== END GET METHOD ==================
};
#endif
