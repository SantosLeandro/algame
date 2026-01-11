#include "vector2.hpp"

// Construtores
Vector2::Vector2() : x(0), y(0) {}
Vector2::Vector2(float x, float y) : x(x), y(y) {}

// Operadores
Vector2 Vector2::operator+(const Vector2& other) const {
    return Vector2(x + other.x, y + other.y);
}

Vector2 Vector2::operator-(const Vector2& other) const {
    return Vector2(x - other.x, y - other.y);
}

Vector2 Vector2::operator*(float scalar) const {
    return Vector2(x * scalar, y * scalar);
}

Vector2& Vector2::operator+=(const Vector2& other) {
    x += other.x;
    y += other.y;
    return *this;
}

Vector2& Vector2::operator-=(const Vector2& other) {
    x -= other.x;
    y -= other.y;
    return *this;
}

float Vector2::length() const {
    return std::sqrt(x * x + y * y);
}

Vector2 Vector2::normalized() const {
    float len = length();
    return (len == 0) ? Vector2(0, 0) : Vector2(x / len, y / len);
}

void Vector2::normalize() {
    float len = length();
    if(len != 0) {
        x /= len;
        y /= len;
    }
}
