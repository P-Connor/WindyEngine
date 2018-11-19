#pragma once
#include "Component.h"
#include "Vector3.h"

class Transform : Component {
public:
	Transform();

	Vector3<double> position, rotation, scale;

};