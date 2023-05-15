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
    devWindow = NULL;
	eventQueue = NULL;
	timer = NULL;
    font = NULL;
    setFPS = 60;
    setUPS = 30;
    fps = 0;
    ups = 0;
    displaySize.x = 1024;
    displaySize.y = 768;
    mapSize.x = 3000;
    mapSize.y = 2000;
    prevTime = 0;
    devWindowOn = false;
    camera = NULL;
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

        display = al_create_display(displaySize.x, displaySize.y);
        if (!display) {
            al_destroy_timer(timer);
            al_shutdown_primitives_addon();
            al_uninstall_keyboard();
            throw std::exception("Failed to create display!\n");
        }

        devWindow = al_create_bitmap(150, 300);
        if (!devWindow) {
            al_destroy_display(display);
            al_destroy_timer(timer);
            al_shutdown_primitives_addon();
            al_uninstall_keyboard();
            throw std::exception("Failed to create devWindow!\n");
        }

        eventQueue = al_create_event_queue();
        if (!eventQueue) {
            al_destroy_display(display);
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

    camera = new CCamera(displaySize.x, displaySize.y);
    camera->pDisplay = &display;
    camera->pObjects = &objects;

    al_register_event_source(eventQueue, al_get_display_event_source(display));

    al_register_event_source(eventQueue, al_get_keyboard_event_source());

    al_register_event_source(eventQueue, al_get_timer_event_source(timer));

    al_clear_to_color(al_map_rgb(0, 0, 0));

    al_flip_display();
	return 0;
}
int CGameEngine::run()
{    
    addGameObject(500, 200, CGameObject::Type::CAR);
    addGameObject(400, 200, CGameObject::Type::BALL);
    addGameObject(1000, 1300, CGameObject::Type::BALL);
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
                        //objects[0]->velocity.y = -300;
                    if (ev.keyboard.keycode == 83)
                        objects[0]->angle += 0.1f;
                    if (ev.keyboard.keycode == 82)
                        objects[0]->angle -= 0.1f;
                }
            }
            checkCollisions();
            for (int i = 0; i < objects.size(); i++)
                objects[i]->update((double)(deltaU / 1000.0));
            camera->update((double)(deltaU / 1000.0));
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
    al_shutdown_ttf_addon();
    for (int i = 0; i < objects.size(); i++)
        delete objects[i];
    objects.clear();
    rigidbodies.clear();
    delete camera;
	return 0;
}

void CGameEngine::render()
{
    camera->renderBG();
    camera->renderObjects();
    if (devWindowOn)
        camera->renderDeView();
    camera->renderToDisplay();
}

void CGameEngine::addGameObject(float x, float y, unsigned char type)
{
    CRigidbody* tempRigidbody = NULL;
    CGameObject* tempGameObject = NULL;
    switch (type)
    {
    case CGameObject::Type::CAR:
        tempRigidbody = new CRigidbody(x, y, "resources\\img\\car.png");
        tempRigidbody->gravity = true;
        tempRigidbody->mass = 100;
        tempRigidbody->collides = true;
        tempRigidbody->spring = 1;
        tempRigidbody->dumping = 1;
        tempRigidbody->offset.x = 300;
        tempRigidbody->offset.y = 300;
        tempRigidbody->collider->setType(CCollider::Type::POLY);
        objects.push_back(tempRigidbody);
        rigidbodies.push_back(tempRigidbody);
        /*objects[objects.size() - 1]->collider->points.push_back(CPhysics::CVector2<float>(0, 50));
        objects[objects.size() - 1]->collider->points.push_back(CPhysics::CVector2<float>(90, 5));
        objects[objects.size() - 1]->collider->points.push_back(CPhysics::CVector2<float>(160, 0));
        objects[objects.size() - 1]->collider->points.push_back(CPhysics::CVector2<float>(200, 30));
        objects[objects.size() - 1]->collider->points.push_back(CPhysics::CVector2<float>(280, 35));
        objects[objects.size() - 1]->collider->points.push_back(CPhysics::CVector2<float>(300, 80));
        objects[objects.size() - 1]->collider->points.push_back(CPhysics::CVector2<float>(0, 80));
        */
        break;
    case CGameObject::Type::BALL:
        tempRigidbody = new CRigidbody(x, y, "resources\\img\\ball.png");
        tempRigidbody->gravity = true;
        tempRigidbody->mass = 10;
        tempRigidbody->collides = true;
        tempRigidbody->spring = 2;
        tempRigidbody->dumping = 1;
        tempRigidbody->offset.x = 100;
        tempRigidbody->offset.y = 100;
        if (x > 900) tempRigidbody->velocity = CVector2<float>(-300, -700);
        tempRigidbody->collider->setType(CCollider::Type::ELLIPSE);
        tempRigidbody->collider->addPoint(100, 100);
        objects.push_back(tempRigidbody);
        rigidbodies.push_back(tempRigidbody);
        //dynamic_cast<CRigidbody*>(objects[0])->update(1);
        /*
        objects.push_back(new CGameObject(400.0f, 100.0f));
        objects[objects.size() - 1]->collider->points.push_back(CPhysics::CVector2<float>(40, 40));
        objects[objects.size() - 1]->gravity = true;
        objects[objects.size() - 1]->mass = 50;

        objects.push_back(new CGameObject(400.0f, 300.0f));
        objects[objects.size() - 1]->collider->points.push_back(CPhysics::CVector2<float>(0, 0));
        objects[objects.size() - 1]->collider->points.push_back(CPhysics::CVector2<float>(100, 0));
        */
        break;
    }
}

void CGameEngine::checkCollisions()
{
    for (int i = 0; i < rigidbodies.size() - 1; i++)
    {
        if (rigidbodies[i]->collides)
        {
            for (int j = i + 1; j < rigidbodies.size(); j++)
            {
                rigidbodies[i]->checkCollision(rigidbodies[j]);
            }
        }
    }
}
