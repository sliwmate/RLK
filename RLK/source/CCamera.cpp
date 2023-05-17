#include "CCamera.h"

CCamera::CCamera()
{
	angle = 0;
	scale = 0.5;
	view = NULL;
	pObjects = NULL;
	pDisplay = NULL;
}

CCamera::CCamera(int sizeX, int sizeY) : CCamera::CCamera()
{
	view = al_create_bitmap(sizeX * 2, sizeY * 2);
    position.x = -300;
    position.y = 0;
}

CCamera::~CCamera()
{
    al_destroy_bitmap(view);
}

void CCamera::update(double dt)
{
}

void CCamera::renderBG()
{
    al_set_target_bitmap(view);
    al_clear_to_color(al_map_rgb(0, 180, 110));
}

void CCamera::renderObjects()
{
	if (*pDisplay)
	{
        for (int i = 0; i < pObjects->size(); i++)
            (*pObjects)[i]->render(position);
        /*
        if (devWindowOn)
        {
            al_set_target_bitmap(devWindow);
            al_clear_to_color(al_map_rgb(0, 0, 0));
            std::string temp_str = "FPS:" + std::to_string(fps) + " UPS:" + std::to_string(ups);
            char const* pchar = temp_str.c_str();
            al_draw_text(font, al_map_rgb(250, 250, 30), 150 - 2, 0, 2, pchar);
        }
        */
        
        //al_clear_to_color(al_map_rgb(0, 0, 0));
        
        //if (devWindowOn)
        //   al_draw_tinted_bitmap(devWindow, al_map_rgba_f(1, 1, 1, 0.5f), displaySize.x - 150, 0, 0);
        
	}
}

void CCamera::renderDeView()
{
}

void CCamera::renderToDisplay()
{
    al_set_target_bitmap(al_get_backbuffer(*pDisplay));
    al_draw_scaled_rotated_bitmap(view, 0, 0, 0, 0, scale, scale, angle, 0);
    al_flip_display();
}
