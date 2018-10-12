#include "Graphics.h"

Graphics::Graphics(HWND hwnd, RECT workSpace)
{
	device = GetDC(hwnd);
	bufferDevice = CreateCompatibleDC(device);
	this->workSpace = workSpace;

	hScreen = CreateCompatibleBitmap(device, workSpace.right, workSpace.bottom);
	oldBmp = (HBITMAP)SelectObject(bufferDevice, hScreen);

	image = (HBITMAP)LoadImage(0, "sprite.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	GetObject(image, sizeof(BITMAP), &bm);
	spriteDevice = CreateCompatibleDC(device);
	SelectObject(spriteDevice, image);
}

Graphics::~Graphics()
{
	DeleteObject(hScreen);
	DeleteObject(oldBmp);
	DeleteObject((HBITMAP)image);
	DeleteDC(bufferDevice);
	DeleteDC(device);
	DeleteDC(spriteDevice);
}

void Graphics::DrawEllipse(HWND hWnd, float X, float Y, float radius)
{
	BeginPaint(hWnd, &PStruct);
	PatBlt(bufferDevice, 0, 0, workSpace.right, workSpace.bottom, WHITENESS);

	Ellipse(bufferDevice, (int)X, (int)Y, X + radius, Y + radius);

	BitBlt(device, 0, 0, workSpace.right, workSpace.bottom, bufferDevice, 0, 0, SRCCOPY);

	EndPaint(hWnd, &PStruct);
}

void Graphics::DrawSprite(HWND hWnd, float X, float Y)
{
	BeginPaint(hWnd, &PStruct);
	PatBlt(bufferDevice, 0, 0, workSpace.right, workSpace.bottom, WHITENESS);

	BitBlt(bufferDevice, (int)X, (int)Y, bm.bmWidth, bm.bmHeight, spriteDevice, 0, 0, SRCCOPY);
	
	BitBlt(device, 0, 0, workSpace.right, workSpace.bottom, bufferDevice, 0, 0, SRCCOPY);

	EndPaint(hWnd, &PStruct);
}

vergePoint *Graphics::GetPoints(int type, float radius)
{
	switch (type)
	{
	case 1:
		points.bottom = radius;
		points.left = 0;
		points.right = radius;
		points.top = 0;

		points.mouseX = -radius / 2;
		points.mouseY = -radius / 2;
		break;

	default:
		points.bottom = 20.f;
		points.left = 20.f;
		points.right = 20.f;
		points.top = 20.f;
		points.mouseX = 0;
		points.mouseY = 0;
		break;
	}

	return &points;
}