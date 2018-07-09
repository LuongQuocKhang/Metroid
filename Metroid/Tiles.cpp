//#include "Tiles.h"
//#include "trace.h"
//
//#include <iostream>
//#include <fstream>
//#include <string>
//using namespace std;
// int a[2000];
//Tiles::Tiles()
//{
//	s1 = NULL;
//	s2 = NULL;
//	s3 = NULL;
//	s4 = NULL;
//	s5 = NULL;
//	s6 = NULL;
//	s7 = NULL;
//	s8 = NULL;
//	s9 = NULL;
//	s10 = NULL;
//	s11 = NULL;
//	s12 = NULL;
//	s13 = NULL;
//	s14 = NULL;
//	s15 = NULL;
//	s16 = NULL;
//	s17 = NULL;
//	
//}
//
//
//Tiles::~Tiles()
//{
//	delete(s1);
//	delete(s2);
//	delete(s3);
//	delete(s4);
//	delete(s5);
//	delete(s6);
//	delete(s7);
//	delete(s8);
//	delete(s9);
//	delete(s10);
//	delete(s11);
//	delete(s12);
//	delete(s13);
//	delete(s14);
//	delete(s15);
//	delete(s16);
//	delete(s17);
//}
//
//void Tiles::InitSprites(LPDIRECT3DDEVICE9 d3ddv)
//{
//	if (d3ddv == NULL) return;
//	//Create sprite handler
//	HRESULT result = D3DXCreateSprite(d3ddv, &_SpriteHandler);
//	if (result != D3D_OK) return;
//
//	//Create instance of sprites
//	s1 = new Sprite(_SpriteHandler, TILES_SHEET_PATH, S1, S1_WIDTH, S1_HEIGHT, TILES_COUNT, SPRITE_PER_ROW);
//	s2 = new Sprite(_SpriteHandler, TILES_SHEET_PATH, S2, S1_WIDTH, S1_HEIGHT, TILES_COUNT, SPRITE_PER_ROW);
//	s3 = new Sprite(_SpriteHandler, TILES_SHEET_PATH, S3, S1_WIDTH, S1_HEIGHT, TILES_COUNT, SPRITE_PER_ROW);
//	s4 = new Sprite(_SpriteHandler, TILES_SHEET_PATH, S4, S1_WIDTH, S1_HEIGHT, TILES_COUNT, SPRITE_PER_ROW);
//	s5 = new Sprite(_SpriteHandler, TILES_SHEET_PATH, S5, S1_WIDTH, S1_HEIGHT, TILES_COUNT, SPRITE_PER_ROW);
//	s6 = new Sprite(_SpriteHandler, TILES_SHEET_PATH, S6, S1_WIDTH, S1_HEIGHT, TILES_COUNT, SPRITE_PER_ROW);
//	s7 = new Sprite(_SpriteHandler, TILES_SHEET_PATH, S7, S1_WIDTH, S1_HEIGHT, TILES_COUNT, SPRITE_PER_ROW);
//	s8 = new Sprite(_SpriteHandler, TILES_SHEET_PATH, S8, S1_WIDTH, S1_HEIGHT, TILES_COUNT, SPRITE_PER_ROW);
//	s9 = new Sprite(_SpriteHandler, TILES_SHEET_PATH, S9, S1_WIDTH, S1_HEIGHT, TILES_COUNT, SPRITE_PER_ROW);
//	s10 = new Sprite(_SpriteHandler, TILES_SHEET_PATH, S10, S1_WIDTH, S1_HEIGHT, TILES_COUNT, SPRITE_PER_ROW);
//	s11 = new Sprite(_SpriteHandler, TILES_SHEET_PATH, S11, S1_WIDTH, S1_HEIGHT, TILES_COUNT, SPRITE_PER_ROW);
//	s12 = new Sprite(_SpriteHandler, TILES_SHEET_PATH, S12, S1_WIDTH, S1_HEIGHT, TILES_COUNT, SPRITE_PER_ROW);
//	s13 = new Sprite(_SpriteHandler, TILES_SHEET_PATH, S13, S1_WIDTH, S1_HEIGHT, TILES_COUNT, SPRITE_PER_ROW);
//	s14 = new Sprite(_SpriteHandler, TILES_SHEET_PATH, S14, S1_WIDTH, S1_HEIGHT, TILES_COUNT, SPRITE_PER_ROW);
//	s15 = new Sprite(_SpriteHandler, TILES_SHEET_PATH, S15, S1_WIDTH, S1_HEIGHT, TILES_COUNT, SPRITE_PER_ROW);
//	s16 = new Sprite(_SpriteHandler, TILES_SHEET_PATH, S16, S1_WIDTH, S1_HEIGHT, TILES_COUNT, SPRITE_PER_ROW);
//	s17 = new Sprite(_SpriteHandler, TILES_SHEET_PATH, S17, S1_WIDTH, S1_HEIGHT, TILES_COUNT, SPRITE_PER_ROW);
//}
//
//void Tiles::ImportFile()
//{
//
//	string line,h;
//	int j = 0;
//	ifstream myfile("TILES.txt");
//	if (myfile.is_open())
//	{
//		while (getline(myfile, line))
//		{
//			for (int i = 0; i < line.length(); i++)
//			{
//				if (line[i] == '\t')
//				{
//					if (i>5 && line[i - 3] == '\t'&&line[i - 2] != '\t')
//					{
//						h = line.substr(i - 2, i);
//					}
//					else
//					{
//						h = line.substr(i - 1, i);
//					}
//				
//					int value = atoi(h.c_str());
//					a[j] = value;
//					j++;
//				}
//			}
//
//		}
//	}
//}
//
//void Tiles::Check(int a[], int vpx, int vpy, int c, int d)
//{
//	int j;
//	int i = 0;
//	for (j = d; j < c; j++)
//	{
//		if (a[j] == 0)
//		{
//			s1->Render(32 + i, 32); i += 32;
//		}
//		else if (a[j] == 1)
//		{
//			s2->Render(32 + i, 32); i += 32;
//		}
//		else if (a[j] == 2)
//		{
//			s3->Render(32 + i, 32); i += 32;
//		}
//		else if (a[j] == 3)
//		{
//			s4->Render(32 + i, 32); i += 32;
//		}
//		else if (a[j] == 4)
//		{
//			s5->Render(32 + i, 32); i += 32;
//		}
//		else if (a[j] == 5)
//		{
//			s6->Render(32 + i, 32); i += 32;
//		}
//		else if (a[j] == 6)
//		{
//			s7->Render(32 + i, 32); i += 32;
//		}
//		else if (a[j] == 7)
//		{
//			s8->Render(32 + i, 32); i += 32;
//		}
//		else if (a[j] == 9)
//		{
//			s10->Render(32 + i, 32); i += 32;
//		}
//		else if (a[j] == 10)
//		{
//			s11->Render(32 + i, 32); i += 32;
//		}
//		else if (a[j] == 11)
//		{
//			s12->Render(32 + i, 32); i += 32;
//		}
//		else if (a[j] == 12)
//		{
//			s13->Render(32 + i, 32); i += 32;
//		}
//		else if (a[j] == 13)
//		{
//			s14->Render(32 + i, 32); i += 32;
//		}
//		else if (a[j] == 14)
//		{
//			s15->Render(32 + i, 32); i += 32;
//		}
//		else if (a[j] == 15)
//		{
//			s16->Render(32 + i, 32); i += 32;
//		}
//		else if (a[j] == 16)
//		{
//			s17->Render(32 + i, 32); i += 32;
//		}
//		else
//		{
//			s9->Render(32 + i, 32); i += 32;
//		}
//	}
//	j = 0;
//	i = 0;
//}
//void Tiles::_Render(int xc, int samus_pos_x)
//{
//	_SpriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
//	
//	int vpx = samus_pos_x - 150;
//	//int vpx = xc;
//	//if (vpx <= 0) vpx = 0;
//	//xc += 1;
//	//s15->Render(32, 32, vpx, VIEW_PORT_Y1);
//	ImportFile();
//
//	int c = 80;
//	int d = VIEW_PORT_Y1;
//	int f = 0;
//	for (int i = 0; i < 15; i++)
//	{
//		Check(a, vpx, d, c, f); c += 80; d += 32;  f += 80;
//	}
//	_SpriteHandler->End();
//}