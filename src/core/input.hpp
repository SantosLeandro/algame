#pragma once

#include <array>
#include "key.hpp"

class Input {
public:
    static Input& getInstance();
    void update();

    void press(Key key);
    void release(Key key);

  
    bool isKeyDown(Key key) const;     
    bool isKeyPressed(Key key) const;  
    bool isKeyReleased(Key key) const;

private:
    Input();
    Input(const Input&) = delete;
    Input& operator=(const Input&) = delete;

    std::array<bool, (int)Key::COUNT> m_down;
    std::array<bool, (int)Key::COUNT> m_pressed;
    std::array<bool, (int)Key::COUNT> m_released;
};