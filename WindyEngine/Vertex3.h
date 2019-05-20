#pragma once
#include "Vector3.h"
#include <Windows.h>

class Vertex3 {

public:
	Vertex3();
	Vertex3(const Vector3<double>&, const COLORREF&);
	Vertex3& operator= (const Vertex3&);

	Vector3<double> position;
	COLORREF color;

};