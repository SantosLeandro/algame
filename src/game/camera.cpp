#include "camera.hpp"
#include <algorithm>

Camera::Camera()
{
}

Camera::Camera(GameObject *target, int w, int h)
{
    m_target = target;
    m_w = w;
    m_h = h;
    m_smooth = 0.08f;
    m_maxW = 1000;
    m_maxH = 1000;
}

void Camera::setTarget(GameObject *target)
{
    m_target = target;
}

void Camera::setMaxWidth(int w)
{
    m_maxW = w;
}

void Camera::setMaxHeight(int h)
{
    m_maxH = h;
}

void Camera::update()
{
    if (!m_target)
    {
        al_identity_transform(&m_transform);
        al_translate_transform(&m_transform, 0, 0);
        al_use_transform(&m_transform);
        return;
    }

    float targetX = m_target->getPosition().x - (m_w / 2.0f);
    float targetY = m_target->getPosition().y - (m_h / 2.0f);

    m_position.x += (targetX - m_position.x) * m_smooth;
    m_position.y += (targetY - m_position.y) * m_smooth;

    float renderX = floor(m_position.x);
    float renderY = floor(m_position.y);

    renderX = std::max(0.0f, std::min(renderX, static_cast<float>(m_maxW - m_w)));
    renderY = std::max(0.0f, std::min(renderY, static_cast<float>(m_maxH - m_h)));

    al_identity_transform(&m_transform);
    al_translate_transform(&m_transform, -renderX, -renderY);
    al_use_transform(&m_transform);
}