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

	pixelBufferInfo = { 0 };
	pixelBufferInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	pixelBufferInfo.bmiHeader.biWidth = resolution.X;
	pixelBufferInfo.bmiHeader.biHeight = -resolution.Y;
	pixelBufferInfo.bmiHeader.biPlanes = 1;
	pixelBufferInfo.bmiHeader.biBitCount = 32;
	pixelBufferInfo.bmiHeader.biCompression = BI_RGB;
	pixelBufferInfo.bmiHeader.biSizeImage = resolution.X * resolution.Y * 4;
	pixelBufferInfo.bmiHeader.biClrUsed = 0;
	pixelBufferInfo.bmiHeader.biClrImportant = 0;
	pixelBuffer = CreateDIBSection(memoryHDC, &pixelBufferInfo, DIB_RGB_COLORS, (void**)&pixelBufferBytes, NULL, NULL);

	zBufferBytes = new double [resolution.X * resolution.Y];
	std::fill(zBufferBytes, zBufferBytes + (resolution.X * resolution.Y), INFINITY);

	SelectObject(memoryHDC, pixelBuffer);
}

Graphics::~Graphics()
{
	DeleteObject(pixelBuffer);
	delete[] zBufferBytes;
}

const HDC& Graphics::GetMemoryHDC()
{
	return memoryHDC;
}

void Graphics::ClearBuffer() {		
	memset(pixelBufferBytes, 0, pixelBufferInfo.bmiHeader.biSizeImage);
	std::fill(zBufferBytes, zBufferBytes + (resolution.X * resolution.Y), INFINITY);
}

void Graphics::FillPixel(const int& x, const int& y, const COLORREF& color)
{
	if (x < resolution.X && x >= 0 && y < resolution.Y && y >= 0) {
		int index = (y * (4 * resolution.X)) + (4 * x);
		pixelBufferBytes[index + 0] = GetBValue(color);
		pixelBufferBytes[index + 1] = GetGValue(color);
		pixelBufferBytes[index + 2] = GetRValue(color);
	}
}

