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
}
CGameObject::CGameObject(float x, float y, const char* spritePath)
{
	init();
	this->position.x = x;
	this->position.y = y;
	sprite = al_load_bitmap(spritePath);
}
void CGameObject::init()
{
	this->id = idGlobal++;
	sprite = NULL;
	mass = 0;
	gravity = false;
}
CGameObject::~CGameObject()
{
	if (!sprite)
	{
		al_destroy_bitmap(sprite);
	}
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
			
		}
		//al_draw_rectangle(x, y, 50, 50, al_map_rgb(100, 250, 250), 3);
	}
}

Collider::CCollider::CCollider()
{
	object = NULL;
}
