#include "Vector2.h"


Vector2 Vector2::operator+(const Vector2 other) const
{
    return Vector2(x + other.x, y + other.y);
}

Vector2 Vector2::operator-(const Vector2 other) const
{
    return Vector2(x - other.x, y - other.y);
}

Vector2 Vector2::operator*(const float multiplier) const
{
    return Vector2(x * multiplier, y * multiplier);
}

float Vector2::operator*(const Vector2 other) const
{
    return x * other.x + y * other.y;
}

Vector2 Vector2::operator/(const float devisor) const
{
    return Vector2(x / devisor, y / devisor);
}

Vector2 Vector2::operator+=(const Vector2 other)
{
    *this = (*this) + other;
    return *this;
}

Vector2 Vector2::operator-=(const Vector2 other)
{
    *this = (*this) - other;
    return *this;
}

Vector2 Vector2::operator*=(const float multiplier)
{
    *this = (*this) * multiplier;
    return *this;
}

Vector2 Vector2::operator/=(const float divisor)
{
    *this = (*this) / divisor;
    return *this;
}

float Vector2::abs()
{
    return sqrtf(*this * (*this));
}

Vector2 Vector2::norm()
{
   return (*this) / this->abs();
}

Vector2 Vector2::rotate(float angle)
{
    Vector2 newVector;
    newVector.x = cos(angle) * x - sin(angle) * y;
    newVector.y = sin(angle) * x + cos(angle) * y;
    return newVector;
}

float Vector2::getAngle()
{
    float angle = acosf(this->norm().x);
    return y > 0 ? angle : (2 * PI -angle);
}

Vector2 Vector2::operator-() const
{
    return Vector2() - *this;
}

Vector2::Vector2(float x, float y)
{
    this->x = x;
    this->y = y;
}

Vector2::Vector2() :Vector2(0,0)
{
}
