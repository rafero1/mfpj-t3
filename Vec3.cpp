#include <iostream>
#include <cmath>
#include <string>
#include "Vec3.h"
#include "util.h"

// Output
std::ostream& operator<<(std::ostream& os, const Vec3& v)
{
	os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
	return os;
}

// Input
std::istream& operator>>(std::istream& is, Vec3& v)
{
	//char chars[] = "1234567890";
	//std::string input;
	is >> v.x >> v.y >> v.z;
	return is;
}

// Soma
Vec3 Vec3::operator+(const Vec3& v) const
{
	return Vec3(x + v.x, y + v.y, z + v.z);
}

// Subtração
Vec3 Vec3::operator-(const Vec3& v) const
{
	return Vec3(x - v.x, y - v.y, z - v.z);
}

// Produto por escalar
Vec3 Vec3::operator*(real n) const
{
	return Vec3(x * n, y * n, z * n);
}

// Divisão por escalar
Vec3 Vec3::operator/(real n) const
{
	return Vec3(x / n, y / n, z / n);
}

// Igualdade
bool Vec3::operator==(const Vec3& v) const
{
	if (comp(x, v.x) &&
		comp(y, v.y) &&
		comp(z, v.z))
	{
		return true;
	}
	return false;
}

// Produto Escalar
real Vec3::dot(const Vec3& v) const
{
	return (x * v.x) + (y * v.y) + (z * v.z);
}

// Produto Vetorial
Vec3 Vec3::cross(const Vec3& v) const
{
	Vec3 r = Vec3((y * v.z) - (z * v.y), (z * v.x) - (x * v.z), (x * v.y) - (y * v.x));
	return r;
}

// Magnitude
real Vec3::mag() const
{
	return std::sqrt((x * x) + (y * y) + (z * z));
}

// Distância entre vetores
real Vec3::distance(const Vec3& v) const
{
    real xf = x - v.x;
    real yf = y - v.y;
    real zf = z - v.z;
    real r = std::sqrt((xf * xf) + (yf * yf) + (zf * zf));
	return r;
}

// Normalização (vetor unitário)
Vec3 Vec3::normalize() const
{
	Vec3 r = (*this / mag());
	return r;
}

// Coseno de theta (para calculo do angulo)
real Vec3::costheta(const Vec3& v) const
{
    real r = dot(v) / (mag() * v.mag());
	return r;
}

// Angulo desse vetor contra outro
real Vec3::angle(const Vec3& v) const
{
    real r = std::acos(costheta(v));
	return r;
}

// Projeção escalar
real Vec3::scalarProjection(const Vec3& v) const
{
    real r = mag() * costheta(v);
	return r;
}

// Projeção vetorial
Vec3 Vec3::vectorProjection(const Vec3& v) const
{
	Vec3 r = v.normalize() * scalarProjection(v);
	return r;
}
