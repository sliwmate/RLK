#include "CCar.h"

CCar::CCar(): CRigidbody::CRigidbody()
{
	wheelF = NULL;
	wheelR = NULL;
}

CCar::CCar(float x, float y, const char* spritePath) :
	CRigidbody::CRigidbody(x, y, spritePath)
{
	wheelF = NULL;
	wheelR = NULL;
}

void CCar::update(double dt)
{
	CRigidbody::update(dt);
	//wheelF->position = this->position + CVector2<float>(-200, 100);
	//wheelR->position = this->position + CVector2<float>(200, 100);
}

void CCar::jump()
{
	if (grounded)
	{
		this->velocity.y += 300;
	}
}

void CCar::forwad()
{
	if (grounded)
	{
		this->velocity.x = 500;
	}
}

void CCar::backward()
{
	if (grounded)
	{
		this->velocity.x = -300;
	}
}

void CCar::boost()
{
	this->force.x = -1000;
}
