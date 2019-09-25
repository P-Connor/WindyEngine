#include "Matrix4.h"

Matrix4 Matrix4::operator*(const Matrix4& matrix2) const
{
	Matrix4 ret;

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			ret[j][i] = matrix[j][0] * matrix2[0][i]
					  + matrix[j][1] * matrix2[1][i]
					  + matrix[j][2] * matrix2[2][i]
					  + matrix[j][3] * matrix2[3][i];
		}
	}

	return ret;
}

Vector3<double> Matrix4::operator*(const Vector3<double>& vec) const
{
	Vector3<double> ret;
	ret.X = vec.X * matrix[0][0] + vec.Y * matrix[0][1] + vec.Z * matrix[0][2] + matrix[0][3];
	ret.Y = vec.X * matrix[1][0] + vec.Y * matrix[1][1] + vec.Z * matrix[1][2] + matrix[1][3];
	ret.Z = vec.X * matrix[2][0] + vec.Y * matrix[2][1] + vec.Z * matrix[2][2] + matrix[2][3];

	return ret;
}


Matrix4 Matrix4::Identity()
{
	/* {	1, 0, 0, 0 ,
			0, 1, 0, 0 ,
			0, 0, 1, 0 ,
			0, 0, 0, 1   } */
	
	Matrix4 ret;
	ret[0][0] = 1;
	ret[1][1] = 1;
	ret[2][2] = 1;
	ret[3][3] = 1;
	return ret;
}

Matrix4 Matrix4::Translation(const Vector3<double>& vec)
{

	/* {	{ 0, 0, 0, vec.X },
			{ 0, 0, 0, vec.Y },
			{ 0, 0, 0, vec.Z },
			{ 0, 0, 0, 1	 } }; */

	Matrix4 ret;
	ret[0][3] = vec.X;
	ret[1][3] = vec.Y;
	ret[2][3] = vec.Z;
	ret[3][3] = 1;
	return ret;
}

Matrix4 Matrix4::Translation(const double& x, const double& y, const double& z)
{
	/* {	{ 0, 0, 0, x },
			{ 0, 0, 0, y },
			{ 0, 0, 0, z },
			{ 0, 0, 0, 1	 } }; */

	Matrix4 ret;
	ret[0][3] = x;
	ret[1][3] = y;
	ret[2][3] = z;
	ret[3][3] = 1;
	return ret;
}

Matrix4 Matrix4::RotationX(const double& radians)
{
	/* { {	{ 1,	0,				0,				0 },
			{ 0,	cos(radians),	sin(radians),	0 },
			{ 0,	-sin(radians),	cos(radians),	0 },
			{ 0,	0,				0,				1 }} }; */
	
	Matrix4 ret;
	ret[0][0] = 1;
	ret[1][1] = cos(radians);
	ret[1][2] = sin(radians);
	ret[2][1] = -sin(radians);
	ret[2][2] = cos(radians);
	ret[3][3] = 1;
	return ret;
};

Matrix4 Matrix4::RotationY(const double& radians)
{
	/* { {	{ cos(radians),	0,	-sin(radians),	0 },
			{ 0,			1,	0,				0 },
			{ sin(radians), 0,	cos(radians),	0 },
			{ 0,			0,	0,				1 }} }; */
	
	Matrix4 ret;
	ret[0][0] = cos(radians);
	ret[0][2] = -sin(radians);
	ret[1][1] = 1;
	ret[2][0] = sin(radians);
	ret[2][2] = cos(radians);
	ret[3][3] = 1;
	return ret;
}

Matrix4 Matrix4::RotationZ(const double& radians)
{
	
	/* { {	{ cos(radians),		sin(radians),	0, 0 },
			{ -sin(radians),	cos(radians),	0, 0 },
			{ 0,				0,				1, 0 },
			{ 0,				0,				0, 1 }} }; */

	Matrix4 ret;
	ret[0][0] = cos(radians);
	ret[0][1] = sin(radians);
	ret[1][0] = -sin(radians);
	ret[1][1] = cos(radians);
	ret[2][2] = 1;
	ret[3][3] = 1;
	return ret;
}

Matrix4 Matrix4::RotationRad(const Vector3<double>& vec)
{

	Matrix4 ret;
	ret = (RotationX(vec.X) * RotationY(vec.Y)) * RotationZ(vec.Z);

	return ret;
}

Matrix4 Matrix4::RotationRad(const double& x, const double& y, const double& z)
{
	Matrix4 ret;
	ret = (RotationX(x) * RotationY(y)) * RotationZ(z);
	return ret;
}

Matrix4 Matrix4::RotationDeg(const Vector3<double>& vec)
{
	Matrix4 ret;
	ret = (RotationX(vec.X * 0.0174533) * RotationY(vec.Y * 0.0174533)) * RotationZ(vec.Z * 0.0174533);

	return ret;
}

Matrix4 Matrix4::RotationDeg(const double& x, const double& y, const double& z)
{
	Matrix4 ret;
	ret = (RotationX(x * 0.0174533) * RotationY(y * 0.0174533)) * RotationZ(z * 0.0174533);

	return ret;
}

Matrix4 Matrix4::Scale(const Vector3<double>& vec)
{
	/* { {	{ vec.X, 0,	0, 0 },
			{ 0, vec.Y,	0, 0 },
			{ 0, 0, vec.Z, 0 },
			{ 0, 0, 0,	   1 }} }; */

	Matrix4 ret;
	ret[0][0] = vec.X;
	ret[1][1] = vec.Y;
	ret[2][2] = vec.Z;
	ret[3][3] = 1;
	return ret;
}

Matrix4 Matrix4::Scale(const double& X, const double& Y, const double& Z)
{
	
	/* { {	{ X, 0,	0, 0 },
			{ 0, Y,	0, 0 },
			{ 0, 0, Z, 0 },
			{ 0, 0, 0, 1 }} }; */

	Matrix4 ret;
	ret[0][0] = X;
	ret[1][1] = Y;
	ret[2][2] = Z;
	ret[3][3] = 1;
	return ret;
}

Vector3<double> Matrix4::MultiplyHomogeneous(const Vector3<double>& vec) const
{
	Vector3<double> ret;
	ret.X = vec.X * matrix[0][0] + vec.Y * matrix[0][1] + vec.Z * matrix[0][2] + matrix[0][3];
	ret.Y = vec.X * matrix[1][0] + vec.Y * matrix[1][1] + vec.Z * matrix[1][2] + matrix[1][3];
	ret.Z = vec.X * matrix[2][0] + vec.Y * matrix[2][1] + vec.Z * matrix[2][2] + matrix[2][3];
	double W = vec.X * matrix[3][0] + vec.Y * matrix[3][1] + vec.Z * matrix[3][2] + matrix[3][3];

	if (W != 0) {
		ret.X /= W;
		ret.Y /= W;
		//ret.Z /= W;
	}

	return ret;
}
