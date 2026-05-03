#include "Rect.h"

Rect::Rect() : x(0), y(0), w(0), h(0) {}
Rect::Rect(float x, float y, float w, float h) : x(x), y(y), w(w), h(h) {}


bool Rect::Contains(Vec2& v) const {
    return v.x >= x && v.x <= x + w && v.y >= y && v.y <= y + h;
}

Vec2 Rect::GetCenter() const {
    return Vec2(x + w / 2.0f, y + h / 2.0f);
}

float Rect::DistanceCenters(const Rect& d) const {
    return GetCenter().Distance(d.GetCenter());
}

Rect Rect::operator+(const Vec2& v) const {
    return Rect(x + v.x, y + v.y, w, h);
}