COLORREF Graphics::GetPixel(const int& x, const int& y)
{
	if (x < resolution.X && x >= 0 && y < resolution.Y && y >= 0) {
		int index = (y * (4 * resolution.X)) + (4 * x);
		
		int bVal = (int)pixelBufferBytes[index + 0];
		int gVal = (int)pixelBufferBytes[index + 1];
		int rVal = (int)pixelBufferBytes[index + 2];
		
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

void Graphics::DrawTriangle(Vertex3 v1, Vertex3 v2, Vertex3 v3)
{
	static Timer t1, rows, pixels;
	t1.Reset();

	if (!isCounterClockwise(v1, v2, v3)) {
		return;
	}
	bool isCC = true;

	if (v1.position.Y > v2.position.Y) {
		std::swap(v1, v2);
		isCC = !isCC;
	}
	if (v1.position.Y > v3.position.Y) {
		std::swap(v1, v3);
		isCC = !isCC;
	}
	if (!isCC) {
		std::swap(v2, v3);
	}

	float A12 = v1.position.Y - v2.position.Y, B12 = v2.position.X - v1.position.X;
	float A23 = v2.position.Y - v3.position.Y, B23 = v3.position.X - v2.position.X;
	float A31 = v3.position.Y - v1.position.Y, B31 = v1.position.X - v3.position.X;

	Vector2<int> p((int)v1.position.X, (int)v1.position.Y);
	float w0 = A23 * p.X + B23 * p.Y + (v2.position.X * v3.position.Y - v2.position.Y * v3.position.X);
	float w1 = A31 * p.X + B31 * p.Y + (v3.position.X * v1.position.Y - v3.position.Y * v1.position.X);
	float w2 = A12 * p.X + B12 * p.Y + (v1.position.X * v2.position.Y - v1.position.Y * v2.position.X);

	//float w0 = w0_row, w1 = w1_row, w2 = w2_row;
	float area = w0 + w1 + w2;;
	float p0, p1, p2;
	float z;
	int incX = (v1.position.X < v2.position.X) ? 1 : -1;
	bool inside = true;

	//WinDebug.Log(std::to_string(t1.Value()) + "\t init");

	for (p.Y = (int)v1.position.Y; (p.Y <= (int)v3.position.Y || p.Y <= (int)v2.position.Y); p.Y++) {
		
		//rows.Reset();

		//Move back to unfillable tile
		while (w0 < 0 && w1 < 0 && w2 < 0) {
			w0 += A23 * incX;
			w1 += A31 * incX;
			w2 += A12 * incX;
			p.X += incX;
		}
		incX *= -1;

		do {
			//pixels.Reset();
			
			//One step to the left/right
			w0 += A23 * incX;
			w1 += A31 * incX;
			w2 += A12 * incX;
			p.X += incX;
			
			// If p is on or inside all edges, render pixel.
			if (w0 < 0 && w1 < 0 && w2 < 0) {
				//WinDebug.Log(std::to_string(pixels.Value()) + "\t check");
				inside = true;
				
				p0 = w0 / area, p1 = w1 / area, p2 = w2 / area;
				z = v1.position.Z * p0 + v2.position.Z * p1 + v3.position.Z * p2;

				//WinDebug.Log(std::to_string(pixels.Value()) + "\t calc");

				//WinDebug.Log(std::to_string((double)w0 / area) + ", " + std::to_string((double)w1 / area) + ", " + std::to_string((double)w2 / area));

				if ((p.Y * resolution.X + p.X) >= 0 && (p.Y * resolution.X + p.X) < (resolution.X * resolution.Y) && zBufferBytes[p.Y * resolution.X + p.X] >= z && z > 0 && z < 1) {
					
					zBufferBytes[p.Y * resolution.X + p.X] = z;
					
					byte r = GetRValue(v1.color) * p0 + GetRValue(v2.color) * p1 + GetRValue(v3.color) * p2;
					byte g = GetGValue(v1.color) * p0 + GetGValue(v2.color) * p1 + GetGValue(v3.color) * p2;
					byte b = GetBValue(v1.color) * p0 + GetBValue(v2.color) * p1 + GetBValue(v3.color) * p2;
					
					FillPixel(p.X, p.Y, RGB(r, g, b));
				}

				//WinDebug.Log(std::to_string(pixels.Value()) + "\t fill");
			}
			else if (inside == true){
				inside = false;
				break;
			}

			//WinDebug.Log(std::to_string(p.X) + "\t X");
			//WinDebug.Log(p.X);

		} while (p.X < resolution.X && p.X > 0);

		// One row step
		w0 += B23;
		w1 += B31;
		w2 += B12;
		//WinDebug.Log(std::to_string(rows.Value()) + "\t row");


	}

	//WinDebug.Log(t1.Value());


	
	/*
	// Compute triangle bounding box
	int minX = WindyMath::Min3(v1.position.X, v2.position.X, v3.position.X);
	int minY = WindyMath::Min3(v1.position.Y, v2.position.Y, v3.position.Y);
	int maxX = WindyMath::Max3(v1.position.X, v2.position.X, v3.position.X);
	int maxY = WindyMath::Max3(v1.position.Y, v2.position.Y, v3.position.Y);

	// Clip against screen bounds
	minX = max(minX, 0);
	minY = max(minY, 0);
	maxX = min(maxX, resolution.X - 1);
	maxY = min(maxY, resolution.Y - 1);

	float A12 = v1.position.Y - v2.position.Y, B12 = v2.position.X - v1.position.X;
	float A23 = v2.position.Y - v3.position.Y, B23 = v3.position.X - v2.position.X;
	float A31 = v3.position.Y - v1.position.Y, B31 = v1.position.X - v3.position.X;

	// Rasterize
	Vector2<int> p(minX, minY);
	float w0_row = (A23)* p.X + (B23)* p.Y + (v2.position.X * v3.position.Y - v2.position.Y * v3.position.X);
	float w1_row = (A31)* p.X + (B31)* p.Y + (v3.position.X * v1.position.Y - v3.position.Y * v1.position.X);
	float w2_row = (A12)* p.X + (B12)* p.Y + (v1.position.X * v2.position.Y - v1.position.Y * v2.position.X);

	float w0, w1, w2;
	float area;
	float p0, p1, p2;
	float z;

	for (p.Y = minY; p.Y <= maxY; p.Y++) {
		
		w0 = w0_row;
		w1 = w1_row;
		w2 = w2_row;

		for (p.X = minX; p.X <= maxX; p.X++) {
			// If p is on or inside all edges, render pixel.
			if (w0 < 0 && w1 < 0 && w2 < 0) {
				area = w0 + w1 + w2;
				p0 = w0 / area, p1 = w1 / area, p2 = w2 / area;
				byte r = GetRValue(v1.color) * p0 + GetRValue(v2.color) * p1 + GetRValue(v3.color) * p2;
				byte g = GetGValue(v1.color) * p0 + GetGValue(v2.color) * p1 + GetGValue(v3.color) * p2;
				byte b = GetBValue(v1.color) * p0 + GetBValue(v2.color) * p1 + GetBValue(v3.color) * p2;

				z = v1.position.Z * p0 + v2.position.Z * p1 + v3.position.Z * p2;

				//WinDebug.Log(std::to_string((double)w0 / area) + ", " + std::to_string((double)w1 / area) + ", " + std::to_string((double)w2 / area));
				
				if (zBufferBytes[p.Y * resolution.X + p.X] >= z && z > 0 && z < 1) {
					zBufferBytes[p.Y * resolution.X + p.X] = z;
					FillPixel(p.X, p.Y, RGB(r, g, b));
				}
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
	*/

	//WinDebug.Log(t1.Value());
	
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

void Graphics::DrawTriangleOutline(const Vertex3& v1, const Vertex3& v2, const Vertex3& v3, COLORREF col)
{
	DrawLine(v1.position.X, v1.position.Y, v2.position.X, v2.position.Y, col);
	DrawLine(v2.position.X, v2.position.Y, v3.position.X, v3.position.Y, col);
	DrawLine(v1.position.X, v1.position.Y, v3.position.X, v3.position.Y, col);

	FillPixel(v1.position.X, v1.position.Y, RGB(255, 0, 255));
	FillPixel(v2.position.X, v2.position.Y, RGB(255, 0, 255));
	FillPixel(v3.position.X, v3.position.Y, RGB(255, 0, 255));
}

bool Graphics::isCounterClockwise(const Vertex3& v1, const Vertex3& v2, const Vertex3& v3)
{
	//compare slopes of vectors v1v2 and v2v3
	return (((v2.position.Y - v1.position.Y)*(v3.position.X - v2.position.X) - (v3.position.Y - v2.position.Y)*(v2.position.X - v1.position.X)) >= 0 ? true : false);
}


