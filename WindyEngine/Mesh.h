#pragma once
#include "Component.h"
#include "Vertex.h"
#include "Vector2.h"

class Mesh : Component {

public: 
	Mesh();

//private:
	Vertex vertices[8];
	Vector3<size_t> triangles[12];
};