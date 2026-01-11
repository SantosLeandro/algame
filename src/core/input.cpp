#include "input.hpp"

Input& Input::getInstance() {
    static Input instance;
    return instance;
}

Input::Input() {
    m_down.fill(false);
    m_pressed.fill(false);
    m_released.fill(false);
}

void Input::update() {
    m_pressed.fill(false);
    m_released.fill(false);
}

void Input::press(Key key) {
    int i = (int)key;
    if (!m_down[i])
        m_pressed[i] = true;
    m_down[i] = true;
}

void Input::release(Key key) {
    int i = (int)key;
    if (m_down[i])
        m_released[i] = true;
    m_down[i] = false;
}

bool Input::isKeyDown(Key key) const {
    return m_down[(int)key];
}

bool Input::isKeyPressed(Key key) const {
    return m_pressed[(int)key];
}

bool Input::isKeyReleased(Key key) const {
    return m_released[(int)key];
}
