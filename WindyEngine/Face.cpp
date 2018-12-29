#include "Face.h"

Face::Face()
{
	vertCount = 4;
	triCount = 2;
	vertices = new Vertex3[vertCount];
	triangles = new Vector3<size_t>[triCount];

	vertices[0].position = Vector3<double>(0.5, 0.5, 0);
	vertices[1].position = Vector3<double>(0.5, -0.5, 0);
	vertices[2].position = Vector3<double>(-0.5, 0.5, 0);
	vertices[3].position = Vector3<double>(-0.5, -0.5, 0);

	//Front v
	triangles[0] = Vector3<size_t>(2, 0, 1);
	triangles[1] = Vector3<size_t>(2, 1, 3);

	vertices[0].color = RGB(255, 0, 0);
	vertices[1].color = RGB(0, 255, 0);
	vertices[2].color = RGB(0, 255, 0);
	vertices[3].color = RGB(0, 0, 255);
}
