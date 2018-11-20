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
	void FillPixel(const int&, const int&, const COLORREF&);
	COLORREF GetPixel(const int&, const int&);
	void DrawLine(const Vector2<int>&, const Vector2<int>&, const COLORREF&);
	void DrawLine(const int&, const int&, const int&, const int&, const COLORREF&);
	void DrawTriangle(const Vector2<int>&, const Vector2<int>&, const Vector2<int>&);

private:
	HDC memoryHDC;
	HBITMAP buffer;
	BITMAPINFO bufferInfo;
	unsigned char *bufferBytes = 0;
	Vector2<int> resolution;
};