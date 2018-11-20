#include "Graphics.h"
#include "WindyMath.h"
#include "Timer.h"
#include "Debug.h"

Graphics::Graphics()
{
	return;
}

Graphics::Graphics(HDC& hdc, const Vector2<int>& _res)
{
	memoryHDC = CreateCompatibleDC(hdc);
	resolution = _res;

	bufferInfo = { 0 };
	bufferInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bufferInfo.bmiHeader.biWidth = resolution.X;
	bufferInfo.bmiHeader.biHeight = -resolution.Y;
	bufferInfo.bmiHeader.biPlanes = 1;
	bufferInfo.bmiHeader.biBitCount = 32;
	bufferInfo.bmiHeader.biCompression = BI_RGB;
	bufferInfo.bmiHeader.biSizeImage = resolution.X * resolution.Y * 4;
	bufferInfo.bmiHeader.biClrUsed = 0;
	bufferInfo.bmiHeader.biClrImportant = 0;
	buffer = CreateDIBSection(memoryHDC, &bufferInfo, DIB_RGB_COLORS, (void**)&bufferBytes, NULL, NULL);

	SelectObject(memoryHDC, buffer);
}

Graphics::~Graphics()
{
	DeleteObject(buffer);
}

const HDC& Graphics::GetMemoryHDC()
{
	return memoryHDC;
}

void Graphics::ClearBuffer() {		
	memset(bufferBytes, 0, bufferInfo.bmiHeader.biSizeImage);
}

void Graphics::FillPixel(const int& x, const int& y, const COLORREF& color)
{
	if (x < resolution.X && x >= 0 && y < resolution.Y && y >= 0) {
		int index = (y * (4 * resolution.X)) + (4 * x);
		bufferBytes[index + 0] = GetBValue(color);
		bufferBytes[index + 1] = GetGValue(color);
		bufferBytes[index + 2] = GetRValue(color);
	}
}

COLORREF Graphics::GetPixel(const int& x, const int& y)
{
	if (x < resolution.X && x >= 0 && y < resolution.Y && y >= 0) {
		int index = (y * (4 * resolution.X)) + (4 * x);
		
		int bVal = (int)bufferBytes[index + 0];
		int gVal = (int)bufferBytes[index + 1];
		int rVal = (int)bufferBytes[index + 2];
		
		return RGB(rVal, gVal, bVal);
	}
	else {
		return NULL;
	}
}

void Graphics::DrawLine(const Vector2<int>& p1, const Vector2<int>& p2, const COLORREF& color)
{
	DrawLine(p1.X, p1.Y, p2.X, p2.Y, color);
}

void Graphics::DrawLine(const int& X1, const int& Y1, const int& X2, const int& Y2, const COLORREF& color)
{
	Timer timer1;

	double slope;
	if ((X1 - X2) != 0) {
		slope = (double)(Y1 - Y2) / (X1 - X2);	//Calculate slope
	}
	else {
		slope = 65536;
	}
	int adjust = (slope >= 0) ? 1 : -1;		//Adjust negatively or positively based on slope
	slope = WindyMath::Abs(slope);			//Make slope positive for incrementation
	double doubleSlope;
	double offset = 0;						//For storing how "high" we've gotten so far
	int threshold = 1;						//When offset passes this, increment "height" and update increment
	int x1, x2;
	int y1, y2;

	if (slope <= 1) {	//If going more horizontal

		doubleSlope = slope * 2;

		if (X1 < X2) {	//Make coords align in positive x direction
			x1 = X1;	x2 = X2;	y1 = Y1;
		}
		else {
			x1 = X2;	x2 = X1;	y1 = Y2;
		}

		int y = y1;
		for (int x = x1; x < x2; x++) {

			if (offset >= threshold) {
				y += adjust;
				threshold += 2;
			}

			FillPixel(x, y, color);

			offset += doubleSlope;
		}
	}
	else {	//If going more vertical

		slope = 1 / slope;
		doubleSlope = slope * 2;

		if (Y1 < Y2) {	//Make coords align in positive y direction
			y1 = Y1;	y2 = Y2;	x1 = X1;
		}
		else {
			y1 = Y2;	y2 = Y1;	x1 = X2;
		}

		int x = x1;
		for (int y = y1; y < y2; y++) {

			if (offset >= threshold) {
				x += adjust;
				threshold += 2;
			}

			FillPixel(x, y, color);

			offset += doubleSlope;
		}

	}

	WinDebug.Log(timer1.Value());
	timer1.Reset();
}

