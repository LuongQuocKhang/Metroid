////Windows framwork source
//#define APP_CLASS L"Metroid-Debug"
//#define MAIN_WINDOW_TITLE L"Metroid-Debug"
//
//#define SCREEN_WIDTH 640
//#define SCREEN_HEIGHT 480
//#define FULLSCREEN true
//
//#include <d3d9.h>
//#include <d3dx9.h>
//#include <time.h>
//#include <windows.h>
//#include "dxgraphics.h"
//
////Windows event callback func
//LRESULT WINAPI WinProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
//{
//	switch (msg)
//	{
//		case WM_DESTROY:
//			PostQuitMessage(0);
//			break;
//		default:
//			return DefWindowProc(hWnd, msg, wParam, lParam);
//	}
//
//	return 0;
//}
//
////helper to set up the window properites
//ATOM MyRegisterClass(HINSTANCE hInstance)
//{
//	WNDCLASSEX wc;
//	wc.cbSize = sizeof(WNDCLASSEX);
//
//	wc.style = CS_HREDRAW | CS_VREDRAW;
//	wc.hInstance = hInstance;
//
//	wc.lpfnWndProc = (WNDPROC)WinProc;
//	wc.cbClsExtra = 0;
//	wc.cbWndExtra = 0;
//	wc.hIcon = NULL;
//	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
//	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
//	wc.lpszMenuName = NULL;
//	wc.lpszClassName = APP_CLASS;
//	wc.hIconSm = NULL;
//
//	return RegisterClassEx(&wc);
//}
//
////entry point for a Windows program
//int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreInstance, LPSTR lpCmdLine, int nCmdShow)
//{
//	MSG msg;
//	HWND hWnd;
//
//	//register class
//	MyRegisterClass(hInstance);
//
//	//set up the screen in windowed or fullscreen mode
//	DWORD style;
//	if (FULLSCREEN)
//		style = WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP;
//	else
//		style = WS_OVERLAPPED;
//
//	//create window
//	hWnd =
//		CreateWindow(
//			APP_CLASS,	// window class
//			APP_CLASS,  // title bar
//			style,		// windows style
//			CW_USEDEFAULT,  // x pos window
//			CW_USEDEFAULT,  // y pos window
//			SCREEN_WIDTH,   // width of window
//			SCREEN_HEIGHT,  // height of window
//			NULL,			// parent window
//			NULL,			// menu
//			hInstance,		// application instance
//			NULL			// window parameters
//		);
//
//	//Check if cant create window
//	if (!hWnd)
//		return FALSE;
//
//	//Display the window
//	ShowWindow(hWnd, nCmdShow);
//	UpdateWindow(hWnd);
//
//	//TO-DO: Update soon!
//	// ...
//	if (!Init_Direct3D(hWnd, SCREEN_WIDTH, SCREEN_HEIGHT, FULLSCREEN))
//		return 0;
//
//	//Init game
//	if (d3ddev == NULL)
//		return;
//
//	//This keeps the game running at a steady frame rate
//	if (GetTickCount() - start >= 30)
//	{
//		//reset timing
//
//	}
//}
//
//void InitWindow()
//{
//	WNDCLASSEX wc;
//	wc.cbSize = sizeof(WNDCLASSEX);
//
//	wc.style = CS_HREDRAW | CS_VREDRAW;
//	wc.hInstance = hInstance;
//
//	wc.lpfnWndProc = (WNDPROC)WinProc;
//	wc.cbClsExtra = 0;
//	wc.cbWndExtra = 0;
//	wc.hIcon = NULL;
//	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
//	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
//	wc.lpszMenuName = NULL;
//	wc.lpszClassName = APP_CLASS;
//	wc.hIconSm = NULL;
//	RegisterClassEx(&wc);
//
//	MSG msg;
//	HWND hWnd;
//
//	//register class
//	MyRegisterClass(hInstance);
//
//	//set up the screen in windowed or fullscreen mode
//	DWORD style;
//	if (FULLSCREEN)
//		style = WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP;
//	else
//		style = WS_OVERLAPPED;
//
//	//create window
//	hWnd =
//		CreateWindow(
//			APP_CLASS,	// window class
//			APP_CLASS,  // title bar
//			style,		// windows style
//			CW_USEDEFAULT,  // x pos window
//			CW_USEDEFAULT,  // y pos window
//			SCREEN_WIDTH,   // width of window
//			SCREEN_HEIGHT,  // height of window
//			NULL,			// parent window
//			NULL,			// menu
//			hInstance,		// application instance
//			NULL			// window parameters
//		);
//
//	//Check if cant create window
//	if (!hWnd)
//		return FALSE;
//
//	//Display the window
//	ShowWindow(hWnd, nCmdShow);
//	UpdateWindow(hWnd);
//}
//
