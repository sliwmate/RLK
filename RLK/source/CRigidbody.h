#pragma once
#include "CGameObject.h"
#include "CCollider.h"
class CRigidbody: public CGameObject
{
public:
	// Public Variables
	CVector2<float> velocity;
	CVector2<float> force;
	float rotVelocity;
	float inertia;
	std::vector<unsigned int> collisionIDs;
	float mass;
	float friction;
	float spring;
	float dumping;
	bool collides;
	bool gravity;
	CCollider* collider;
	// Public Methods
	CRigidbody();
	CRigidbody(float x, float y, const char* spritePath);
	~CRigidbody();
	virtual void update(double dt);
	virtual void render(CVector2<float> offset);
	void collisionExecute(CRigidbody* obj, CVector2<float> contact);
	bool collisionCheck(CRigidbody* obj, CVector2<float>* out);
private:
	// Private Variables
	// Private Methods
};

