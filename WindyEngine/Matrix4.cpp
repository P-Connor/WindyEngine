#include "Matrix4.h"

Matrix4 Matrix4::operator*(const Matrix4& matrix2) const
{
	static Matrix4 ret;

	/*
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			ret[j][i] = matrix[j][0] * matrix2[0][i]
					  + matrix[j][1] * matrix2[1][i]
					  + matrix[j][2] * matrix2[2][i]
					  + matrix[j][3] * matrix2[3][i];
		}
	}
	*/
	ret[0][0] = matrix[0][0] * matrix2.matrix[0][0] + matrix[1][0] * matrix2.matrix[0][1] + matrix[2][0] * matrix2.matrix[0][2] + matrix[3][0] * matrix2.matrix[0][3];
	ret[0][1] = matrix[0][1] * matrix2.matrix[0][0] + matrix[1][1] * matrix2.matrix[0][1] + matrix[2][1] * matrix2.matrix[0][2] + matrix[3][1] * matrix2.matrix[0][3];
	ret[0][2] = matrix[0][2] * matrix2.matrix[0][0] + matrix[1][2] * matrix2.matrix[0][1] + matrix[2][2] * matrix2.matrix[0][2] + matrix[3][2] * matrix2.matrix[0][3];
	ret[0][3] = matrix[0][3] * matrix2.matrix[0][0] + matrix[1][3] * matrix2.matrix[0][1] + matrix[2][3] * matrix2.matrix[0][2] + matrix[3][3] * matrix2.matrix[0][3];
							 
	ret[1][0] = matrix[0][0] * matrix2.matrix[1][0] + matrix[1][0] * matrix2.matrix[1][1] + matrix[2][0] * matrix2.matrix[1][2] + matrix[3][0] * matrix2.matrix[1][3];
	ret[1][1] = matrix[0][1] * matrix2.matrix[1][0] + matrix[1][1] * matrix2.matrix[1][1] + matrix[2][1] * matrix2.matrix[1][2] + matrix[3][1] * matrix2.matrix[1][3];
	ret[1][2] = matrix[0][2] * matrix2.matrix[1][0] + matrix[1][2] * matrix2.matrix[1][1] + matrix[2][2] * matrix2.matrix[1][2] + matrix[3][2] * matrix2.matrix[1][3];
	ret[1][3] = matrix[0][3] * matrix2.matrix[1][0] + matrix[1][3] * matrix2.matrix[1][1] + matrix[2][3] * matrix2.matrix[1][2] + matrix[3][3] * matrix2.matrix[1][3];
							
	ret[2][0] = matrix[0][0] * matrix2.matrix[2][0] + matrix[1][0] * matrix2.matrix[2][1] + matrix[2][0] * matrix2.matrix[2][2] + matrix[3][0] * matrix2.matrix[2][3];
	ret[2][1] = matrix[0][1] * matrix2.matrix[2][0] + matrix[1][1] * matrix2.matrix[2][1] + matrix[2][1] * matrix2.matrix[2][2] + matrix[3][1] * matrix2.matrix[2][3];
	ret[2][2] = matrix[0][2] * matrix2.matrix[2][0] + matrix[1][2] * matrix2.matrix[2][1] + matrix[2][2] * matrix2.matrix[2][2] + matrix[3][2] * matrix2.matrix[2][3];
	ret[2][3] = matrix[0][3] * matrix2.matrix[2][0] + matrix[1][3] * matrix2.matrix[2][1] + matrix[2][3] * matrix2.matrix[2][2] + matrix[3][3] * matrix2.matrix[2][3];

	ret[3][0] = matrix[0][0] * matrix2.matrix[3][0] + matrix[1][0] * matrix2.matrix[3][1] + matrix[2][0] * matrix2.matrix[3][2] + matrix[3][0] * matrix2.matrix[3][3];
	ret[3][1] = matrix[0][1] * matrix2.matrix[3][0] + matrix[1][1] * matrix2.matrix[3][1] + matrix[2][1] * matrix2.matrix[3][2] + matrix[3][1] * matrix2.matrix[3][3];
	ret[3][2] = matrix[0][2] * matrix2.matrix[3][0] + matrix[1][2] * matrix2.matrix[3][1] + matrix[2][2] * matrix2.matrix[3][2] + matrix[3][2] * matrix2.matrix[3][3];
	ret[3][3] = matrix[0][3] * matrix2.matrix[3][0] + matrix[1][3] * matrix2.matrix[3][1] + matrix[2][3] * matrix2.matrix[3][2] + matrix[3][3] * matrix2.matrix[3][3];

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

	/* {	{ 1, 0, 0, vec.X },
			{ 0, 1, 0, vec.Y },
			{ 0, 0, 1, vec.Z },
			{ 0, 0, 0, 1	 } }; */

	Matrix4 ret = Identity();
	ret[0][3] = vec.X;
	ret[1][3] = vec.Y;
	ret[2][3] = vec.Z;
	return ret;
}

