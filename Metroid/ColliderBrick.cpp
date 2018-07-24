#include "ColliderBrick.h"
#include "Metroid.h"
#include "World.h"
#include "utils.h"

ColliderBrick::ColliderBrick()
{
}

ColliderBrick::ColliderBrick(LPD3DXSPRITE spriteHandler, World * manager, float posX, float posY, float width, float height)
{
	this->d3ddv = manager->metroid->GetDevice();
	this->type = COLLIDER_BRICK;
	this->pos_x = posX;
	this->pos_y = posY;
	this->width = width;
	this->height = height;

	isPassable = false;
	collider = new Collider(0, 0, -this->height, this->width);

	d3ddv->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &back_buffer);

	// Create a small off-screen surface (will fill it contain in GameRun)
	int result =
		d3ddv->CreateOffscreenPlainSurface(
			100,					// width 				
			100,					// height
			D3DFMT_X8R8G8B8,		// format
			D3DPOOL_DEFAULT,		// where? (VRAM or RAM)
			&surface,
			NULL);
}


ColliderBrick::~ColliderBrick()
{
}

void ColliderBrick::Render()
{
	
}
void ColliderBrick::RenderDebug(LPDIRECT3DDEVICE9 d3ddv, D3DCOLOR color)
{
	Render();

	D3DXVECTOR3 position(this->pos_x, this->pos_y, 0);

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
	vp_pos.x = vp_pos.x - 16;
	vp_pos.y = vp_pos.y - 16;

	vertices[0].x = vp_pos.x;
	vertices[0].y = vp_pos.y - collider->GetBottom();
	vertices[0].z = 0;
	vertices[0].weight = 5;
	vertices[0].color = color;

	vertices[1].x = vertices[0].x;
	vertices[1].y = vp_pos.y;
	vertices[1].z = 0;
	vertices[1].weight = 5;
	vertices[1].color = color;

	vertices[2].x = vp_pos.x + collider->GetRight();
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