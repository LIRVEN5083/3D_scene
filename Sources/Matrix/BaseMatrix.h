#ifndef _BASE_MATRIX_H
#define _BASE_MATRIX_H

#include "liniarMath.hpp"

struct Matrix4x4 {
    float data[16];

    Matrix4x4() {
        for (int i = 0; i < 16; i++) {
            data[i] = 0.0f;
        }

        data[0] = data[5] = data[10] = data[15] = 1.0f;
    }

    static Matrix4x4 Move(float dx, float dy, float dz) {
        Matrix4x4 res;
        res.data[12] = dx;
        res.data[13] = dy;
        res.data[14] = dz;
        return res;
    }

    static Matrix4x4 Scale(float dx, float dy, float dz) {
        Matrix4x4 res;
        res.data[0] = dx;
        res.data[5] = dy;
        res.data[10] = dz;
        return res;
    }

    static Matrix4x4 RotateX(float angle) {
        Matrix4x4 res;
        float SinA = sin(angle);
        float CosA = cos(angle);
        res.data[5] = CosA;
        res.data[6] = -SinA;
        res.data[9] = SinA;
        res.data[10] = CosA;
        return res;
    }

    static Matrix4x4 RotateY(float angle) {
        Matrix4x4 res;
        float SinA = sin(angle);
        float CosA = cos(angle);
        res.data[0] = CosA;
        res.data[2] = SinA;
        res.data[8] = -SinA;
        res.data[10] = CosA;
        return res;
    }

    static Matrix4x4 RotateZ(float angle) {
        Matrix4x4 res;
        float SinA = sin(angle);
        float CosA = cos(angle);
        res.data[0] = CosA;
        res.data[1] = -SinA;
        res.data[4] = SinA;
        res.data[5] = CosA;
        return res;
    }

    static Matrix4x4 Rotate(float angle, float dx, float dy, float dz) {
        Matrix4x4 res;
        // Normalisation
        // Find Pythagorean length
        float length = sqrt(dx*dx + dy*dy + dz*dz);
        if (length > 0) {
            float invLength = 1.0f / length;
            dx *= invLength;
            dy *= invLength;
            dz *= invLength;
        }
        
        float s = sin(angle);
        float c = cos(angle);
        
        // Very often repeat (1-c)
        float oc = 1.0f - c;

        // first column
        res.data[0] = oc * dx * dx + c;
        res.data[1] = oc * dx * dy + dz * s;
        res.data[2] = oc * dx * dz - dy * s;

        // second column
        res.data[4] = oc * dx * dy - dz * s;
        res.data[5] = oc * dy * dy + c;
        res.data[6] = oc * dy * dz + dx * s;

        // third column
        res.data[8] = oc * dx * dz + dy * s;
        res.data[9] = oc * dy * dz - dx * s;
        res.data[10] = oc * dz * dz + c;

        return res;
    }

    static Matrix4x4 Ortho(float left, float right, float bottom,
                                float top, float near, float far) {
        Matrix4x4 res;

        res.data[0] = 2.0f / (right - left);
        res.data[12] = -(right + left) / (right - left);
        res.data[5] = 2.0f / (top - bottom);
        res.data[13] = -(top + bottom) / (top - bottom);
        res.data[10] = (-2.0f)/(far - near);
        res.data[14] = -(far + near)/(far-near);

        return res;
    }

    static Matrix4x4 Perspective(float left, float right, float bottom,
                                       float top, float near, float far) {
        Matrix4x4 res;
        // fisrt column
        res.data[0] = (2.0f * near) / (right - left);
        // second column
        res.data[5] = (2.0f * near) / (top - bottom);
        // third column
        res.data[8] = (right + left) / (right - left);
        res.data[9] = (top + bottom) / (top - bottom);
        res.data[10] = -((far + near) / (far - near));
        res.data[11] = -1.0f;
        // fourth column
        res.data[14] = -((2.0f * far * near) / (far - near));
        res.data[15] = 0.0f;
        
        return res;
    }

    static Matrix4x4 Camera(vec3 eye, vec3 target, vec3 up) { //up - нужен для орьентации, чтобы понимать где в нашем Координатном фрейме другие оси, путём получения перпендекуляров
        Matrix4x4 res;

        vec3 z = Normalize(eye - target);
        vec3 x = Normalize(Cross_product(up, z)); //y и z - нормализованый перпендекуляр получается x
        vec3 y = Cross_product(z, x);

        // first column
        res.data[0] = x.x;
        res.data[1] = y.x;
        res.data[2] = z.x;
        res.data[3] = 0.0f;

        // second column
        res.data[4] = x.y;
        res.data[5] = y.y;
        res.data[6] = z.y;
        res.data[7] = 0.0f;

        //third column
        res.data[8] = x.z;
        res.data[9] = y.z;
        res.data[10] = z.z;
        res.data[11] = 0.0f;

        // fourth column
        res.data[12] = -dot(x, eye);
        res.data[13] = -dot(y, eye);
        res.data[14] = -dot(z, eye);
        res.data[15] = 1.0f;

        return res;
    }
};

#endif