#ifndef RECT_H
#define RECT_H

#include "Vec2.h"

class Rect {
    public:
        float x, y, w, h;

        Rect();
        Rect(float x, float y, float w, float h);

        bool Contains(Vec2& v) const;
        Vec2 GetCenter() const;
        float DistanceCenters(const Rect& d) const;
        Rect operator+(const Vec2& v) const;
};

#endif