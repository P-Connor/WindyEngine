#include "Graphics.h"
#include "WindyMath.h"

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

void Graphics::FillPixel(int x, int y, COLORREF color)
{
	if (x < resolution.X && x >= 0 && y < resolution.Y && y >= 0) {
		int index = (y * (4 * resolution.X)) + (4 * x);
		bufferBytes[index + 0] = GetBValue(color);
		bufferBytes[index + 1] = GetGValue(color);
		bufferBytes[index + 2] = GetRValue(color);
	}
}

COLORREF Graphics::GetPixel(int x, int y)
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

void Graphics::DrawLine(Vector2<int> p1, Vector2<int> p2, HDC hdc, COLORREF color)
{
	double slope;
	if ((p1.X - p2.X) != 0) {
		slope = (double)(p1.Y - p2.Y) / (p1.X - p2.X);	//Calculate slope
	}
	else {
		slope = 65536;
	}
	int adjust = (slope >= 0) ? 1 : -1;					//Adjust negatively or positively based on slope
	slope = WindyMath::Abs(slope);						//Make slope positive for incrementation
	double doubleSlope;
	double offset = 0;									//For storing how "high" we've gotten so far
	int threshold = 1;									//When offset passes this, increment "height" and update increment
	int x1, x2;
	int y1, y2;
	
	if (slope <= 1) {	//If going more horizontal
		
		doubleSlope = slope * 2;

		if (p1.X < p2.X) {	//Make coords align in positive x direction
			x1 = p1.X;	x2 = p2.X;	y1 = p1.Y;
		}
		else {
			x1 = p2.X;	x2 = p1.X;	y1 = p2.Y;
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

		if (p1.Y < p2.Y) {	//Make coords align in positive y direction
			y1 = p1.Y;	y2 = p2.Y;	x1 = p1.X;
		}
		else {
			y1 = p2.Y;	y2 = p1.Y;	x1 = p2.X;
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
}

void Graphics::DrawLine(const int & X1, const int & Y1, const int & X2, const int & Y2, HDC hdc, COLORREF color)
{
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
}

void Graphics::DrawTriangle(Vector2<int> p1, Vector2<int> p2, Vector2<int> p3, HDC hdc, COLORREF color)
{
	DrawLine(p1, p2, hdc, color);
	DrawLine(p2, p3, hdc, color);
	DrawLine(p1, p3, hdc, color);
}