void Graphics::DrawTriangle(const Vertex3& vertex1, const Vertex3& vertex2, const Vertex3& vertex3)
{
	const static COLORREF color = RGB(255, 255, 255);
	DrawLine((int)vertex1.position.X, (int)vertex1.position.Y, (int)vertex2.position.X, (int)vertex2.position.Y, color);
	DrawLine((int)vertex2.position.X, (int)vertex2.position.Y, (int)vertex3.position.X, (int)vertex3.position.Y, color);
	DrawLine((int)vertex1.position.X, (int)vertex1.position.Y, (int)vertex3.position.X, (int)vertex3.position.Y, color);

	/*
	//Sort vertices from smallest Y to largest Y (top to bottom)
	Vector3<double> v1 = vertex1.position, v2 = vertex2.position, v3 = vertex3.position;
	if (v1.Y > v2.Y) {
		std::swap(v1, v2);
	}
	if (v1.Y > v3.Y) {
		std::swap(v1, v3);
	}
	if (v2.Y > v3.Y) {
		std::swap(v2, v3);
	}

	//Split triangle into two horizontal-sided triangles
	Vector2<int> v4 ((int)(v1.X + ((float)(v2.Y - v1.Y) / (float)(v3.Y - v1.Y)) * (v3.X - v1.X)), v2.Y);

	//Draw bottom-faced triangle using v1, v2, and v4
	DrawLine(v1.X, v1.Y, v2.X, v2.Y, RGB(0, 255, 0));
	DrawLine(v1.X, v1.Y, v4.X, v4.Y, RGB(0, 255, 0));
	DrawLine(v2.X, v2.Y, v4.X, v4.Y, RGB(0, 255, 0));

	int dxL = (v1.X - v2.X), dyL = (v1.Y - v2.Y);
	double slopeL;
	bool switchedL;
	double offsetL = 0;
	int thresholdL = 1;
	if (dxL < dyL) {
		slopeL = dxL / dyL;
		switchedL = true;
	}
	else {
		slopeL = dyL / dxL;
		switchedL = false;
	}

	int dxR = (v1.X - v4.X), dyR = (v1.Y - v4.Y);
	double slopeR;
	bool switchedR;
	double offsetR = 0;
	int thresholdR = 1;
	if (dxR < dyR) {
		slopeR = 2 * abs((double)dxR / dyR);
		switchedR = true;
	}
	else {
		slopeR = 2 * abs((double)dyR / dxR);
		switchedR = false;
	}

	int incL = (dxL >= 0) ? -1 : 1;
	int incR = (dxR >= 0) ? -1 : 1;

	int x = v1.X, y = v1.Y;
	int xR = x, yR = y;
	if (switchedL) {
		
	}
	else {
		for (int xL = v1.X; xL != (int)v2.X + incL; xL += incL) {
			if (offsetL >= thresholdL) {
				thresholdL += 2;

				do {
					if (switchedR) {
						offsetR += slopeR;
						yR += incR;
					}
					else {
						offsetR += slopeR;
						xR += incR;
					}
				} while (offsetR < thresholdR);

				thresholdR += 2;

				y++;
			}

			offsetL += slopeL;
			FillPixel(xL, y, color);
			FillPixel(xR, y, color);
			//for (int i = xL; i != xR; i -= (abs(xL - xR) / (xL - xR))) {
			//	FillPixel(i, y, color + i);
			//}
		}
	}
	



	//Draw top-faced triangle using v3, v4, and v2
	DrawLine(v3.X, v3.Y, v4.X, v4.Y, RGB(0, 0, 255));
	DrawLine(v3.X, v3.Y, v2.X, v2.Y, RGB(0, 0, 255));

	slopeL = (v3.Y - v4.Y) / (v3.X - v4.X);
	int incL = (v3.X - v4.X >= 0) ? -1 : 1;
	slopeL = abs(slopeL * 2);
	double offsetL = 0;
	int thresholdL = 1;

	slopeR = (v3.Y - v2.Y) / (v3.X - v2.X);
	int incR = (v3.X - v2.X >= 0) ? -1 : 1;
	slopeR = abs(slopeR * 2);
	double offsetR = 0;
	int thresholdR = 1;

	if (slopeL <= 1) {
		int y = v3.Y;
		int xR = (int)v4.X;
		for (int xL = v3.X; xL != (int)v4.X + incL; xL += incL) {
			if (offsetL >= thresholdL) {
				thresholdL += 2;

				do {
					offsetR += slopeR;
					xR += incR;
				} while (offsetR < thresholdR);
				thresholdR += 2;

				y--;
			}

			offsetL += slopeL;
			//FillPixel(xL, y, color);
			//FillPixel(xR, y, color);
		}
	}
	*/
}

bool Graphics::EdgeFunction(const Vector3<double>& v1, const Vector3<double>& v2, const Vector3<double>& v3)
{
	return ((v3.X - v1.X) * (v2.Y - v1.Y) - (v3.Y - v1.Y) * (v2.X - v1.X) >= 0);
}


