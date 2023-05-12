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
	float getAngle();
	void setAngle(float a);
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
void CVector2<T>::rotate(float a)
{
	this->x = x;
	this->y = y;
}

template<typename T>
float CVector2<T>::getAngle()
{
	float d = abs();
	if (x < 0)
		return -(1.57f + asinf(y / d));
	else if (x > 0 && y < 0)
		return 1.57 + asinf(y / d);
	else if (x >= 0 && y >= 0)
		return 1.57 + acosf(x / d);
	return 0;
}

template<typename T>
void CVector2<T>::setAngle(float a)
{
	float d = abs();
	x = d * cosf(a - 1.57);
	y = d * sinf(a - 1.57);
}

