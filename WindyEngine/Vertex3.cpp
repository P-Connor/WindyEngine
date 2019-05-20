#include "Vertex3.h"

Vertex3::Vertex3()
{
	position = Vector3<double>();
	color = 0;
}

Vertex3::Vertex3(const Vector3<double>& pos, const COLORREF& col)
{
	position = pos;
	color = col;
}

Vertex3& Vertex3::operator= (const Vertex3& other) {
	position = other.position;
	color = other.color;
	return *this;
}
