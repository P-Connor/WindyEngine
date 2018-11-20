#pragma once
#include "Component.h"
#include "Vertex3.h"
#include "Vector2.h"

class Mesh : Component {

public: 
	Mesh();

//private:
	Vertex3 vertices[8];
	Vector3<size_t> triangles[12];
};