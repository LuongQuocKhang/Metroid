#include <d3dx9.h>
#include "utils.h"
#include "trace.h"
#include "Camera.h"


LPDIRECT3DSURFACE9 CreateSurfaceFromFile(LPDIRECT3DDEVICE9 d3ddv, LPWSTR FilePath)
{
	D3DXIMAGE_INFO info; 

	HRESULT result = D3DXGetImageInfoFromFile(FilePath,&info);
	if (result!=D3D_OK)
	{
		trace(L"[ERROR] Failed to get image info '%s'",FilePath);
		return NULL;
	}

	LPDIRECT3DSURFACE9 surface;

	d3ddv->CreateOffscreenPlainSurface(
			info.Width,				// width
			info.Height,			// height
			D3DFMT_X8R8G8B8,		// format
			D3DPOOL_DEFAULT,		
			&surface,
			NULL);

	result = D3DXLoadSurfaceFromFile(
			surface, 		// surface
			NULL,			// destination palette	
			NULL,			// destination rectangle 
			FilePath,			
			NULL,			// source rectangle
			D3DX_DEFAULT, 	// filter image
			D3DCOLOR_XRGB(0,0,0),				// transparency (0 = none)
			NULL);			// reserved

	if (result!=D3D_OK)
	{
		trace(L"[ERROR] D3DXLoadSurfaceFromFile() failed");
		return NULL;
	}

	return surface;
}
void DrawCollider(LPDIRECT3DDEVICE9 d3ddv, float x, float y, Collider* collider, D3DCOLOR color)
{
	D3DXVECTOR3 position((float)x, (float)y, 0);

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


	CUSTOMVERTEX vertices[5];
	LPDIRECT3DVERTEXBUFFER9 vertexBuffer;

	vertices[0].x = vp_pos.x - collider->GetRight() / 2;
	vertices[0].y = vp_pos.y - collider->GetBottom() / 2;
	vertices[0].z = 0;
	vertices[0].weight = 5;
	vertices[0].color = color;

	vertices[1].x = vertices[0].x;
	vertices[1].y = vp_pos.y + collider->GetBottom() / 2;
	vertices[1].z = 0;
	vertices[1].weight = 5;
	vertices[1].color = color;

	vertices[2].x = vp_pos.x + collider->GetRight() / 2;
	vertices[2].y = vertices[1].y;
	vertices[2].z = 0;
	vertices[2].weight = 5;
	vertices[2].color = color;

	vertices[3].x = vertices[2].x;
	vertices[3].y = vertices[0].y;
	vertices[3].z = 0;
	vertices[3].weight = 5;
	vertices[3].color = color;

	vertices[4].x = vertices[0].x;
	vertices[4].y = vertices[0].y;
	vertices[4].z = 0;
	vertices[4].weight = 5;
	vertices[4].color = color;

	d3ddv->CreateVertexBuffer(5 * sizeof(CUSTOMVERTEX), 0, D3DFVF_XYZRHW | D3DFVF_DIFFUSE, D3DPOOL_DEFAULT, &vertexBuffer, NULL);


	VOID* p_Vertices;
	if (FAILED(vertexBuffer->Lock(0, 5 * sizeof(CUSTOMVERTEX), (void**)&p_Vertices, 0)))
	{
		/*MessageBox(han_Window, "Error trying to lock", "FillVertices()", MB_OK);*/
	}
	else {
		memcpy(p_Vertices, vertices, 5 * sizeof(CUSTOMVERTEX));
		vertexBuffer->Unlock();
	}
	d3ddv->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE);
	d3ddv->SetStreamSource(0, vertexBuffer, 0, sizeof(CUSTOMVERTEX));
	d3ddv->DrawPrimitive(D3DPT_LINESTRIP, 0, 4);

	vertexBuffer->Release();
}
