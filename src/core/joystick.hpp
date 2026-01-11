#pragma once
#include <array>
#include <allegro5/allegro5.h>

enum class JoystickButton
{
    NONE = 0,
    BUTTON_1,
    BUTTON_2,
    BUTTON_3,
    BUTTON_4,
    BUTTON_5,
    BUTTON_6,
    BUTTON_7,
    BUTTON_8,
    BUTTON_9,
    BUTTON_10,

    DPAD_UP,
    DPAD_DOWN,
    DPAD_LEFT,
    DPAD_RIGHT,

    COUNT
};

enum class JoyAxis {
    LX,
    LY,
    RX,
    RY,
    LT,
    RT,
    COUNT
};

class Joystick
{
public:
    static Joystick &getInstance();

    void initialize();
    void update(ALLEGRO_EVENT &event);

    void press(JoystickButton button);
    void release(JoystickButton button);

    bool isButtonDown(JoystickButton button) const;
    bool isButtonPressed(JoystickButton button) const;
    bool isButtonReleased(JoystickButton button) const;

    float getAxis(JoyAxis axis) const { return m_axes[(int)axis]; }

    void reset();

    JoystickButton mapButton(int allegroButton);
    void mapAxis(int stick, int axis, int pos);
    void mapDpad(int stick, int axis, int pos);

private:
    Joystick();
    Joystick(const Joystick &) = delete;
    Joystick &operator=(const Joystick &) = delete;

    std::array<bool, (int)JoystickButton::COUNT> m_buttons;
    std::array<float, 6> m_axes;
    bool m_connected;
};

