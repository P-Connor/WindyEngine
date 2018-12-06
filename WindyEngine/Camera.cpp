#include "Camera.h"
#include "WindyMath.h"

Camera::Camera(const Vector2<int>& _resolution)
{
	nearP = 1;
	farP = 1000;

	aspectRatio = 16.0 / 9;
	fov = (75 * (2 * 3.14159265359)) / 360;

	mode = PERSPECTIVE;

	UpdProjection();

	resolution = _resolution;

	worldToCamera = Matrix4::Identity();
	cameraToWorld = worldToCamera;
}

//Returns true if the point is potentially visible
void Camera::WorldToScreen(Vertex3& vert)
{	
	vert.position = worldToCamera * vert.position;	//Convert to camera coordinate system

	vert.position = projectionMatrix.MultiplyHomogeneous(vert.position);//Project to canvas
	
	//Normalize coordinates (0 to 1)
	double size = WindyMath::Tan(fov / 2);
	vert.position.X = (vert.position.X + (size  / 2)) / size;
	vert.position.Y = (vert.position.Y + (size / 2)) / size;

	//Convert to screen coordinates
	vert.position.X *= resolution.X;
	vert.position.Y = resolution.Y - (resolution.Y * vert.position.Y); //Flip on y axis for top to bottom Y coords
}

void Camera::UpdProjection()
{
	switch (mode) {
	
	case PERSPECTIVE:
		projectionMatrix.matrix = { {	{1 / (aspectRatio * WindyMath::Tan(fov / 2)),	0,								0,	0					},
										{0,												1 / WindyMath::Tan(fov / 2),	0,	0					},
										{0,												0,								1 / (farP - nearP),	-nearP / (farP - nearP)	},
										{0,												0,								1,	0					}	} };
		break;
	
	case ORTHOGRAPHIC:
		projectionMatrix.matrix = { {	{1 / (aspectRatio * WindyMath::Tan(fov / 2)),	0,								0,	0					},
										{0,												1 / WindyMath::Tan(fov / 2),	0,	0					},
										{0,												0,								1,	0	},
										{0,												0,								0,	1	}				} };
		break;	
	}

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
	fov = (deg * (2 * 3.14159265359)) / 360;
	UpdProjection();
}
