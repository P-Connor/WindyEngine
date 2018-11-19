#pragma once
#include <Windows.h>
#include "Vector2.h"
#include "Camera.h"

class Graphics {
	
public:
	Graphics();
	Graphics(HDC& hdc, const Vector2<int>& _resolution);
	~Graphics();

	const HDC& GetMemoryHDC();
	void ClearBuffer();
	void FillPixel(int, int, COLORREF);
	COLORREF GetPixel(int, int);
	void DrawLine(Vector2<int>, Vector2<int>, HDC, COLORREF);
	void DrawLine(const int&, const int&, const int&, const int&, HDC, COLORREF);
	void DrawTriangle(Vector2<int>, Vector2<int>, Vector2<int>, HDC, COLORREF);

private:
	HDC memoryHDC;
	HBITMAP buffer;
	BITMAPINFO bufferInfo;
	unsigned char *bufferBytes = 0;
	Vector2<int> resolution;
};