#pragma once
#ifndef _GAME_H_
#define _GAME_H_
#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <dinput.h>
#include "Parameters.h"
#include "SoundManager.h"

#define KEY_DOWN(code) ( IsKeyDown(code) )

#define KEYBOARD_BUFFER_SIZE	1024
class Game
{
protected:
	LPDIRECT3D9			_d3d;
	LPDIRECT3DDEVICE9	_d3ddv;
	LPDIRECT3DSURFACE9 _BackBuffer;

	LPDIRECTINPUT8       _di;		// The DirectInput object         
	LPDIRECTINPUTDEVICE8 _Keyboard;	// The keyboard device 

	BYTE  _KeyStates[256];			// DirectInput keyboard state buffer 
								
	DIDEVICEOBJECTDATA _KeyEvents[KEYBOARD_BUFFER_SIZE]; // Buffered keyboard data


	DWORD _DeltaTime;		// Time between the last frame and current frame
	int _Mode;				// Screen mode 
	int _IsFullScreen;		// Is running in fullscreen mode?
	int _FrameRate;

	int _ScreenWidth;
	int _ScreenHeight;
	int _Depth;

	D3DFORMAT _BackBufferFormat;

	HINSTANCE	_hInstance;	// Handle of the game instance
	HWND		_hWnd;				// Handle of the Game Window

	LPWSTR		_Name;			// Name of game will be used as Window Class Name

	void _SetScreenDimension(int Mode);

	static LRESULT CALLBACK _WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	//Init method
	void _InitWindow();
	void _InitDirectX();
	void _InitKeyboard();

	void _ProcessKeyBoard();
	int IsKeyDown(int KeyCode);

	// Render a single frame
	void _RenderFrame();

	//
	//====================== VIRTUAL METHOD ===========================
	//
	virtual void Update(float Delta);
	// Đã bỏ delta time cho phương thức Render
	virtual void Render(LPDIRECT3DDEVICE9 d3ddv);
	virtual void LoadResources(LPDIRECT3DDEVICE9 d3ddv);
	virtual void ProcessInput(LPDIRECT3DDEVICE9 d3ddv, float Delta);

	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
	//======================= END VIRTUAL METHOD ======================

public:
	//Doi tuong Direct Sound
	static SoundManager *gameSound;

	LPDIRECT3D9 GetDirectX();
	LPDIRECT3DDEVICE9 GetDevice();
	LPDIRECT3DSURFACE9 GetBackBuffer();

	int GetMode();

	int GetScreenWidth();
	int GetScreenHeight();
	int GetDepth();
	int FrameRate;

	Game();
	Game(HINSTANCE hInstance, LPWSTR Name, int Mode, int IsFullscreen, int FrameRate) ;
	~Game();

	// Initialize the game with set parameters
	void Init();

	// Run game
	void Run();
};

#endif


