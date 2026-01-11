#include "gui.hpp"

DialogBox::DialogBox(const Vector2 &pos, const Vector2 &size, const std::string &text, Graphics &graphics, const Font &font)
{
    m_pos = pos;
    m_size = size;
    m_text = text;
    m_font = font;
}

void DialogBox::render(Graphics &graphics)
{
    graphics.drawRectangle(static_cast<int>(m_pos.x), static_cast<int>(m_pos.y),
                           static_cast<int>(m_pos.x + m_size.x), static_cast<int>(m_pos.y + m_size.y),Color{0.2f,0.2f,0.2f,0.7f});
    graphics.drawText(m_text.c_str(), static_cast<int>(m_pos.x + 10), static_cast<int>(m_pos.y + 10));
}

void DialogBox::setText(const std::string &text)
{
    m_text = text;
}

void DialogBox::update()
{
    
}

Button::Button(const Vector2 &pos, const Vector2 &size, const std::string &text, Graphics &graphics, const Font &font)
    : DialogBox(pos, size, text, graphics, font)
{
    m_pos = pos;
    m_size = size;
    m_text = text;
    m_font = font;
}

void Button::onClick()
{
    m_text = "Button Clicked!";
}
