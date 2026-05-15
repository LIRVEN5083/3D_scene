#ifndef _LINIAR_MATH_HPP
#define _LINIAR_MATH_HPP

#define _USE_MATH_DEFINES
#include <cmath>

struct vec3 {
    float x, y, z;

    vec3 operator -(const vec3& first) {
        return {
            this->x - first.x,
            this->y - first.y,
            this->z - first.z
        };
    }

    vec3 operator +(const vec3& first) {
        return {
            this->x + first.x,
            this->y + first.y,
            this->z + first.z
        };
    }
};

float quad(float a);

float radians(float a);

//Векторное произведение (перп-вектор только на 2 вектора сразу. Т.е вектор который перпендекулярен 2 другим векторам)
vec3 Cross_product(vec3 a, vec3 b);

//Приводим вектор к базису т.е r 1.0f при этом сохраняя его направление
vec3 Normalize(vec3 a);

float dot(vec3 a, vec3 b);

float det(const float* matrix, int ROWsize);

#endif