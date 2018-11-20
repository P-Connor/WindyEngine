#pragma once

//TEMPLATE HEADER

template <class T>
class Vector2 {

public:
	Vector2();
	Vector2(T, T);

	Vector2<T>& operator* (const T&) const;
	
	T X, Y;

	void Translate(const T&, const T&);
	void Translate(const Vector2<T>&);
	void Scale(const T&, const T&);
	void Scale(const Vector2<T>&);

	T Magnitude();
	T MagnitudeSquared();
	void Normalize();

	double perpProduct(const Vector2<T>&);
};

//IMPLEMENTATION

template<class T>
Vector2<T>::Vector2()
{
	X = 0;
	Y = 0;
}

template<class T>
Vector2<T>::Vector2(T x, T y)
{
	X = x;
	Y = y;
}

template<class T>
Vector2<T>& Vector2<T>::operator*(const T& scalar) const
{
	Vector2<T> ret;
	ret.X *= scalar;
	ret.Y *= scalar;
	return ret;
}

template <class T>
void Vector2<T>::Translate(const T& x, const T& y) 
{
	X += x;
	Y += y;
}

template<class T>
void Vector2<T>::Translate(const Vector2<T>& vec)
{
	X += vec.X;
	Y += vec.Y;
}

template<class T>
void Vector2<T>::Scale(const T& x, const T& y)
{
	X *= x;
	Y *= y;
}

template<class T>
void Vector2<T>::Scale(const Vector2<T>& vec)
{
	X *= vec.X;
	Y *= vec.Y;
}

template<class T>
T Vector2<T>::Magnitude()
{
	return WindyMath::Sqrt((X * X) + (Y * Y));
}

template<class T>
T Vector2<T>::MagnitudeSquared()
{
	return ((X * X) + (Y * Y));
}

template<class T>
void Vector2<T>::Normalize()
{
	T magnitude = Magnitude();
	if (magnitude != 0) {
		X /= magnitude;
		Y /= magnitude;
	}
}

template<class T>
inline double Vector2<T>::perpProduct(const Vector2<T>& vec)
{
	return X * vec.X - Y * vec.Y;
}

