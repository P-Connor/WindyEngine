#pragma once
#include <cmath>
#include "Vector2.h"

template <class T>
class Vector3 {

public:
	Vector3();
	Vector3(const T&, const T&, const T&);

	Vector3<T>& operator= (const Vector3<T>& vec);

	Vector3<T>& operator* (const T&) const;
	Vector3<T>& operator* (const Vector3<T>&) const;
	Vector3<T>& operator*= (const Vector3<T>&);

	T X, Y, Z;

	Vector2<T>& XY();
	Vector2<T>& YZ();
	Vector2<T>& XZ();

	void Translate(const T&, const T&, const T&);
	void Translate(const Vector3<T>&);
	
	T Magnitude();
	T MagnitudeSquared();
	void Normalize();
};

template<class T>
Vector3<T>::Vector3()
{
	X = 0;
	Y = 0;
	Z = 0;
}

template<class T>
Vector3<T>::Vector3(const T& x, const T& y, const T& z)
{
	X = x;
	Y = y;
	Z = z;
}

template<class T>
Vector3<T>& Vector3<T>::operator= (const Vector3<T>& vec) {
	X = vec.X;
	Y = vec.Y;
	Z = vec.Z;
	return *this;
}

template<class T>
Vector3<T>& Vector3<T>::operator* (const T& scalar) const
{
	Vector3<T> ret;
	ret.X *= scalar;
	ret.Y *= scalar;
	ret.Z *= scalar;
	return ret;
}

template<class T>
Vector3<T>& Vector3<T>::operator*(const Vector3<T>& vec) const
{
	Vector3<T> ret;
	ret.X *= vec.X;
	ret.Y *= vec.Y;
	ret.Z *= vec.Z;
	return ret;
}

template<class T>
Vector3<T>& Vector3<T>::operator*= (const Vector3<T>& vec) {
	X *= vec.X;
	Y *= vec.Y;
	Z *= vec.Z;
	return *this;
}

template<class T>
void Vector3<T>::Translate(const T& x, const T& y, const T& z)
{
	X += x;
	Y += y;
	Z += z;
}

template<class T>
void Vector3<T>::Translate(const Vector3<T>& vec)
{
	X += vec.X;
	Y += vec.Y;
	Z += vec.Z;
}

template<class T>
T Vector3<T>::Magnitude()
{
	return sqrt((X * X) + (Y * Y) + (Z * Z));
}

template<class T>
T Vector3<T>::MagnitudeSquared()
{
	return ((X * X) + (Y * Y) + (Z * Z));
}

template<class T>
void Vector3<T>::Normalize()
{
	T magnitude = Magnitude();
	if (magnitude != 0) {
		X /= magnitude;
		Y /= magnitude;
		Z /= magnitude;
	}
}

template<class T>
Vector2<T>& Vector3<T>::XY()
{
	Vector2<T> ret;
	ret.X = X;
	ret.Y = Y;
	return ret;
}

template<class T>
Vector2<T>& Vector3<T>::YZ()
{
	Vector2<T> ret;
	ret.X = Y;
	ret.Y = Z;
	return ret;
}

template<class T>
Vector2<T>& Vector3<T>::XZ()
{
	Vector2<T> ret;
	ret.X = X;
	ret.Y = Z;
	return ret;
}
