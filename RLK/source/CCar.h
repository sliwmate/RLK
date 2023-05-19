#pragma once
#include "CRigidbody.h"
class CCar : public CRigidbody
{
public:
	CRigidbody* wheelF;
	CRigidbody* wheelR;
	bool grounded;
	CCar();
	CCar(float x, float y, const char* spritePath);
	void update(double dt);
	void jump();
	void forwad();
	void backward();
	void boost();
};

