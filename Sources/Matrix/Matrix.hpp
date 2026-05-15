#ifndef _MATRIX_H
#define _MATRIX_H

#include "BaseMatrix.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

Matrix4x4 multiply(const float* A, const float* B);

Matrix4x4 orthoProjection(int width, int height);

Matrix4x4 perspectiveProjection(float fovY, int sizeX, int sizeY, float zNear, float zFar);

Matrix4x4 Camera(vec3 Position);

#endif