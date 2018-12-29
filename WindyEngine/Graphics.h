#pragma once
#include <Windows.h>
#include "Vector2.h"
#include "Vertex3.h"
#include "Camera.h"

class Graphics {
	
public:
	Graphics();
	Graphics(HDC& hdc, const Vector2<int>& _resolution);
	~Graphics();

	Graphics(const Graphics& g) {
		memoryHDC = g.memoryHDC;
		pixelBuffer = g.pixelBuffer;
		pixelBufferInfo = g.pixelBufferInfo;
		pixelBufferBytes = g.pixelBufferBytes;
		zBufferBytes = g.zBufferBytes;
		resolution = g.resolution;
		return;
	}

	const HDC& GetMemoryHDC();
	void ClearBuffer();
	void FillPixel(const int&, const int&, const COLORREF&);
	COLORREF GetPixel(const int&, const int&);
	void DrawLine(const Vector2<int>&, const Vector2<int>&, const COLORREF&);
	void DrawLine(const int&, const int&, const int&, const int&, const COLORREF&);
	void DrawTriangle(Vertex3, Vertex3, Vertex3);
	void DrawTriangleScanline(const Vertex3&, const Vertex3&, const Vertex3&);
	bool isCounterClockwise(const Vertex3&, const Vertex3&, const Vertex3&);

private:
	HDC memoryHDC;
	HBITMAP pixelBuffer;
	BITMAPINFO pixelBufferInfo;
	unsigned char *pixelBufferBytes = 0;
	double *zBufferBytes = 0;
	Vector2<int> resolution;
};