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
	static CVector2<float> getContactPoint(CCollider c1, CCollider c2);
};

