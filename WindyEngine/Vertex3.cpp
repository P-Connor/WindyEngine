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
