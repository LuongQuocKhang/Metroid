//#include "vsgame.h"
//
//LPDIRECT3DSURFACE9 samus_image[7];
//SPRITE samus;
//
////timing variable
//long start = GetTickCount();
//
////init the game
//int Game_Init(HWND hwnd)
//{
//	char s[20];
//	int n;
//
//	//set random number seed
//	srand(time(NULL));
//
//	//load the sprite animation
//	//--TO DO: Will be edited
//	for (n = 0; n < 6; n++)
//	{
//		sprintf(s, "samus %d.png", n + 1);
//		samus_image[n] = LoadSurface(s, D3DCOLOR_XRGB(255, 0, 255));
//		if (samus_image[n] == NULL)
//			return 0;
//	}
//
//	//intit sprite properties
//	//-- TO DO: Will be edited
//	samus.x = 0;
//	samus.y = 0;
//	samus.width = 0;
//	samus.height = 0;
//	samus.curframe = 0;
//	samus.lastframe = 0;
//	samus.animdelay = 2;
//	samus.animcount = 0;
//	samus.movex = 8;
//	samus.movey = 0;
//
//	//return okay
//	return  1;
//}
//
////the main game loop
//void Game_Run(HWND hwnd)
//{
//	RECT rect;
//
//	//make sure Direct3D is valid
//	if (GetTickCount() - start >= 30)
//	{
//
//	}
//}