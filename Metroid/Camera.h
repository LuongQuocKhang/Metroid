#pragma once
#include "Parameters.h"
#include <vector>
using namespace std;
struct CamInfo
{
	float min_x;
	float max_x;
	float min_y;
	float max_y;
};
class Camera
{
public:
	static vector<CamInfo> list;

	static int index;

	static float max_x;
	static float min_x;

	static float max_y;
	static float min_y;

	static float currentCamX;
	static float currentCamY;

	static int width;	// width của viewport
	static int height;	// height của viewport

	static float speed;

	static bool moveLeft;
	static bool moveRight;

	Camera();
	~Camera();

	static void SetCameraX(float pos_x, float t);
	static void SetCameraY(float pos_y, float t);

	static int GetCameraX(); 
	static int GetCameraY();


	static void SetDemension(int mode);

	static bool IsInCamera(float x, float y, float width, float height);
};