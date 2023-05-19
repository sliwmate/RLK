#pragma once
#include "CCommon.h"
#include <allegro5/allegro_primitives.h>
class CCollider
{
public:
	typedef enum
	{
		POLY = 1,
		ELLIPSE = 2,
		LINE = 3
	} Type;
	unsigned char type;
	CVector2<float> position;
	std::vector<CVector2<float>> points;
	CCollider();
	~CCollider();
	void render(CVector2<float> offset);
	void update(CVector2<float> pos, float angle);
	void addPoint(float x, float y);
	inline void setType(unsigned char type) { this->type = type; }
	static bool pointCircle(CVector2<float>p, CVector2<float> c, float r);
	static bool circleCircle(CVector2<float>c1, float r1, CVector2<float> c2, float r2, CVector2<float>* out);
	static bool linePoint(CVector2<float> a1, CVector2<float> a2, CVector2<float> p);
	static bool lineCircle(CVector2<float> a1, CVector2<float> a2, CVector2<float> c, float r, CVector2<float>* out);

private:
};

