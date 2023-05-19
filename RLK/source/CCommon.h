#pragma once
#include <vector>
#include <cmath>

template <typename T> class CVector2
{
public:
	T x;
	T y;
	CVector2();
	CVector2(T x, T y);
	inline float abs() { return std::sqrtf((float)(x * x + y * y)); };
	void rotate(float a);
	double getAngle();
	void setAngle(double a);
	CVector2<T> normalize();
	static CVector2<T> setVector(float d, double a);
	static double dot(CVector2<T>& a, CVector2<T>& b);
};
template<typename T>
CVector2<T>::CVector2()
{
	x = 0;
	y = 0;
}

template<typename T>
CVector2<T>::CVector2(T x, T y)
{
	this->x = x;
	this->y = y;
}

template<typename T>
CVector2<T>& operator+=(CVector2<T>& a, CVector2<T>& b)
{
	a.x += b.x;
	a.y += b.y;
	return a;
}
template<typename T>
CVector2<T>& operator-(CVector2<T>& a)
{
	a.x = -a.x;
	a.y = -a.y;
	return a;
}

template<typename T>
CVector2<T> operator-(CVector2<T> a, CVector2<T> b)
{
	return CVector2<T>(a.x - b.x, a.y - b.y);
}

template<typename T>
CVector2<T> operator+(CVector2<T> a, CVector2<T> b)
{
	return CVector2<T>(a.x + b.x, a.y + b.y);
}

template<typename T>
CVector2<T> operator*(CVector2<T> a, float b)
{
	return CVector2<T>(a.x * b, a.y * b);
}
template<typename T>
CVector2<T> operator*(float b, CVector2<T> a)
{
	return CVector2<T>(a.x * b, a.y * b);
}

template<typename T>
void CVector2<T>::rotate(float a)
{
	this->x = x;
	this->y = y;
}

template<typename T>
double CVector2<T>::getAngle()
{
	float d = abs();
	if (x < 0)
		return -(1.57 + asin(y / d));
	else if (x > 0 && y < 0)
		return 1.57 + asin(y / d);
	else if (x >= 0 && y >= 0)
		return 1.57 + acos(x / d);
	return 0;
}

template<typename T>
void CVector2<T>::setAngle(double a)
{
	float d = abs();
	x = static_cast<float>(d * cos(a - 1.57));
	y = static_cast<float>(d * sin(a - 1.57));
	return this;
}

template<typename T>
CVector2<T> CVector2<T>::normalize()
{
	float d = abs();
	if (d > 0)
	{
		x = x / d;
		y = y / d;
	}
	else
	{
		x = 0;
		y = 0;
	}
	return *this;
}

template<typename T>
CVector2<T> setVector(float d, double a)
{
	CVector2<T> ret(d, 0);
	ret.setAngle(a);
	return ret;
}

template<typename T>
double CVector2<T>::dot(CVector2<T>& a, CVector2<T>& b)
{
	return a.x * b.x + a.y * b.y;
}
