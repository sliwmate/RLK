#pragma once
#include <vector>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include "CCommon.h"
#include "CGameObject.h"
class CCamera
{
public:
	float angle;
	float scale;
	CVector2<float> position;
	std::vector<CGameObject*>* pObjects;
	ALLEGRO_BITMAP* view;
	ALLEGRO_DISPLAY** pDisplay;
	CCamera();
	CCamera(int sizeX, int sizeY);
	~CCamera();
	void update(double dt);
	void renderBG();
	void renderObjects();
	void renderDeView();
	void renderToDisplay();
};

