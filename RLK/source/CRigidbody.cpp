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
	position.x = tempX;
	position.y = tempY;
	collider->update(position, angle);
}

void CRigidbody::render(CVector2<float> offset)
{
	CGameObject::render(offset);
	collider->render(offset);
}

bool CRigidbody::collisionCheck(CRigidbody* obj)
{
	return CCollider::inCollision(*collider, *obj->collider);
}

void CRigidbody::collisionExecute(CRigidbody* obj)
{
	if (this->collider->type == CCollider::Type::ELLIPSE &&
		obj->collider->type == CCollider::Type::ELLIPSE)
	{
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
	}
	if (this->collider->type == CCollider::Type::POLY &&
		obj->collider->type == CCollider::Type::POLY)
	{
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
	}
	if (this->collider->type == CCollider::Type::ELLIPSE &&
		obj->collider->type == CCollider::Type::POLY ||
		this->collider->type == CCollider::Type::POLY &&
		obj->collider->type == CCollider::Type::ELLIPSE)
	{
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
	}
}