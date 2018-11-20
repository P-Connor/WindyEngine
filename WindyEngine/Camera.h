#pragma once
#include "Matrix4.h"
#include "Vertex3.h"
#include "Vector2.h"
#include "Vector3.h"

class Camera {
	
public:
	void WorldToScreen(Vertex3&);
	void SetFov(const double&);
	
	Camera() {};
	Camera(const Vector2<int>&);

	Matrix4 cameraToWorld, worldToCamera;
	Matrix4 projectionMatrix;

private:
	double nearP, farP;

	double aspectRatio, fov;

	Vector2<int> resolution;
};