#pragma once
#include "Vector3.h"
#include <Windows.h>

struct Vertex3 {
	Vertex3();
	Vertex3(const Vector3<double>&, const COLORREF&);

	Vector3<double> position;
	COLORREF color;
};