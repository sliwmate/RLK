#pragma once
#include <vector>
#include <cmath>
namespace CPhysics
{
	template <typename T> class CVector2
	{
	public:
		T x;
		T y;
		CVector2();
		CVector2(T x, T y);
		inline float abs() { std::sqrtf(x ^ 2 + y ^ 2); };
	};
	template<typename T>
	CPhysics::CVector2<T>::CVector2()
	{
		x = 0;
		y = 0;
	}

	template<typename T>
	CPhysics::CVector2<T>::CVector2(T x, T y)
	{
		this->x = x;
		this->y = y;
	}

	class CCollider
	{
	public:
		CVector2<float> position;
		
	};
};

