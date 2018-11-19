#include "Camera.h"
#include "WindyMath.h"

Camera::Camera(const Vector2<int>& _resolution)
{
	nearP = 1;
	farP = 10000;

	aspectRatio = 16.0 / 9;
	fov = (75 * (2 * 3.14159265359)) / 360;

	projectionMatrix.matrix = { {	{1 / (aspectRatio * WindyMath::Tan(fov / 2)), 0, 0,	0},
									{0, -1 / WindyMath::Tan(fov / 2), 0, 0},	//INVESTIGATE WHY NEGATIVE
									{0, 0, 1, 0},
									{0, 0, 1, 0}	} };

	resolution = _resolution;

	worldToCamera = Matrix4::Identity();
	cameraToWorld = worldToCamera;
}

Vector2<int> Camera::WorldToScreen(const Vector3<double>& point3D)
{	
	Vector3<double> ret = worldToCamera * point3D;	//Convert to camera coordinate system
	if (ret.Z < 0) {
		return Vector2<int>(-1, -1);
	}
	ret = projectionMatrix.MultiplyHomogeneous(ret);//Project to canvas
	
	//Normalize coordinates (0 to 1)
	double height = WindyMath::Tan(fov / 2), width = height;
	ret.X = (ret.X + (width  / 2)) / width;
	ret.Y = (ret.Y + (height / 2)) / height;

	//Convert to screen coordinates
	ret.X *= resolution.X;
	ret.Y *= resolution.Y;

	return Vector2<int>(ret.X, ret.Y);
}

void Camera::SetFov(const double& deg)
{
	fov = (deg * (2 * 3.14159265359)) / 360;
	projectionMatrix.matrix = { {	{1 / (aspectRatio * WindyMath::Tan(fov / 2)), 0, 0,	0},
									{0, 1 / WindyMath::Tan(fov / 2), 0, 0},
									{0, 0, 1, 0},
									{0, 0, 1, 0}	} };
}