Matrix4 Matrix4::Translation(const double& x, const double& y, const double& z)
{
	/* {	{ 1, 0, 0, x },
			{ 0, 1, 0, y },
			{ 0, 0, 1, z },
			{ 0, 0, 0, 1 } }; */

	Matrix4 ret = Identity();
	ret[0][3] = x;
	ret[1][3] = y;
	ret[2][3] = z;
	return ret;
}

Matrix4 Matrix4::RotationX(const double& radians)
{
	/* { {	{ 1,	0,				0,				0 },
			{ 0,	cos(radians),	-sin(radians),	0 },
			{ 0,	sin(radians),	cos(radians),	0 },
			{ 0,	0,				0,				1 }} }; */
	
	Matrix4 ret;
	ret[0][0] = 1;
	ret[1][1] = cos(radians);
	ret[1][2] = -sin(radians);
	ret[2][1] = -ret[1][2];
	ret[2][2] = ret[1][1];
	ret[3][3] = 1;
	return ret;
};

Matrix4 Matrix4::RotationY(const double& radians)
{
	/* { {	{ cos(radians),	0,	sin(radians),	0 },
			{ 0,			1,	0,				0 },
			{ -sin(radians), 0,	cos(radians),	0 },
			{ 0,			0,	0,				1 }} }; */
	
	Matrix4 ret;
	ret[0][0] = cos(radians);
	ret[0][2] = sin(radians);
	ret[1][1] = 1;
	ret[2][0] = -ret[0][2];
	ret[2][2] = ret[0][0];
	ret[3][3] = 1;
	return ret;
}

Matrix4 Matrix4::RotationZ(const double& radians)
{
	
	/* { {	{ cos(radians),		-sin(radians),	0, 0 },
			{ sin(radians),		cos(radians),	0, 0 },
			{ 0,				0,				1, 0 },
			{ 0,				0,				0, 1 }} }; */

	Matrix4 ret;
	ret[0][0] = cos(radians);
	ret[0][1] = -sin(radians);
	ret[1][0] = ret[0][1];
	ret[1][1] = ret[0][0];
	ret[2][2] = 1;
	ret[3][3] = 1;
	return ret;
}

Matrix4 Matrix4::RotationRad(const Vector3<double>& vec)
{
	//Matrix4 ret;
	//ret = (RotationX(vec.X) * RotationY(vec.Y)) * RotationZ(vec.Z);
	return RotationRad(vec.X, vec.Y, vec.Z);
}

Matrix4 Matrix4::RotationRad(const double& x, const double& y, const double& z)
{
	return (RotationY(y) * RotationX(x)) * RotationZ(z);

	/*
	Matrix4 ret;
	//ret = (RotationX(x) * RotationY(y)) * RotationZ(z);
	
	double a = sin(x);
	double b = cos(x);
	double c = sin(y);
	double d = cos(y);
	double e = sin(z);
	double f = cos(z);

	ret[0][0] = f * d;
	ret[0][1] = e * d;
	ret[0][2] = -c;
	ret[1][0] = (f * a * c) - (e * b);
	ret[1][1] = (e * a * c) + (f * b);
	ret[1][2] = a * d;
	ret[2][0] = (f * b * c) + (e * a);
	ret[2][1] = (e * b * c) - (f * a);
	ret[2][2] = b * d;
	ret[3][3] = 1;

	return ret;
	*/
}

