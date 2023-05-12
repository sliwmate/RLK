#pragma once
#include "CRigidbody.h"
class CCar : public CRigidbody
{
public:
	CRigidbody* wheelF;
	CRigidbody* wheelR;
	CCar();
	CCar(float x, float y, const char* spritePath);
};

