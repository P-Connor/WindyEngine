#pragma once
#include "Matrix4.h"
#include "Vertex3.h"
#include "Vector2.h"
#include "Vector3.h"

enum CameraMode {PERSPECTIVE, ORTHOGRAPHIC};

class Camera {
	
public:
	void WorldToScreen(Vertex3&);
	
	void UpdProjection();
	
	CameraMode GetMode() const;
	void SetMode(const CameraMode&);
	double GetNearP() const;
	void SetNearP(const double&);
	double GetFarP() const;
	void SetFarP(const double&);
	double GetFov() const;
	void SetFov(const double&);
	
	Camera() {};
	Camera(const Vector2<int>&);

	Matrix4 cameraToWorld, worldToCamera;
	Matrix4 projectionMatrix;

private:
	double nearP, farP;

	double aspectRatio, fov;

	CameraMode mode;

	Vector2<int> resolution;
};