#pragma once
#include <array>
#include "Vector3.h"

class Matrix4 {
public:
	Matrix4();

	std::array<double, 4>& operator[] (unsigned short i) { return matrix[i]; }
	const std::array<double, 4>& operator[] (unsigned short i) const { return matrix[i]; }

	Matrix4 operator* (const Matrix4&) const;
	Vector3<double> operator* (const Vector3<double>&) const;

	static Matrix4 Identity();
	
	static Matrix4 Translation(const Vector3<double>&);
	static Matrix4 Translation(const double&, const double&, const double&);
	static Matrix4 RotationX(const double&);
	static Matrix4 RotationY(const double&);
	static Matrix4 RotationZ(const double&);
	static Matrix4 RotationRad(const Vector3<double>&);
	static Matrix4 RotationRad(const double&, const double&, const double&);
	static Matrix4 RotationDeg(const Vector3<double>&);
	static Matrix4 RotationDeg(const double&, const double&, const double&);
	static Matrix4 Scale(const Vector3<double>&);
	static Matrix4 Scale(const double&, const double&, const double&);

	Vector3<double> MultiplyHomogeneous(const Vector3<double>&) const;

//protected:
	std::array<std::array<double, 4>, 4> matrix;
};