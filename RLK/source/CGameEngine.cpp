#include "CGameEngine.h"
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <chrono>
#include <string>
CGameEngine::CGameEngine ()
{
	display = NULL;
    buffer = NULL;
    devWindow = NULL;
	eventQueue = NULL;
	timer = NULL;
    font = NULL;
    setFPS = 60;
    setUPS = 30;
    fps = 0;
    ups = 0;
    displayWidth = 1024;
    displayHeight = 768;
    prevTime = 0;
    devWindowOn = false;
}
int CGameEngine::init()
{
    try
    {
        if (!al_init()) {
            throw std::exception("Failed to initialize allegro!\n");
        }
        al_init_ttf_addon();
        font = al_load_ttf_font("resources\\fonts\\Roboto-Regular.ttf", 22, 0);
        al_init_image_addon();

        timer = al_create_timer(1.0 / this->setFPS);
        if (!timer) {
            throw std::exception("Failed to create timer!\n");
        }

        if (!al_install_keyboard()) {
            al_destroy_timer(timer);
            throw std::exception("Failed to ínstall keyboard\n");
        }

        if (!al_init_primitives_addon()) {
            al_destroy_timer(timer);
            al_uninstall_keyboard();
            throw std::exception("Failed to init primitives\n");
        }

        display = al_create_display(displayWidth, displayHeight);
        if (!display) {
            al_destroy_timer(timer);
            al_shutdown_primitives_addon();
            al_uninstall_keyboard();
            throw std::exception("Failed to create display!\n");
        }

        buffer = al_create_bitmap(displayWidth, displayHeight);
        if (!buffer) {
            al_destroy_display(display);
            al_destroy_timer(timer);
            al_shutdown_primitives_addon();
            al_uninstall_keyboard();
            throw std::exception("Failed to create buffer!\n");
        }
        devWindow = al_create_bitmap(150, 300);
        if (!devWindow) {
            al_destroy_display(display);
            al_destroy_bitmap(buffer);
            al_destroy_timer(timer);
            al_shutdown_primitives_addon();
            al_uninstall_keyboard();
            throw std::exception("Failed to create devWindow!\n");
        }

        eventQueue = al_create_event_queue();
        if (!eventQueue) {
            al_destroy_display(display);
            al_destroy_bitmap(buffer);
            al_destroy_bitmap(devWindow);
            al_destroy_timer(timer);
            al_shutdown_primitives_addon();
            al_uninstall_keyboard();
            throw std::exception("Failed to create event_queue!\n");
        }
    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << std::endl;
        return 1;
    }

    al_register_event_source(eventQueue, al_get_display_event_source(display));

    al_register_event_source(eventQueue, al_get_keyboard_event_source());

    al_register_event_source(eventQueue, al_get_timer_event_source(timer));

    al_clear_to_color(al_map_rgb(0, 0, 0));

    al_flip_display();
	return 0;
}
int CGameEngine::run()
{
    objects.push_back(new CGameObject(100.0f, 100.0f, "resources\\img\\car.png"));
    objects[objects.size() - 1]->gravity = true;
    objects[objects.size() - 1]->mass = 100.0f;
    objects[objects.size() - 1]->collider->points.push_back(CPhysics::CVector2<float>(0, 50));
    objects[objects.size() - 1]->collider->points.push_back(CPhysics::CVector2<float>(90, 5));
    objects[objects.size() - 1]->collider->points.push_back(CPhysics::CVector2<float>(160, 0));
    objects[objects.size() - 1]->collider->points.push_back(CPhysics::CVector2<float>(200, 30));
    objects[objects.size() - 1]->collider->points.push_back(CPhysics::CVector2<float>(280, 35));
    objects[objects.size() - 1]->collider->points.push_back(CPhysics::CVector2<float>(300, 80));
    objects[objects.size() - 1]->collider->points.push_back(CPhysics::CVector2<float>(0, 80));
    //al_start_timer(timer);
    long frameCnt = 0;
    int frameTimer = 0;
    long updateCnt = 0;
    int updateTimer = 0;
    long prevTime = 0;
    long initTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now()).time_since_epoch()).count();
    int deltaR = 0;
    int deltaU = 0;
    while (true)
    {
        long now = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now()).time_since_epoch()).count();
        int dt = now - initTime;
        initTime = now;
        deltaR += dt;
        deltaU += dt;
        int timeR = (int)(1000.0f / setFPS);
        int timeU = (int)(1000.0f / setUPS);
        if (deltaU >= timeU)
        {
            if (!al_event_queue_is_empty(eventQueue))
            {
                ALLEGRO_EVENT ev;
                al_wait_for_event(eventQueue, &ev);

                if (ev.type == ALLEGRO_EVENT_TIMER) {

                }
                else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
                    break;
                }
                else if ((ev.type == ALLEGRO_EVENT_KEY_DOWN) || (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE))
                {
                    std::cout << ev.keyboard.keycode << std::endl;
                    if (ev.keyboard.keycode == 48)
                        devWindowOn = !devWindowOn;
                    if (ev.keyboard.keycode == 59)
                        break;
                    if (ev.keyboard.keycode == 75)
                        objects[0]->velocity.y = -300;
                }
            }
            for (int i = 0; i < objects.size(); i++)
                objects[i]->update(deltaU / 1000.f);
            updateTimer += deltaU;
            deltaU -= timeU;
            updateCnt++;
        }
        if (updateTimer >= 200)
        {
            ups = updateCnt * 1000.0f / updateTimer;
            updateTimer -= 200;
            updateCnt = 0;
        }
        if (deltaR >= timeR)
        {
                render();
                frameTimer += deltaR;
                while (deltaR >= timeR) deltaR -= timeR;
                frameCnt++;
        }
        if (frameTimer >= 200)
        {
            fps = frameCnt * 1000.0f / frameTimer;
            frameTimer -= 200;
            frameCnt = 0;
        }
    }

    al_destroy_timer(timer);
    al_destroy_display(display);
    al_destroy_event_queue(eventQueue);
    al_shutdown_primitives_addon();
    al_destroy_font(font);
    al_uninstall_keyboard();
    al_destroy_bitmap(buffer);
    al_shutdown_ttf_addon();
    for (int i = 0; i < objects.size(); i++)
        delete objects[i];
    objects.clear();
	return 0;
}

void CGameEngine::render()
{
    al_set_target_bitmap(buffer);
    al_clear_to_color(al_map_rgb(0, 180, 110));
    al_draw_rectangle(10, 20, 50, 50, al_map_rgb(red, 250, 250), 3);
    for (int i = 0; i < objects.size(); i++)
        objects[i]->render(buffer);
    red = (red == 0) ? 250 : 0;
    if (devWindowOn)
    {
        al_set_target_bitmap(devWindow);
        al_clear_to_color(al_map_rgb(0, 0, 0));
        std::string temp_str = "FPS:" + std::to_string(fps) + " UPS:" + std::to_string(ups);
        char const* pchar = temp_str.c_str();
        al_draw_text(font, al_map_rgb(250, 250, 30), 150 - 2, 0, 2, pchar);
    }
    al_set_target_bitmap(al_get_backbuffer(display));
    //al_clear_to_color(al_map_rgb(0, 0, 0));
    al_draw_scaled_rotated_bitmap(buffer, 0, 0, 0, 0, 1.0f, 1.0f, 0.0f, 0);
    if(devWindowOn)
        al_draw_tinted_bitmap(devWindow, al_map_rgba_f(1, 1, 1, 0.5f), displayWidth - 150, 0, 0);
    al_flip_display();
}
