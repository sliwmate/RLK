#pragma once
#include <iostream>
#include <fstream>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <iostream>
#include "CGameObject.h"
#include "CRigidbody.h"
#include "CCamera.h"
#include "CCommon.h"
#include "CCar.h"
#include <vector>
class CGameEngine
{
public:
	unsigned short setFPS;
	unsigned short setUPS;
	unsigned int fps;
	unsigned int ups;
	CVector2<int> displaySize;
	CVector2<float> mapSize;
	CGameEngine();
	int init();
	int run();
private:
	long prevTime;
	bool devWindowOn;
	std::vector<CGameObject*> objects;
	std::vector<CRigidbody*> rigidbodies;
	CCamera* camera;
	ALLEGRO_DISPLAY* display;
	ALLEGRO_BITMAP* devWindow;
	ALLEGRO_EVENT_QUEUE* eventQueue;
	ALLEGRO_TIMER* timer;
	ALLEGRO_FONT* font;
	void render();
	CGameObject* addGameObject(float x, float y, unsigned char type);
	CRigidbody* addRigidbody(CVector2<float> pos, CVector2<float> vel, unsigned char type);
	CCar* addCar(CVector2<float> pos, unsigned char type);
	void checkCollisions();
};

