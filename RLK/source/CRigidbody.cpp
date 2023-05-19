#include "CRigidbody.h"

CRigidbody::CRigidbody() : CGameObject::CGameObject()
{
	collider = NULL;
	rotVelocity = 0;
	inertia = 0;
	mass = 0;
	gravity = false;
	collider = new CCollider();
	spring = 0;
	dumping = 0;
	collides = false;
	friction = 0;
	dynamic = true;
}

CRigidbody::CRigidbody(float x, float y, const char* spritePath) :
	CGameObject::CGameObject(x, y, spritePath)
{
	collider = NULL;
	rotVelocity = 0;
	inertia = 0;
	mass = 0;
	gravity = false;
	collider = new CCollider();
	spring = 0;
	dumping = 0;
	collides = false;
	friction = 0;
	dynamic = true;
}

CRigidbody::~CRigidbody()
{
	if (collider)
		delete collider;
}

void CRigidbody::update(double dt)
{
	inertia = mass * 1000;
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
	position.x = tempX;
	position.y = tempY;
	angle += rotVelocity * dt;
	collider->update(position, angle);
}

void CRigidbody::render(CVector2<float> offset)
{
	CGameObject::render(offset);
	collider->render(offset);
}

bool CRigidbody::collisionCheck(CRigidbody* obj, CVector2<float>* out)
{
	if (this->collider->type == CCollider::Type::ELLIPSE &&
		obj->collider->type == CCollider::Type::ELLIPSE)
	{
		return CCollider::circleCircle(
			this->collider->position,
			this->collider->points[0].x,
			obj->collider->position,
			obj->collider->points[0].x,
			out);
	}
	if (this->collider->type == CCollider::Type::POLY &&
		obj->collider->type == CCollider::Type::ELLIPSE)
	{
		for (int i = 0; i < this->collider->points.size() - 1; i++)
		{
			if (CCollider::lineCircle(
				this->collider->position + this->collider->points[i],
				this->collider->position + this->collider->points[i + 1],
				obj->collider->position, obj->collider->points[0].x, out))
			{
				return true;
			}
		}
	}
	return false;
}

void CRigidbody::collisionExecute(CRigidbody* obj, CVector2<float> contact)
{
	float friction = 0;
	if (this->friction > 0 && obj->friction > 0) friction = this->friction + obj->friction;
	CVector2<float> rObj2 = obj->position - contact;
	CVector2<float> rObj1 = this->position - contact;
	CVector2<float> vnObj1 = CVector2<float>::dot(this->velocity, rObj2) / (rObj2.abs() * rObj2.abs()) * rObj2;
	CVector2<float> vnObj2 = CVector2<float>::dot(obj->velocity, rObj1) / (rObj1.abs() * rObj1.abs()) * rObj1;
	CVector2<float> vsObj1 = (this->velocity - vnObj1) + ((this->rotVelocity * rObj1.abs()) * (this->velocity - vnObj1).normalize());
	CVector2<float> vsObj2 = (obj->velocity - vnObj2) + ((obj->rotVelocity * rObj2.abs()) * (obj->velocity - vnObj2).normalize());
	CVector2<float> velDifObj1 = (vnObj1 + friction * vsObj1) - (vnObj2 + friction * vsObj2);
	CVector2<float> posDifObj1 = this->position - obj->position;
	double a = CVector2<float>::dot(velDifObj1, posDifObj1) / (posDifObj1.abs() * posDifObj1.abs());
	a = a * ((2 * obj->mass) / (this->mass + obj->mass));
	this->velocity = (vnObj1 + (2 - friction) * vsObj1) - (a * posDifObj1);
	/*
	float dRotVel = 0.5f * friction * (vsObj1 - vsObj2).abs() / rObj1.abs();
	if ((vsObj1.normalize() - (vsObj1 - vsObj2).normalize()).abs() > 0.001f)
	{
		dRotVel = -dRotVel;
	}
	this->rotVelocity += dRotVel;
	*/

	CVector2<float> velDifObj2 = (vnObj2 + vsObj2) - (vnObj1 + vsObj1);
	CVector2<float> posDifObj2 = obj->position - this->position;
	a = CVector2<float>::dot(velDifObj2, posDifObj2) / (posDifObj2.abs() * posDifObj2.abs());
	a = a * ((2 * this->mass) / (obj->mass + this->mass));
	obj->velocity = (vnObj2 + (2 - friction) * vsObj2) - (a * posDifObj2);
	/*
	dRotVel = 0.5f * friction * (vsObj1 - vsObj2).abs() / rObj2.abs();
	if ((vsObj2.normalize() - (vsObj2 - vsObj1).normalize()).abs() > 0.001f)
	{
		dRotVel = -dRotVel;
	}
	obj->rotVelocity += dRotVel;
	*/
	/* Basic elastic collision (old version)
	CVector2<float> velDif = this->velocity - obj->velocity;
	CVector2<float> posDif = this->position - obj->position;
	double a = CVector2<float>::dot(velDif, posDif) / (posDif.abs() * posDif.abs());
	a = a * ((2 * obj->mass) / (this->mass + obj->mass));
	CVector2<float> temp = this->velocity - (a * posDif);
	this->velocity.x = temp.x;
	this->velocity.y = temp.y;

	velDif = obj->velocity - this->velocity;
	posDif = obj->position - this->position;
	a = CVector2<float>::dot(velDif, posDif) / (posDif.abs() * posDif.abs());
	a = a * ((2 * this->mass) / (obj->mass + this->mass));
	temp = obj->velocity - (a * posDif);
	obj->velocity.x = temp.x;
	obj->velocity.y = temp.y;
	*/
}