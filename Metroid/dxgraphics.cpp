//// Direct3D framework source
//
//#include <d3d9.h>
//#include <d3dx9.h>
//#include "dxgraphics.h"
//
////variable declarations
//LPDIRECT3D9 _d3d = NULL;
//LPDIRECT3DDEVICE9 d3ddv = NULL;
//LPDIRECT3DSURFACE9 back_buffer = NULL;
////khang
//int Init_Direct3D(HWND hWnd, int width, int height, int fullscreen)
//{
//	_d3d = Direct3DCreate9(D3D_SDK_VERSION);
//	D3DPRESENT_PARAMETERS d3dpp;
//
//	ZeroMemory(&d3dpp, sizeof(d3dpp));
//
//	d3dpp.Windowed = fullscreen ? FALSE : TRUE;
//
//	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
//
//	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;;
//	d3dpp.BackBufferCount = 1;
//	d3dpp.BackBufferHeight = height;
//	d3dpp.BackBufferWidth = width;
//	d3dpp.hDeviceWindow = hWnd;
//
//
//	_d3d->CreateDevice(
//		D3DADAPTER_DEFAULT,
//		D3DDEVTYPE_HAL,
//		hWnd,
//		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
//		&d3dpp,
//		&d3ddv);
//
//	if (d3ddv == NULL)
//	{
//		MessageBox(hWnd, (LPCWCHAR)"Error create Direct3D device", (LPCWCHAR)"Error", MB_OK);
//		return 0;
//	}
//
//	d3ddv->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &back_buffer);
//	return 0;
//}
////khang
//LPDIRECT3DSURFACE9 LoadSurface(LPWSTR filename, D3DCOLOR transcolor)
//{
//	LPDIRECT3DSURFACE9 image = NULL;
//	D3DXIMAGE_INFO info;
//	HRESULT result;
//
//	// get width and height from bitmap file
//	result = D3DXGetImageInfoFromFile(filename, &info);
//
//	if (result != D3D_OK)
//	{
//		return NULL;
//	}
//	// create surface
//	result = d3ddev->CreateOffscreenPlainSurface(info.Width,
//		info.Height,
//		D3DFMT_X8R8G8B8, // format
//		D3DPOOL_DEFAULT, // memory pool to use
//		&image, // pointer to the surface
//		NULL);
//
//	// load surface from file into newly created surface
//	result = D3DXLoadSurfaceFromFile(
//		image, // des surface
//		NULL, // des palate
//		NULL,
//		filename,
//		NULL,
//		D3DX_DEFAULT,
//		transcolor,
//		NULL
//	);
//
//	if (result != D3D_OK)
//		return NULL;
//
//	return image;
//}
//
