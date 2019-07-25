#ifndef VEC2_H
#define VEC2_H

#include <iostream>

typedef double real;
class Vec2
{
public:
    union
    {
        real coords[3];
        struct { real x, y; };
    };

    // Construtor padrão
    Vec2(): x(0), y(0) {}

    // Construtor básico
    Vec2(real x, real y): x(x), y(y) {}

    // IO
    friend std::ostream& operator<<(std::ostream& os, const Vec2& v);
    friend std::istream& operator>>(std::istream& is, Vec2& v);

    // Operações
    Vec2 operator+(const Vec2& v) const;    // Adição de vetores
    Vec2 operator-(const Vec2& v) const;    // Subtração de vetores
    Vec2 operator*(real n) const;  // Produto por escalar
    Vec2 friend operator*(real n, const Vec2& v) {return v*n;}
    Vec2 operator/(real n) const;  // Divisão por escalar
    Vec2 friend operator/(real n, const Vec2& v) {return v/n;}
    bool operator==(const Vec2& v) const;   // Igualdade

    real dot(const Vec2& v) const;		// Produto escalar (Dot product, produto interno)
    real cross(const Vec2& v) const;        // Produto vetorial 2D (Cross product)

    // Magnitude (Norma, módulo, comprimento)
    real mag() const;

    // Distância entre vetores
    real distance(const Vec2& v) const;

    // Normalização (vetor unitário)
    Vec2 normalize() const;

    // Ângulos entre vetores
    real costheta(const Vec2& v) const;
    real angle(const Vec2& v) const;

    // Projeção
    real scalarProjection(const Vec2& v) const;
    Vec2 vectorProjection(const Vec2& v) const;

    bool notNull();

    int oct();
    real pseudoangle();
    real pseudoangleBetween(Vec2 v);
    Vec2 pseudoangleVec();
};

#endif // VEC2_H
