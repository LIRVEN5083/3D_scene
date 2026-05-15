#include "Matrix.hpp"

Matrix4x4 multiply(const float* A, const float* B) {
    Matrix4x4 res;
    for (int i = 0; i < 4; i++) { // raw A
        for (int j = 0; j < 4; j++) { // column B
            res.data[i * 4 + j] =
                A[i * 4 + 0] * B[0 * 4 + j] +
                A[i * 4 + 1] * B[1 * 4 + j] +
                A[i * 4 + 2] * B[2 * 4 + j] +
                A[i * 4 + 3] * B[3 * 4 + j];
        }
    }
    return res;
}

//Это сохраняющаяся пропорция относительно размеров нашего окна. Т.е если треугольник равносторонний он им и останется вне зависимости от изменения размера окна
Matrix4x4 orthoProjection(int width, int height) { //Ортографическая проекция
    
    if (height == 0) {
        height = 1;
    }
    float aspect = (float)width / (float)height;

    Matrix4x4 myOrtho;

    if (width >= height) {
        myOrtho = Matrix4x4::Ortho(-1.0f * aspect, 1.0f * aspect, -1.0f, 1.0f, -1.0f, 1.0f);
    }
    else {
        myOrtho = Matrix4x4::Ortho(-1.0f, 1.0f, -1.0f / aspect, 1.0f / aspect, -1.0f, 1.0f);
    }
    
    return myOrtho;
}

Matrix4x4 perspectiveProjection(float fovY_degrees, int sizeX, int sizeY, float zNear, float zFar){
    float aspect = (float)sizeX / (float)sizeY;
    float fovRAD = fovY_degrees * (M_PI / 180.0f);
    float top, bottom, right, left;

    top = zNear * tan(fovRAD / 2.0f);
    bottom = -top;
    right = top * aspect;
    left = -right;

    return Matrix4x4::Perspective(left, right, bottom, top, zNear, zFar);
}
