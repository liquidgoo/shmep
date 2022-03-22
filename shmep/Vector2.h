#pragma once
#include <math.h>
const float  PI = 3.14159265358979f;
class Vector2
{
public:
    float x;
    float y;
    Vector2 operator+(const Vector2 other) const;
    Vector2 operator-(const Vector2 other) const;
    Vector2 operator*(const float multiplier) const;
    float operator*(const Vector2 other) const;
    Vector2 operator/(const float devisor) const;
    Vector2 operator+=(const Vector2 other);
    Vector2 operator-=(const Vector2 other);
    Vector2 operator*=(const float multiplier);
    Vector2 operator/=(const float divisor);
    float abs();
    Vector2 norm();
    Vector2 rotate(float angle);
    float getAngle();
    Vector2 operator-()const;
    Vector2(float x, float y);
    Vector2();
};

