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

void Graphics::DrawTriangle(const Vertex3& v1, const Vertex3& v2, const Vertex3& v3)
{
	static Timer t1;

	// Compute triangle bounding box
	double minX = WindyMath::Min3(v1.position.X, v2.position.X, v3.position.X);
	double minY = WindyMath::Min3(v1.position.Y, v2.position.Y, v3.position.Y);
	double maxX = WindyMath::Max3(v1.position.X, v2.position.X, v3.position.X);
	double maxY = WindyMath::Max3(v1.position.Y, v2.position.Y, v3.position.Y);

	/*
	// Clip against screen bounds
	minX = max(minX, 0);
	minY = max(minY, 0);
	maxX = min(maxX, screenWidth - 1);
	maxY = min(maxY, screenHeight - 1);
	*/

	double A12 = v1.position.Y - v2.position.Y, B12 = v2.position.X - v1.position.X;
	double A23 = v2.position.Y - v3.position.Y, B23 = v3.position.X - v2.position.X;
	double A31 = v3.position.Y - v1.position.Y, B31 = v1.position.X - v3.position.X;

	// Rasterize
	Vector2<double> p(minX, minY);
	double w0_row = (A23)* p.X + (B23)* p.Y + (v2.position.X * v3.position.Y - v2.position.Y * v3.position.X);
	double w1_row = (A31)* p.X + (B31)* p.Y + (v3.position.X * v1.position.Y - v3.position.Y * v1.position.X);
	double w2_row = (A12)* p.X + (B12)* p.Y + (v1.position.X * v2.position.Y - v1.position.Y * v2.position.X);

	for (p.Y = minY; p.Y <= maxY; p.Y++) {
		
		double w0 = w0_row, w1 = w1_row, w2 = w2_row;

		for (p.X = minX; p.X <= maxX; p.X++) {
			
			// If p is on or inside all edges, render pixel.
			if (w0 <= 0 && w1 <= 0 && w2 <= 0) {
				FillPixel(p.X, p.Y, RGB(255, 255, 255));
			}

			//One step to the right
			w0 += A23;
			w1 += A31;
			w2 += A12;

		}

		// One row step
		w0_row += B23;
		w1_row += B31;
		w2_row += B12;
	}

	WinDebug.Log(t1.Value());
	t1.Reset();
}

