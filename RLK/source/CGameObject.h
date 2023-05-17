#pragma once
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <vector>
#include "CCommon.h"

class CGameObject
{
public:
	typedef enum
	{
		CAR = 1,
		WHEEL = 2,
		BOOST = 3,
		BALL = 4,
		GOAL = 5
	} Type;
	static unsigned int idGlobal;
	unsigned int id;
	unsigned char type;
	CVector2<float> position;
	CVector2<float> offset;
	float angle;
	CGameObject();
	CGameObject(float x, float y);
	CGameObject(float x, float y, const char* spritePath);
	~CGameObject();
	virtual void render(CVector2<float> offset);
	virtual void update(double dt);

private:
	ALLEGRO_BITMAP* sprite;
	void init();
};



