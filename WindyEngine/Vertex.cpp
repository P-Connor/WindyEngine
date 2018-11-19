#include "Vertex.h"

Vertex::Vertex()
{
	position = Vector3<double>();
	color = 0;
}

Vertex::Vertex(const Vector3<double>& pos, const COLORREF& col)
{
	position = pos;
	color = col;
}
