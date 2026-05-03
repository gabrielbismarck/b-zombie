#ifndef VEC2_H
#define VEC2_H

class Vec2 {
    public: float x, y;

    Vec2(); // Inicializa com (0, 0)
    Vec2(float x, float y);

    // Operações recomendadas para trabalhar com vetores
    // Aqui faço uma sobrecarga nos operadores para trabalhar com vetores
    // Quando usar um operador (+, - ou *), ele retorna um novo vetor (Vec2)
    Vec2 operator+(const Vec2& v) const;
    Vec2 operator-(const Vec2 v) const;
    Vec2 operator*(const float v) const;

    // Magnitude do vetor
    float Mag() const;

    // Normaliza o vetor
    Vec2 Normalize() const;

    // Distância entre 2 pontos
    float Distance(const Vec2& v) const;

    // Inclinação do vetor
    float InclinationX() const;

    // Inclinação em radianos
    Vec2 InclinationRad(float angle) const;
};
#endif