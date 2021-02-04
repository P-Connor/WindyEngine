#pragma once
#include "Component.h"
#include "Vector3.h"
#include "Matrix4.h"

class Transform : Component {
public:
	Transform();

	Vector3<double> position, rotation, scale;

	void Translate(double x, double y, double z);
	void Translate(Vector3<double> vec);

	void TranslateWorld(double x, double y, double z);
	void TranslateWorld(Vector3<double> vec);

	void Rotate (double x, double y, double z);
	void Rotate (Vector3<double> vec);

	void Scale (double x, double y, double z);
	void Scale (Vector3<double> vec);

};