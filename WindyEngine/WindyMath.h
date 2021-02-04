#pragma once
#include <cmath>

namespace WindyMath {

	const double RAD_TO_DEG = 0.0174533;
	const double PI = 3.14159265359;

	template <class T>
	double Sqrt(const T& n) { return sqrt(n); }
	template <class T>
	T Abs(const T& n) { return abs(n); }

	template <class T>
	T Sin(const T& n) { return sin(n); }
	template <class T>
	T Cos(const T& n) { return cos(n); }
	template <class T>
	T Tan(const T& n) { return tan(n); }

	template <class T>
	T Csc(const T& n) {
		T temp = Sin(n);

		if (temp != 0)
			return 1 / temp;
		else
			return NAN;
	}
	template <class T>
	T Sec(const T& n) {
		T temp = Cos(n);

		if (temp != 0)
			return 1 / temp;
		else
			return NAN;
	}
	template <class T>
	T Cot(const T& n) {
		T temp = Tan(n);

		if (temp != 0)
			return 1 / temp;
		else
			return NAN;
	}

	/*
	double Lerp(const double& i, const double& f, double p) {
		return (i + (p * (f - i)));
	}
	*/

	template <class T>
	T Min3(const T& x, const T& y, const T& z) {
		if (x < y) {
			if (x < z) {
				return x;
			}
			else {
				return z;
			}
		}
		else {
			if (y < z) {
				return y;
			}
			else {
				return z;
			}
		}
	}
	template <class T>
	T Max3(const T& x, const T& y, const T& z) {
		if (x > y) {
			if (x > z) {
				return x;
			}
			else {
				return z;
			}
		}
		else {
			if (y > z) {
				return y;
			}
			else {
				return z;
			}
		}
	}



}