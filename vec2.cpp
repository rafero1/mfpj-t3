#include "vec2.h"

#include <math.h>
#include "util.h"

// Output
std::ostream& operator<<(std::ostream& os, const Vec2& v)
{
    os << "(" << v.x << ", " << v.y << ")";
    return os;
}

// Input
std::istream& operator>>(std::istream& is, Vec2& v)
{
    //char chars[] = "1234567890";
    //std::string input;
    is >> v.x >> v.y;
    return is;
}

// Soma
Vec2 Vec2::operator+(const Vec2& v) const
{
    return Vec2(x + v.x, y + v.y);
}

// Subtração
Vec2 Vec2::operator-(const Vec2& v) const
{
    return Vec2(x - v.x, y - v.y);
}

// Produto por escalar
Vec2 Vec2::operator*(real n) const
{
    return Vec2(x * n, y * n);
}

// Divisão por escalar
Vec2 Vec2::operator/(real n) const
{
    return Vec2(x / n, y / n);
}

// Igualdade
bool Vec2::operator==(const Vec2& v) const
{
    if (comp(x, v.x) &&
        comp(y, v.y))
    {
        return true;
    }
    return false;
}

// Produto Escalar
real Vec2::dot(const Vec2& v) const
{
    return (x * v.x) + (y * v.y);
}

// Produto Vetorial 2D
real Vec2::cross(const Vec2& v) const
{
    real r = (x*v.y) - (y/v.x);
    return r;
}

// Magnitude
real Vec2::mag() const
{
    return std::sqrt((x * x) + (y * y));
}

// Distância entre vetores
real Vec2::distance(const Vec2& v) const
{
    real xf = x - v.x;
    real yf = y - v.y;
    real r = std::sqrt((xf * xf) + (yf * yf));
    return r;
}

// Normalização (vetor unitário)
Vec2 Vec2::normalize() const
{
    Vec2 r = (*this / mag());
    return r;
}

// Coseno de theta (para calculo do angulo)
real Vec2::costheta(const Vec2& v) const
{
    real r = dot(v) / (mag() * v.mag());
    return r;
}

// Angulo desse vetor contra outro
real Vec2::angle(const Vec2& v) const
{
    real r = std::acos(costheta(v));
    return r;
}

// Projeção escalar
real Vec2::scalarProjection(const Vec2& v) const
{
    real r = mag() * costheta(v);
    return r;
}

// Projeção vetorial
Vec2 Vec2::vectorProjection(const Vec2& v) const
{
    Vec2 r = v.normalize() * scalarProjection(v);
    return r;
}

bool Vec2::notNull()
{
    if (x == 0 && y == 0)
        return false;
    else return true;
}

int Vec2::oct()
{
    if (x > 0 && y > 0 && x > y) return 1;
    if (x >= 0 && y > 0 && y > x) return 2;

    if (x < 0 && y > 0 && y >= -x) return 3;
    if (x < 0 && y >= 0 && y < -x) return 4;

    if (x < 0 && y < 0 && x <= y) return 5;
    if (x <= 0 && y < 0 && x > y) return 6;

    if (x > 0 && y < 0 && x <= -y) return 7;
    if (x > 0 && y < 0 && x > -y) return 8;

    else return 1;
}

real Vec2::pseudoangle()
{
    double r = 0.0;
    if (oct() == 1)
    {
        r= y/x;
    }
    if (oct() == 2)
    {
        r= 2-(x/y);
    }
    if (oct() == 3)
    {
        r= 2-(x/y);
    }
    if (oct() == 4)
    {
        r= 4+(y/x);
    }
    if (oct() == 5)
    {
        r= 4-(-(y/x));
    }
    if (oct() == 6)
    {
        r= 6-(x/y);
    }
    if (oct() == 7)
    {
        r= 6-(x/y);
    }
    if (oct() == 8)
    {
        r= 8+(y/x);
    }
    return r;
}

Vec2 Vec2::pseudoangleVec()
{
    Vec2 r;
    if (oct() == 1)
    {
        r.x = 1;
        r.y = pseudoangle();
    }
    if (oct() == 2)
    {
        r.x = 2-pseudoangle();
        r.y = 1;
    }
    if (oct() == 3)
    {
        r.x = 2-pseudoangle();
        r.y = 1;
    }
    if (oct() == 4)
    {
        r.x = -1;
        r.y = 4-pseudoangle();
    }
    if (oct() == 5)
    {
        r.x = -1;
        r.y = 4-pseudoangle();
    }
    if (oct() == 6 )
    {
        r.x = -(6-pseudoangle());
        r.y = -1;
    }
    if (oct() == 7)
    {
        r.x = -(6-pseudoangle());
        r.y = -1;
    }
    if (oct() == 8)
    {
        r.x = 1;
        r.y = -(8-pseudoangle());
    }
    return r;
}

real Vec2::pseudoangleBetween(Vec2 v)
{
    return std::abs(pseudoangle() - v.pseudoangle());
}
