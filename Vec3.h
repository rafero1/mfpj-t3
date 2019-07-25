#ifndef VEC3_H
#define VEC3_H

#include <iostream>

/* Desafio:
 * TODO: Vetores 2D e 4D
 * TODO: Quais constantes de classe pode adicionar?
**/
typedef double real;
class Vec3
{
public:
	
	union
	{
        real coords[3];
        struct { real x, y, z; };
	};

	// Construtor padrão
	Vec3(): x(0), y(0), z(0) {}

	// Construtor básico
    Vec3(real x, real y, real z): x(x), y(y), z(z) {}

    // IO
	friend std::ostream& operator<<(std::ostream& os, const Vec3& v);
	friend std::istream& operator>>(std::istream& is, Vec3& v);

	// Operações
	Vec3 operator+(const Vec3& v) const;    // Adição de vetores
	Vec3 operator-(const Vec3& v) const;    // Subtração de vetores
    Vec3 operator*(real n) const;  // Produto por escalar
    Vec3 friend operator*(real n, const Vec3& v) {return v*n;}
    Vec3 operator/(real n) const;  // Divisão por escalar
    Vec3 friend operator/(real n, const Vec3& v) {return v/n;}
    bool operator==(const Vec3& v) const;   // Igualdade

    real dot(const Vec3& v) const;		// Produto escalar (Dot product, produto interno)
	Vec3 cross(const Vec3& v) const;        // Produto vetorial (Cross product)

	// Magnitude (Norma, módulo, comprimento)
    real mag() const;

    // Distância entre vetores
    real distance(const Vec3& v) const;

	// Normalização (vetor unitário)
	Vec3 normalize() const;

	// Ângulos entre vetores
    real costheta(const Vec3& v) const;
    real angle(const Vec3& v) const;

	// Projeção
    real scalarProjection(const Vec3& v) const;
	Vec3 vectorProjection(const Vec3& v) const;

private:
};

#endif // VEC3_H
