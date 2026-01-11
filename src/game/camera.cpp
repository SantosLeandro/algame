#include "camera.hpp"

Camera::Camera()
{
}

Camera::Camera(GameObject *target, int w, int h)
{
    m_target = target;
    m_w = w;
    m_h = h;
    m_smooth = 0.08f;
}

void Camera::update()
{
    if (!m_target) return;

    // posição desejada (centralizar no player)
    float targetX = m_target->getPosition().x - (m_w / 2.0f);
    float targetY = m_target->getPosition().y - (m_h / 2.0f);

    // LERP (suavização)
    m_position.x += (targetX - m_position.x) * m_smooth;
    m_position.y += (targetY - m_position.y) * m_smooth;

     // 🔥 CORREÇÃO CRÍTICA: snap para pixel inteiro
    float renderX = floor(m_position.x);
    float renderY = floor(m_position.y);

    al_identity_transform(&m_transform);
    al_translate_transform(&m_transform, -renderX, -renderY);
    al_use_transform(&m_transform);
}