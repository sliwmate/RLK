#include "CGameObject.h"
#include <iostream>
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
	angle = 0;
}
CGameObject::~CGameObject()
{
	if (!sprite)
		al_destroy_bitmap(sprite);
}
void CGameObject::update(double dt)
{

}

void CGameObject::render(CVector2<float> offset)
{
	if (sprite)
	{
		al_draw_tinted_scaled_rotated_bitmap(
			sprite,
			al_map_rgba_f(1, 1, 1, 1),
			this->offset.x, this->offset.y,		// center
			this->position.x - offset.x, this->position.y - offset.y,		// position
			1, 1,	// scale
			angle,		// angle
			0			// flags
		);
		al_draw_filled_circle(this->position.x - offset.x, this->position.y - offset.y, 5, al_map_rgba_f(0, 1, 1, 1));
	}
}
