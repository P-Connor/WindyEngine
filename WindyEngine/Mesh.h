#pragma once
#include "Component.h"
#include "Vertex3.h"
#include "Vector2.h"

class Mesh : Component {

public: 
	Mesh();
	~Mesh();

	Mesh(const Mesh&);
	Mesh& operator=(const Mesh&);

//private:
	Vertex3 *vertices;
	Vector3<size_t> *triangles;
	unsigned int vertCount, triCount;
};