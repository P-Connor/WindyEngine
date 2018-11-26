#include "Cube.h"

Cube::Cube()
{
	vertices[0].position = Vector3<double>(0.5, 0.5, 0.5);
	vertices[1].position = Vector3<double>(0.5, 0.5, -0.5);
	vertices[2].position = Vector3<double>(0.5, -0.5, 0.5);
	vertices[3].position = Vector3<double>(0.5, -0.5, -0.5);
	vertices[4].position = Vector3<double>(-0.5, 0.5, 0.5);
	vertices[5].position = Vector3<double>(-0.5, 0.5, -0.5);
	vertices[6].position = Vector3<double>(-0.5, -0.5, 0.5);
	vertices[7].position = Vector3<double>(-0.5, -0.5, -0.5);

	//RIGHT v
	triangles[0] = Vector3<size_t>(0,1,2);
	triangles[1] = Vector3<size_t>(3,2,1);
	//Left v
	triangles[2] = Vector3<size_t>(4,6,5);
	triangles[3] = Vector3<size_t>(7,5,6);
	//Front v
	triangles[4] = Vector3<size_t>(1,5,3);
	triangles[5] = Vector3<size_t>(7,3,5);
	//Back v
	triangles[6] = Vector3<size_t>(0,2,4);
	triangles[7] = Vector3<size_t>(6,4,2);
	//Top v
	triangles[8] = Vector3<size_t>(0,4,1);
	triangles[9] = Vector3<size_t>(5,1,4);
	//Bottom v
	triangles[10] = Vector3<size_t>(7,6,3);
	triangles[11] = Vector3<size_t>(2,3,6);

	vertices[0].color = RGB(255, 0, 0);
	vertices[1].color = RGB(0, 255, 0);
	vertices[2].color = RGB(0, 255, 0);
	vertices[3].color = RGB(0, 0, 255);
	vertices[4].color = RGB(255, 255, 255);
	vertices[5].color = RGB(255, 255, 255);
	vertices[6].color = RGB(255, 255, 255);
	vertices[7].color = RGB(255, 255, 255);
}
