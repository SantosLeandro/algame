#include "algame.hpp"

ALGame::ALGame()
{
    for(int i = 0; i < ALLEGRO_KEY_MAX; i++)
        m_key[i] = 0;
}

ALGame::~ALGame()
{
    al_destroy_font(m_font);
    al_destroy_display(m_disp);
    al_destroy_timer(m_timer);
    al_destroy_event_queue(m_queue);
}

void ALGame::must_init(bool test, const char *description)
{
    if(test) return;

    printf("couldn't initialize %s\n", description);
    exit(1);
}

int ALGame::prepare()
{
    if(!al_init())
    {
        printf("couldn't initialize allegro\n");
        return 1;
    }

    if(!al_install_keyboard())
    {
        printf("couldn't initialize keyboard\n");
        return 1;
    }

    m_timer = al_create_timer(1.0 / 60.0);
    if(!m_timer)
    {
        printf("couldn't initialize timer\n");
        return 1;
    }

    m_queue = al_create_event_queue();
    if(!m_queue)
    {
        printf("couldn't initialize queue\n");
        return 1;
    }

    m_disp = al_create_display(1280, 720);
    if(!m_disp)
    {
        printf("couldn't initialize display\n");
        return 1;
    }

    m_font = al_create_builtin_font();
    if(!m_font)
    {
        printf("couldn't initialize font\n");
        return 1;
    }

    if(!al_init_primitives_addon()){
        printf("couldn't initialize primitives addon\n");
        return 1;
    }

    must_init(al_init_image_addon(), "image addon");

    Joystick::getInstance().initialize();

    al_register_event_source(m_queue, al_get_keyboard_event_source());
    al_register_event_source(m_queue, al_get_display_event_source(m_disp));
    al_register_event_source(m_queue, al_get_timer_event_source(m_timer));
    al_register_event_source(m_queue, al_get_joystick_event_source());
    m_graphics.initialize(m_disp);

    return 0;
}

void ALGame::run()
{
    if(this->prepare() != 0) {
         printf("couldn't initialize ALGame\n");
        return;
    } else {
        printf("ALGame initialized successfully\n");
    }
    this->initialize();
    ALLEGRO_EVENT event;
    al_start_timer(m_timer);
    bool redraw = false;
    m_running = true;
    while(m_running)
    {
        al_wait_for_event(m_queue, &event);
        Joystick::getInstance().update(event);
        switch(event.type)
        {
            case ALLEGRO_EVENT_TIMER:
                update();
                Input::getInstance().update();
                redraw = true;
                break;
            case ALLEGRO_EVENT_KEY_DOWN:
                Input::getInstance().press(mapAllegroKey(event.keyboard.keycode));
                break;
            case ALLEGRO_EVENT_KEY_UP:
                Input::getInstance().release(mapAllegroKey(event.keyboard.keycode));
                break;
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                m_running = false;
                break;
        }
        if(redraw && al_is_event_queue_empty(m_queue))
        {
            render();
            redraw = false;
        }
    }
}

void ALGame::initialize()
{
}

void ALGame::process_input()
{

}

void ALGame::update()
{

}



void ALGame::render()
{
    
}


