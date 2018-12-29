#pragma once
#include "Component.h"
#include "Transform.h"
#include "Mesh.h"
#include "Cube.h"
#include "Face.h"
#include <vector>

class GameObject {

public:
	GameObject();
	
	template <class C>
	void AddComponent();

	Transform transform;
	Mesh mesh;

private:
	std::vector<Component> components;

};