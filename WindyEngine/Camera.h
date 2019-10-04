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

	void SetPosition(const Vector3<double>&);
	void SetRotation(const Vector3<double>&);
	void SetScale(const Vector3<double>&);

	Matrix4 GetWorldToCamera() const;
	Matrix4 GetProjection() const;
	
	Camera() {};
	Camera(const Vector2<int>&);

private:
	void UpdViewMatrix();
	void UpdProjection();

	Matrix4 worldToCamera, projectionMatrix;
	double nearP, farP;
	double aspectRatio, fov;
	CameraMode mode;

	Vector2<int> resolution;

	Transform transform;
};