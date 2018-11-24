#include "Camera.h"
#include "WindyMath.h"

Camera::Camera(const Vector2<int>& _resolution)
{
	nearP = 1;
	farP = 10000;

	aspectRatio = 16.0 / 9;
	fov = (75 * (2 * 3.14159265359)) / 360;

	projectionMatrix.matrix = { {	{1 / (aspectRatio * WindyMath::Tan(fov / 2)),	0,								0,	0	},
									{0,												1 / WindyMath::Tan(fov / 2),	0,	0	},
									{0,												0,								1,	1	},
									{0,												0,								1,	0	}	} };

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

void Camera::SetFov(const double& deg)
{
	fov = (deg * (2 * 3.14159265359)) / 360;
	projectionMatrix.matrix = { {	{1 / (aspectRatio * WindyMath::Tan(fov / 2)),	0,								0,	0	},
									{0,												1 / WindyMath::Tan(fov / 2),	0,	0	},
									{0,												0,								1,	1	},
									{0,												0,								1,	0	}	} };
}
