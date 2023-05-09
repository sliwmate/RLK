#pragma once
#include <iostream>
#include <fstream>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <iostream>
#include "CGameObject.h"
#include <vector>
class CGameEngine
{
public:
	unsigned short setFPS;
	unsigned short setUPS;
	unsigned int fps;
	unsigned int ups;
	unsigned short displayWidth;
	unsigned short displayHeight;
	long prevTime;
	CGameEngine();
	int init();
	int run();
private:
	unsigned char red = 250;
	bool devWindowOn;
	std::ofstream logFile;
	ALLEGRO_DISPLAY* display;
	ALLEGRO_BITMAP* buffer;
	ALLEGRO_BITMAP* devWindow;
	ALLEGRO_EVENT_QUEUE* eventQueue;
	ALLEGRO_TIMER* timer;
	ALLEGRO_FONT* font;
	void render();
	bool getFPS(long* cnt);
	std::vector<CGameObject*> objects;
};

