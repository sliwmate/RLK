#pragma once
#include "source/CGameObject.h"
class CCar : public CGameObject
{
public:
	Collider::CCollider* wheelFCollider;
	Collider::CCollider* wheelRCollider;
	CCar();
};

