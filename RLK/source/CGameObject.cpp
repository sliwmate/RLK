#include "CGameObject.h"
unsigned int CGameObject::idGlobal = 1;
CGameObject::CGameObject()
{
	init();
}
CGameObject::CGameObject(float x, float y)
{
	init();
	this->position.x = x;
	this->position.y = y;
	collider = new Collider::CCollider();
}
CGameObject::CGameObject(float x, float y, const char* spritePath)
{
	init();
	this->position.x = x;
	this->position.y = y;
	collider = new Collider::CCollider();
	sprite = al_load_bitmap(spritePath);
}
void CGameObject::init()
{
	this->id = idGlobal++;
	sprite = NULL;
	collider = NULL;
	mass = 0;
	gravity = false;
}
CGameObject::~CGameObject()
{
	if (!sprite)
		al_destroy_bitmap(sprite);
	if(collider)
		delete collider;
}
void CGameObject::update(float dt)
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
	if (tempX < 900 && tempX > 50 && tempY < 600 && tempY > 50)
	{
		position.x = tempX;
		position.y = tempY;
		collider->update(position, 0);
	}
	else force.y = 0;
}

void CGameObject::render(ALLEGRO_BITMAP* canvas)
{
	if (canvas)
	{
		if (sprite)
		{
			al_draw_tinted_scaled_rotated_bitmap(
				sprite,
				al_map_rgba_f(1, 1, 1, 1),
				0, 0,		// center
				(int)this->position.x, (int)this->position.y,		// position
				0.5f, 0.5f,	// scale
				0.0f,		// angle
				0			// flags
			);
			collider->render(canvas);
		}
		//al_draw_rectangle(x, y, 50, 50, al_map_rgb(100, 250, 250), 3);
	}
}

Collider::CCollider::CCollider()
{
	//object = NULL;
}

Collider::CCollider::~CCollider()
{
	points.clear();
}

void Collider::CCollider::render(ALLEGRO_BITMAP* canvas)
{
	for (int i = 0; i < points.size() - 1; i++)
	{
		al_draw_line(
			position.x + points[i].x, position.y + points[i].y,
			position.x + points[i + 1].x, position.y + points[i + 1].y,
			al_map_rgba_f(0, 1, 1, 1), 1);
	}
	al_draw_line(
		position.x + points[0].x, position.y + points[0].y,
		position.x + points[points.size() -1].x, position.y + points[points.size() - 1].y,
		al_map_rgba_f(0, 1, 1, 1), 1);
}

void Collider::CCollider::update(CPhysics::CVector2<float> pos, float angle)
{
	position.x = pos.x;
	position.y = pos.y;
}
