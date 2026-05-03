#include "Vec2.h"
#include <cmath>


Vec2::Vec2() : x(0), y(0) {}
Vec2::Vec2(float x, float y) : x(x), y(y) {}

Vec2 Vec2::operator+(const Vec2& v) const {
    return Vec2(x + v.x, y + v.y);
}
Vec2 Vec2::operator-(const Vec2 v) const {
    return Vec2(x - v.x, y - v.y);
}
Vec2 Vec2::operator*(const float v) const {
    return Vec2(x * v, y * v);
}

float Vec2::Mag() const {
    return std::sqrt(x * x + y * y);
}

// Dividir os componentes de um vetor pela magnitude dele, obteremos um vetor unitário.
Vec2 Vec2::Normalize() const {
    float mag = Mag();
    if (mag == 0)
        return Vec2(0, 0);

    return Vec2(x / mag, y / mag);
}

// Distância entre dois pontos é equivalente à magnitude da diferença entre dois vetores
float Vec2::Distance(const Vec2& v) const {
    return (*this - v).Mag();
}

float Vec2::InclinationX() const {
    return std::atan2(y, x);
}

// x’ = x * cosθ - y * sinθ
// y’ = y * cosθ + x * sinθ
Vec2 Vec2::InclinationRad(float angle) const {
    return Vec2(x*std::cos(angle) - y*std::sin(angle), y*std::cos(angle) + x*std::sin(angle));
}
