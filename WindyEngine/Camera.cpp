#include "Camera.h"
#include "WindyMath.h"

Camera::Camera(const Vector2<int>& _resolution)
{
	nearP = 1;
	farP = 1000;

	aspectRatio = 16.0 / 9;
	fov = (75 * (2 * WindyMath::PI)) / 360;

	mode = PERSPECTIVE;

	UpdProjection();

	resolution = _resolution;

	transform.position = Vector3<double>(5, 0, 0);
	transform.rotation = Vector3<double>(0, 0, 0);
	transform.scale = Vector3<double>(1, 1, 1);

	worldToCamera = Matrix4::Identity();
}

//Returns true if the point is potentially visible?
void Camera::WorldToScreen(Vertex3& vert)
{	
	//vert.position = worldToCamera * vert.position;	//Convert to camera coordinate system
	vert.position -= transform.position;
	vert.position = Matrix4::RotationDeg(transform.rotation) * vert.position;

	vert.position = projectionMatrix.MultiplyHomogeneous(vert.position);//Project to canvas
	
	//Normalize coordinates (0 to 1)
	double size = WindyMath::Tan(fov / 2);
	vert.position.X = (vert.position.X + (size  / 2)) / size;
	vert.position.Y = (vert.position.Y + (size / 2)) / size;

	//Convert to screen coordinates
	vert.position.X *= resolution.X;
	vert.position.Y = resolution.Y - (resolution.Y * vert.position.Y); //Flip on y axis for top to bottom Y coords
}


CameraMode Camera::GetMode() const { return mode; }

void Camera::SetMode(const CameraMode& _mode)
{
	mode = _mode;
	UpdProjection();
}

double Camera::GetNearP() const { return nearP; }

void Camera::SetNearP(const double& _nearP)
{
	nearP = _nearP;
	UpdProjection();
}

double Camera::GetFarP() const { return farP; }

void Camera::SetFarP(const double& _farP)
{
	farP = _farP;
	UpdProjection();
}

double Camera::GetFov() const { return fov; }

void Camera::SetFov(const double& deg)
{
	fov = (deg * (2 * WindyMath::PI)) / 360;
	UpdProjection();
}

Transform& Camera::GetTransform() {
	return transform;
}

Matrix4 Camera::GetWorldToCamera() const
{
	return worldToCamera;
}

Matrix4 Camera::GetProjection() const
{
	return projectionMatrix;
}

void Camera::UpdViewMatrix()
{
	worldToCamera = Matrix4::RotationDeg(transform.rotation);
	//worldToCamera = Matrix4::Scale(transform.scale) * worldToCamera;
	worldToCamera = Matrix4::Translation(transform.position) * worldToCamera;
}

void Camera::UpdProjection()
{
	switch (mode) {

	case PERSPECTIVE:
		/* { {	{1 / (aspectRatio * WindyMath::Tan(fov / 2)),	0,								0,					0						},
				{0,												1 / WindyMath::Tan(fov / 2),	0,					0						},
				{0,												0,								-1 / (farP - nearP),	-nearP / (farP - nearP)	},
				{0,												0,								-1,					0						}	} }; */

		projectionMatrix = Matrix4();
		projectionMatrix[0][0] = 1 / (aspectRatio * WindyMath::Tan(fov / 2));
		projectionMatrix[1][1] = 1 / WindyMath::Tan(fov / 2);
		projectionMatrix[2][2] = -1 / (farP - nearP);
		projectionMatrix[2][3] = -nearP / (farP - nearP);
		projectionMatrix[3][2] = -1;

		break;

	case ORTHOGRAPHIC:
		/* { {	{1 / (aspectRatio * WindyMath::Tan(fov / 2)),	0,								0,	0	},
				{0,												1 / WindyMath::Tan(fov / 2),	0,	0	},
				{0,												0,								1,	0	},
				{0,												0,								0,	1	}	} }; */

		projectionMatrix = Matrix4();
		projectionMatrix[0][0] = 1 / (aspectRatio * WindyMath::Tan(fov / 2));
		projectionMatrix[1][1] = 1 / WindyMath::Tan(fov / 2);
		projectionMatrix[2][2] = 1;
		projectionMatrix[3][3] = 1;

		break;
	}

}