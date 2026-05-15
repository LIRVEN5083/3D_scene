#include "liniarMath.hpp"

float quad(float a) {return a * a;}

float radians(float a)
{
	return a*(M_PI/180.0f);
};

vec3 Cross_product(vec3 a, vec3 b) {
	vec3 result;
	result.x = a.y * b.z - a.z * b.y;
	result.y = a.z * b.x - a.x * b.z;
	result.z = a.x * b.y - a.y * b.x;
	return result;
};

vec3 Normalize(vec3 a) {
	//Длинна вектора по Пифагору
	float L = sqrt(quad(a.x) + quad(a.y) + quad(a.z));
	if (L > 0) {
		return { a.x / L, a.y / L, a.z / L };
	}
	return { 0, 0, 0 };
}

float dot(vec3 a, vec3 b) {
	return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}

float det(const float* matrix, int ROWsize) {
    float result = 1.0f;
    float size = ROWsize * ROWsize;
    float* src = new float[ROWsize * ROWsize];

    for (int i = 0; i < size; i++) {
        src[i] = matrix[i];
    }

    // Проверка на нули в ведущей диоганали 
    for (int a = 0; a < ROWsize; a++) {
        int countROW = a;
        for (int b = a + 1; b < ROWsize; b++) {
            if (std::abs(src[b * ROWsize + a]) > std::abs(src[countROW * ROWsize + a])) {
                countROW = b;
            }
        }
        // Если нули по всей диагонали то определитель 0
        if (std::abs(src[countROW * ROWsize + a]) == 0.0f) {
            delete[] src;
            return 0.0f;
        }
        // Свап строк местами если у нас нашёлся ноль
        if (a != countROW) {
            for (int c = 0; c < ROWsize; c++) {
                float temp = src[a * ROWsize + c];
                src[a * ROWsize + c] = src[countROW * ROWsize + c];
                src[countROW * ROWsize + c] = temp;
            }
            result *= -1.0f;
        }

        result *= src[a * ROWsize + a];

        // Обнуление элементов под ведущим элементом
        for (int d = a + 1; d < ROWsize; d++) {
            float factor = src[d * ROWsize + a] / src[a * ROWsize + a];
            for (int k = a; k < ROWsize; ++k) {
                src[d * ROWsize + k] -= factor * src[a * ROWsize + k];
            }
        }
    }
    delete[] src;
    return result;
}
