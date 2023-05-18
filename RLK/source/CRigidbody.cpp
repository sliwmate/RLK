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
	return false;
}

void CRigidbody::collisionExecute(CRigidbody* obj, CVector2<float> contact)
{
	if (this->collider->type == CCollider::Type::ELLIPSE &&
		obj->collider->type == CCollider::Type::ELLIPSE)
	{
		CVector2<float> Br = obj->position - contact;
		CVector2<float> Ar = this->position - contact;
		CVector2<float> Avn = CVector2<float>::dot(this->velocity, Br) / (Br.abs() * Br.abs()) * Br;
		CVector2<float> Bvn = CVector2<float>::dot(obj->velocity, Ar) / (Ar.abs() * Ar.abs()) * Ar;
		CVector2<float> Avs = this->velocity - Avn;
		CVector2<float> Bvs = obj->velocity - Bvn;
		CVector2<float> AvelDif = (Avn/* + Avs*/) - (Bvn/* + Bvs*/);
		CVector2<float> AposDif = this->position - obj->position;
		double a = CVector2<float>::dot(AvelDif, AposDif) / (AposDif.abs() * AposDif.abs());
		a = a * ((2 * obj->mass) / (this->mass + obj->mass));
		CVector2<float> temp = (Avn + (2 - (this->friction + obj->friction)) * 0.5 * Avs) - (a * AposDif);
		this->velocity.x = temp.x;
		this->velocity.y = temp.y;
		this->rotVelocity = (this->friction + obj->friction) * 0.5 * Bvs.abs() / Ar.abs();

		CVector2<float> BvelDif = (Bvn + Bvs) - (Avn + Avs);
		CVector2<float> BposDif = obj->position - this->position;
		a = CVector2<float>::dot(BvelDif, BposDif) / (BposDif.abs() * BposDif.abs());
		a = a * ((2 * this->mass) / (obj->mass + this->mass));
		temp = (Bvn + (2-(this->friction + obj->friction)) * 0.5 * Bvs) - (a * BposDif);
		obj->velocity.x = temp.x;
		obj->velocity.y = temp.y;
		obj->rotVelocity = (this->friction + obj->friction) * 0.5 * Avs.abs() / Br.abs();
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