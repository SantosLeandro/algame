#include "joystick.hpp"
#include <stdio.h>

Joystick &Joystick::getInstance()
{
    static Joystick instance;
    return instance;
}

Joystick::Joystick()
{
    m_buttons.fill(false);
    m_axes.fill(0.0f);
    m_connected = false;
}

void Joystick::initialize()
{
    al_install_joystick();
    reset();
    m_connected = al_get_num_joysticks() > 0;
}

void Joystick::reset()
{
    m_buttons.fill(false);
    m_axes.fill(0.0f); 
}

void Joystick::update(ALLEGRO_EVENT &event)
{
    switch (event.type)
    {
    case ALLEGRO_EVENT_JOYSTICK_BUTTON_DOWN:
        m_buttons[(int)mapButton(event.joystick.button)] = true;
        break;

    case ALLEGRO_EVENT_JOYSTICK_BUTTON_UP:
        m_buttons[(int)mapButton(event.joystick.button)] = false;
        break;

    case ALLEGRO_EVENT_JOYSTICK_AXIS:
        mapAxis(event.joystick.stick, event.joystick.axis, event.joystick.pos);
        mapDpad(event.joystick.stick, event.joystick.axis, event.joystick.pos);
        break;

    case ALLEGRO_EVENT_JOYSTICK_CONFIGURATION:
        al_reconfigure_joysticks();
        m_connected = al_get_num_joysticks() > 0;
        break;
    }
}

void Joystick::press(JoystickButton button)
{
}

void Joystick::release(JoystickButton button)
{
}

bool Joystick::isButtonDown(JoystickButton button) const
{
    return m_buttons[(int)button];
}

bool Joystick::isButtonPressed(JoystickButton button) const
{
    return false;
}

bool Joystick::isButtonReleased(JoystickButton button) const
{
    return false;
}

JoystickButton Joystick::mapButton(int allegroButton)
{
    return JoystickButton();
}

void Joystick::mapAxis(int stick, int axis, int pos)
{
    if (stick == 0)
    {
        if (axis == 0)
            m_axes[(int)JoyAxis::LX] = pos;
        if (axis == 1)
            m_axes[(int)JoyAxis::LY] = pos;
    }
    if (stick == 1)
    {
        if (axis == 0)
            m_axes[(int)JoyAxis::RX] = pos;
        if (axis == 1)
            m_axes[(int)JoyAxis::RY] = pos;
        if (axis == 2)
            m_axes[(int)JoyAxis::LT] = pos;
        if (axis == 3)
            m_axes[(int)JoyAxis::RT] = pos;
    }
}

void Joystick::mapDpad(int stick, int axis, int value)
{
    printf("Mapping D-Pad: stick=%d, axis=%d, value=%d\n", stick, axis, value);
    if (stick == 3) {
    if (axis == 0) {
        m_buttons[(int)JoystickButton::DPAD_LEFT]  = (value < -0.5f);
        m_buttons[(int)JoystickButton::DPAD_RIGHT] = (value >  0.5f);
    }
    if (axis == 1) {
        m_buttons[(int)JoystickButton::DPAD_UP]    = (value < -0.5f);
        m_buttons[(int)JoystickButton::DPAD_DOWN]  = (value >  0.5f);
    }
}
}