Matrix4 Matrix4::RotationDeg(const Vector3<double>& vec)
{
	return RotationRad(vec * WindyMath::RAD_TO_DEG);
}

Matrix4 Matrix4::RotationDeg(const double& x, const double& y, const double& z)
{
	return RotationRad(x * WindyMath::RAD_TO_DEG, y * WindyMath::RAD_TO_DEG, z * WindyMath::RAD_TO_DEG);
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

//Returns the matrix's determinant
double Matrix4::Determinant() {
	
	//Overview: Compute determinant by maniupulating matrix into upper triangular form

	double ret = 1;	//use ret's sign to keep track of swaps

	//Transform first column's values to 0 under first row
	for (int j = 1; j <= 3; j++) {
		if (matrix[j][0] != 0) {	//make sure it's not already 0
			double x = matrix[j][0] / matrix[0][0];
			for (int i = 0; i <= 3; i++) {
				matrix[j][i] -= x * matrix[0][i];
			}
		}
	}

	//Check if number in (row 2, column 2) is 0
	if (matrix[1][1] == 0) {
		//If so, try to swap it with a lower row that doesn't have a 0 in column 2
		int j;
		for (j = 2; j <= 3; j++) {		//search through 2 lower rows to find nonzero value
			if (matrix[j][1] != 0) {
				break;					//j will be at correct row when break hits
			}
		}

		if (j < 4) {	//if a potential swap was found, then swap
			
			ret *= -1;  //swap sign of result
			double temp[4];	
			for (int i = 0; i <= 3; i++) {
				temp[i] = matrix[1][i];			//store row 2 into temp row
			}
			for (int i = 0; i <= 3; i++) {
				matrix[1][i] = matrix[j][i];	//swap row j into row 2
			}
			for (int i = 0; i <= 3; i++) {
				matrix[j][i] = temp[i];			//restore row 2 into row j
			}

		}
		else {			//else the determinant is 0
			return 0;
		}
	}

	//Transform 2nd column's values to 0 under second row
	for (int j = 2; j <= 3; j++) {
		if (matrix[j][1] != 0) {	//make sure it's not already 0
			double x = matrix[j][1] / matrix[1][1];
			for (int i = 1; i <= 3; i++) {
				matrix[j][i] -= x * matrix[1][i];
			}
		}
	}

	//Check if number in (row 3, column 3) is 0
	if (matrix[2][2] == 0) {
		//If so, try to swap it with the bottom row
		if (matrix[3][2] != 0) {
			
			ret *= -1;  //swap sign of result
			double temp[4];
			for (int i = 0; i <= 3; i++) {
				temp[i] = matrix[2][i];			//store row 3 into temp row
			}
			for (int i = 0; i <= 3; i++) {
				matrix[2][i] = matrix[3][i];	//swap row 4 into row 3
			}
			for (int i = 0; i <= 3; i++) {
				matrix[3][i] = temp[i];			//restore row 3 into row 4
			}

		}
		else {	//if the lower row is also 0 in column 3, determinant is 0
			return 0;
		}
	}

	//Transform 3rd column's values to 0 under third row
	if (matrix[3][2] != 0) {	//make sure it's not already 0
		double x = matrix[3][2] / matrix[2][2];
		for (int i = 2; i <= 3; i++) {
			matrix[3][i] -= x * matrix[2][i];
		}
	}

	//finally, compute determinant by finding product of diagonal
	return ret * matrix[0][0] * matrix[1][1] * matrix[2][2] * matrix[3][3];
}

//Will return matrix's inverse once I get around to writing it
//NOTE: FUNCTION NOT COMPLETE, RETURNS THIS OBJECT
Matrix4 Matrix4::Inverse() {
	//TO-DO: Compute inverse
	return *this;
}

Vector3<double> Matrix4::MultiplyHomogeneous(const Vector3<double>& vec) const
{
	Vector3<double> ret = *this * vec;
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
