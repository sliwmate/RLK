#pragma once
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <vector>
#include "CPhysics.h"

namespace Collider
{
	class CCollider
	{
	public:
		CPhysics::CVector2<float> position;
		std::vector<CPhysics::CVector2<float>> points;
		CCollider();
		~CCollider();
		void render(ALLEGRO_BITMAP* canvas);
		void update(CPhysics::CVector2<float> pos, float angle);

	};
}

class CGameObject
{
public:
	static unsigned int idGlobal;
	CPhysics::CVector2<float> position;
	CPhysics::CVector2<float> velocity;
	CPhysics::CVector2<float> force;
	unsigned int mass;
	bool gravity;
	long id;
	Collider::CCollider* collider;
	CGameObject();
	CGameObject(float x, float y);
	CGameObject(float x, float y, const char* spritePath);
	void init();
	~CGameObject();
	void render(ALLEGRO_BITMAP* canvas);
	void update(float dt);

private:
	ALLEGRO_BITMAP* sprite;
};



