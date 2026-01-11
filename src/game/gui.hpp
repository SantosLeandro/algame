#pragma once
#include <string>

#include "../core/color.hpp"
#include "../core/graphics.hpp"
#include "../core/vector2.hpp"


struct Font{
    Color color;
    int size;
    ALLEGRO_FONT* allegroFont;
};

class DialogBox {
public:
    DialogBox(const Vector2& pos, const Vector2& size, const std::string& text, Graphics &graphics, const Font &font);
    virtual void render(Graphics &graphics);
    virtual void setText(const std::string& text);
    void update();
    virtual void onOpen() {}
    virtual void onClose() {}
    virtual void onClick() {}
private:
    Vector2 m_pos;
    Vector2 m_size;
    std::string m_text;
    Font m_font;
};

class Button:public DialogBox {
public:
    Button(const Vector2& pos, const Vector2& size, const std::string& text, Graphics &graphics, const Font &font);
    void onClick() override;
private:
    Vector2 m_pos;
    Vector2 m_size;
    std::string m_text;
    Font m_font;
};