void Graphics::DrawTriangleScanline(const Vertex3& vertex1, const Vertex3& vertex2, const Vertex3& vertex3)
{
	const static COLORREF color = RGB(255, 255, 255);
	
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

	//Split triangle into two horizontal-sided triangles by adding another point
	Vector2<int> v4 ((int)(v1.X + ((float)(v2.Y - v1.Y) / (float)(v3.Y - v1.Y)) * (v3.X - v1.X)), v2.Y);

	//Draw bottom-faced triangle using v1, v2, and v4

	int dxL = (v1.X - v2.X), dyL = (v1.Y - v2.Y);
	int dxR = (v1.X - v4.X), dyR = (v1.Y - v4.Y);
	if (dyL != 0 && dxL != 0) {
		double slopeL;
		bool switchedL;
		double offsetL = 0;
		int thresholdL = 1;
		int incL = (dxL >= 0) ? -1 : 1;
		if (abs(dyL) <= abs(dxL)) {
			if (dxL != 0) {
				slopeL = 2 * abs((double)dyL / dxL);
			}
			else {
				slopeL = 65536;
			}
			switchedL = false;
		}
		else {
			if (dyL != 0) {
				slopeL = 2 * abs((double)dxL / dyL);
			}
			else {
				slopeL = 65536;
			}
			switchedL = true;
		}

		double slopeR;
		bool switchedR;
		double offsetR = 0;
		int thresholdR = 1;
		int incR = (dxR >= 0) ? -1 : 1;
		if (abs(dyR) <= abs(dxR)) {
			if (dxR != 0) {
				slopeR = 2 * abs((double)dyR / dxR);
			}
			else {
				slopeR = 65536;
			}
			switchedR = false;
		}
		else {
			if (dyR != 0) {
				slopeR = 2 * abs((double)dxR / dyR);
			}
			else {
				slopeR = 65536;
			}
			switchedR = true;
		}

		int x = v1.X, y = v1.Y;
		int xR = x, yR = y;
		if (!switchedL) {
			for (int xL = v1.X; xL != (int)v2.X + incL; xL += incL) {
				if (offsetL > thresholdL) {
					thresholdL += 2;

					if (!switchedR) {
						do {
							offsetR += slopeR;
							xR += incR;
							if (slopeR == 0) { break; }

						} while (offsetR < thresholdR);

						thresholdR += 2;
					}
					else {
						offsetR += slopeR;
						if (offsetR > thresholdR) {
							xR += incR;
							thresholdR += 2;
						}
					}

					y++;
				}

				offsetL += slopeL;

				for (int i = xL; i != xR; i -= (abs(xL - xR) / (xL - xR))) {
					FillPixel(i, y, color);
				}
			}
		}
		else {

			for (int xL = v1.X; xL != (int)v2.X + incL; xL += incL) {

				while (offsetL < thresholdL && y != (int)v2.Y) {
					offsetL += slopeL;

					if (!switchedR) {
						do {
							offsetR += slopeR;
							xR += incR;
							if (slopeR == 0) { break; }

						} while (offsetR < thresholdR);

						thresholdR += 2;
					}
					else {
						offsetR += slopeR;
						if (offsetR > thresholdR) {
							xR += incR;
							thresholdR += 2;
						}
					}

					for (int i = xL; i != xR; i -= (abs(xL - xR) / (xL - xR))) {
						FillPixel(i, y, color);
					}

					y++;
				}

				thresholdL += 2;
			}
		}

	}
	



	//Draw top-faced triangle using v3, v4, and v2

	dxR = (v3.X - v4.X), dyR = (v3.Y - v4.Y);
	dxL = (v3.X - v2.X), dyL = (v3.Y - v2.Y);
	if (dyL != 0 && dxL != 0) {
		double slopeL;
		bool switchedL;
		double offsetL = 0;
		int thresholdL = 1;
		int incL = (dxL >= 0) ? -1 : 1;
		if (abs(dyL) <= abs(dxL)) {
			if (dxL != 0) {
				slopeL = 2 * abs((double)dyL / dxL);
			}
			else {
				slopeL = 65536;
			}
			switchedL = false;
		}
		else {
			if (dyL != 0) {
				slopeL = 2 * abs((double)dxL / dyL);
			}
			else {
				slopeL = 65536;
			}
			switchedL = true;
		}

		double slopeR;
		bool switchedR;
		double offsetR = 0;
		int thresholdR = 1;
		int incR = (dxR >= 0) ? -1 : 1;
		if (abs(dyR) <= abs(dxR)) {
			if (dxR != 0) {
				slopeR = 2 * abs((double)dyR / dxR);
			}
			else {
				slopeR = 65536;
			}
			switchedR = false;
		}
		else {
			if (dyR != 0) {
				slopeR = 2 * abs((double)dxR / dyR);
			}
			else {
				slopeR = 65536;
			}
			switchedR = true;
		}

		int x = v3.X, y = v3.Y;
		int xR = x, yR = y;
		if (!switchedL) {
			for (int xL = v3.X; xL != (int)v2.X + incL; xL += incL) {
				if (offsetL > thresholdL) {
					thresholdL += 2;

					if (!switchedR) {
						do {
							offsetR += slopeR;
							xR += incR;
							if (slopeR == 0) { break; }

						} while (offsetR < thresholdR);

						thresholdR += 2;
					}
					else {
						offsetR += slopeR;
						if (offsetR > thresholdR) {
							xR += incR;
							thresholdR += 2;
						}
					}

					y--;
				}

				offsetL += slopeL;

				//FillPixel(xL, y, color);
				//FillPixel(xR, y, color);

				for (int i = xL; i != xR; i -= (abs(xL - xR) / (xL - xR))) {
					FillPixel(i, y, RGB(0, 0, 255));
				}
			}
		}
		else {

			for (int xL = v3.X; xL != (int)v2.X + incL; xL += incL) {

				while (offsetL < thresholdL && y != (int)v2.Y) {
					offsetL += slopeL;

					if (!switchedR) {
						do {
							offsetR += slopeR;
							xR += incR;
							if (slopeR == 0) { break; }

						} while (offsetR < thresholdR);

						thresholdR += 2;
					}
					else {
						offsetR += slopeR;
						if (offsetR > thresholdR) {
							xR += incR;
							thresholdR += 2;
						}
					}

					for (int i = xL; i != xR; i -= (abs(xL - xR) / (xL - xR))) {
						FillPixel(i, y, RGB(0, 0, 255));
					}

					y--;
				}

				thresholdL += 2;

				//FillPixel(xL, y, color);
				//FillPixel(xR, y, color);
			}
		}

	}
}

int Graphics::EdgeFunction(const Vector3<double>& v1, const Vector3<double>& v2, const Vector2<int>& point)
{
	//return (b.x - a.x)*(c.y - a.y) - (b.y - a.y)*(c.x - a.x);
	
	return (v1.Y - v2.Y) * point.X + (v2.X - v1.X) * point.Y + (v1.X * v2.Y - v1.Y * v2.X);

	//return (point.Y - v1.Y) * (v2.X - v1.X) - (point.X - v1.X) * (v2.Y - v1.Y);
}


