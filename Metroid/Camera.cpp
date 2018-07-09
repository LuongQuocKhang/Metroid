#include "Camera.h"
vector<CamInfo> Camera::list;

int Camera::index = 0;

float Camera::currentCamX = 480;
float Camera::currentCamY = 480;
//float Camera::currentCamY = 4000;

float Camera::max_x = 2560;
float Camera::min_x = 0;

float Camera::max_y = 0;
float Camera::min_y = 0;

int Camera::width =  480;
int Camera::height =  500;

float Camera::speed = 0.2f;

bool Camera::moveLeft = false;
bool Camera::moveRight = false;

Camera::Camera()
{
	Camera::SetDemension(GAME_SCREEN_RESOLUTION_480_480_24);
}


Camera::~Camera()
{
}

void Camera::SetCameraX(float pos_x, float t)
{

	if (moveRight == true)
	{
		currentCamX += speed * t;
		// Nếu current đã chạy đến vị trí max
		if (currentCamX >= list[index + 1].min_x)
		{
			
			moveRight = false;	//Ngừng hiệu ứng chuyển camera
			index++;
			//min_x = max_x;		//Gán min bằng max, rồi max gán mức tiếp theo
			//max_x += 500;	//test
		}
		return;
	}
	if (moveLeft == true)
	{
		currentCamX -= speed * t;
		// Nếu góc phải camera đã chạy đến vị trí min
		if (currentCamX + width <= list[index - 1].max_x)
		{
			moveLeft = false;	//Ngừng hiệu ứng chuyển camera
			index--;
			//max_x = min_x;		//Gán max bằng min, rồi min gán mức nhỏ hơn
		}
		return;
	}

	if (list[index].max_x == list[index].min_x) return;

	currentCamX = pos_x - 240;
	
	if (currentCamX < list[index].min_x)
	{
		currentCamX = list[index].min_x;
	}
	else if (currentCamX + width >= list[index].max_x)
	{
		currentCamX = list[index].max_x - width;
	}
}

void Camera::SetCameraY(float pos_y, float t)
{
	if (list[index].max_y == list[index].min_y) return;
	
	currentCamY = pos_y + 240;

	if (currentCamY < list[index].min_y)
	{
		currentCamY = list[index].min_y;
	}
	if (currentCamY + height >= list[index].max_y)
	{
		currentCamY = list[index].max_y;
	}
}

void Camera::SetDemension(int mode)
{
	switch (mode)
	{
	case GAME_SCREEN_RESOLUTION_480_480_24:
		width = 480;
		height = 480;
		break;
	case GAME_SCREEN_RESOLUTION_640_480_24:
		width = 640;
		height = 480;
		break;
	case GAME_SCREEN_RESOLUTION_800_600_24:
		width = 800;
		height = 600;
		break;
	case GAME_SCREEN_RESOLUTION_1024_768_24:
		width = 1024;
		height = 768;
		break;
	}
}


int Camera::GetCameraX()
{
	return currentCamX;
}

int Camera::GetCameraY()
{
	return currentCamY;
}

bool Camera::IsInCamera(float x, float y, float width, float height)
{
		 //Kiềm tra bên trái
		if (x + width < Camera::currentCamX)
			return false;
		// Kiểm tra phía trên
		if (y + height > Camera::currentCamY)
			return false;
		// Kiểm tra bên phải
		if (x > Camera::currentCamX + Camera::width)
			return false;
		// Kiểm tra phía dưới
		if (y < Camera::currentCamY - Camera::height)
			return false;
	
		return true;
}
