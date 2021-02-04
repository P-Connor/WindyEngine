#pragma once
#include "Matrix4.h"
#include "Vertex3.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Transform.h"

enum CameraMode {PERSPECTIVE, ORTHOGRAPHIC};

class Camera {
	
public:
	void WorldToScreen(Vertex3&);
	
	CameraMode GetMode() const;
	void SetMode(const CameraMode&);
	double GetNearP() const;
	void SetNearP(const double&);
	double GetFarP() const;
	void SetFarP(const double&);
	double GetFov() const;
	void SetFov(const double&);

	Transform& GetTransform();

	Matrix4 GetWorldToCamera() const;
	Matrix4 GetProjection() const;
	
	//TODO - Fix default constructor
	Camera() {};
	Camera(const Vector2<int>&);

	// Use after manually updating tranform data
	void UpdViewMatrix();

private:
	void UpdProjection();

	Matrix4 worldToCamera, projectionMatrix;
	double nearP, farP;
	double aspectRatio, fov;
	CameraMode mode;

	Vector2<int> resolution;

	Transform transform;
};