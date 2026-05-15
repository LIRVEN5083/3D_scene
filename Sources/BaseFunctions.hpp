#ifndef _BASE_FUNCTIONS_HPP
#define _BASE_FUNCTIONS_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <chrono>
#include <iostream>
#include <thread>

//WindowSize
extern int windowSizeX;
extern int windowSizeY;

//Movement
extern float valueZ;
extern float valueX;
extern float valueY;
extern float speed;
extern float lastFrameTime;

//For view
extern float lastX;
extern float lastY;
extern float yaw;
extern float pitch;

//Mouse pos
extern int times;

void mouse_callback(GLFWwindow* window, double xpos, double ypos);

void IncreaseSpeed(float& speed);

void DecreaseSpeed(float& speed);

void Move(float valueX, float valueY);

void SetupModelViewMatrix(float phase, int speed);

float getTime();

void WindowSize(GLFWwindow* window, int width, int height);

void RegSpeed(GLFWwindow* window, int key, int scancode, int action, int mode);

#endif