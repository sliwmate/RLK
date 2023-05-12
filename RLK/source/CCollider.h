#pragma once
#include "CCommon.h"
#include <allegro5/allegro_primitives.h>
class CCollider
{
public:
	CVector2<float> position;
	std::vector<CVector2<float>> points;
	CCollider();
	~CCollider();
	void render(CVector2<float> offset);
	void update(CVector2<float> pos, float angle);
};

