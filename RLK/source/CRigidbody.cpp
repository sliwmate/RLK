#include "CRigidbody.h"

CRigidbody::CRigidbody() : CGameObject::CGameObject()
{
	collider = NULL;
	mass = 0;
	gravity = false;
	collider = new CCollider();
	spring = 0;
	dumping = 0;
	collides = false;
}

CRigidbody::CRigidbody(float x, float y, const char* spritePath) :
	CGameObject::CGameObject(x, y, spritePath)
{
	collider = NULL;
	mass = 0;
	gravity = false;
	collider = new CCollider();
	spring = 0;
	dumping = 0;
	collides = false;
}

CRigidbody::~CRigidbody()
{
	if (collider)
		delete collider;
}

void CRigidbody::update(double dt)
{
	if (gravity)
	{
		force.x += 0.0f;
		force.y += 20 * mass;
	}
	if (mass > 0)
	{
		velocity.x += force.x / mass * dt;
		velocity.y += force.y / mass * dt;
	}
	float tempX = position.x + velocity.x * dt;
	float tempY = position.y + velocity.y * dt;
	if (tempX < 900 && tempX > 50 && tempY < 1500)
	{
		position.x = tempX;
		position.y = tempY;
		collider->update(position, angle);
	}
	else force.y = 0;
}

void CRigidbody::render(CVector2<float> offset)
{
	CGameObject::render(offset);
	collider->render(offset);
}
