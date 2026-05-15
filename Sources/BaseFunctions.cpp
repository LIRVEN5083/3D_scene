#include "BaseFunctions.hpp"

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; 
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.05f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    if (pitch > 89.0f) pitch = 89.0f;
    if (pitch < -89.0f) pitch = -89.0f;
}

float getTime() {
    static auto start_Time = std::chrono::steady_clock::now();
    auto current_Time = std::chrono::steady_clock::now();

    std::chrono::duration<float> time = current_Time - start_Time;

    return time.count();
}

void IncreaseSpeed(float& speed) {
    speed += 0.1;
    if (times == 2) {
        std::cout << "current speed: " << speed << "\n";
        times = 0;
    }
    times++;
}

void DecreaseSpeed(float& speed) {
    if(speed > 0.2){
        speed -= 0.1;
    }
    if (times == 2) {
        std::cout << "current speed: " << speed << "\n";
        times = 0;
    }
    times++;
}

void Move(float valueX, float valueY) {
    glTranslated(valueX, valueY, 0.0);
}

void SetupModelViewMatrix(float time, int speed) {
    glMatrixMode(GL_MODELVIEW); // команда устаревшего (Fixed Function Pipeline) OpenGL, которая переключает текущий режим работы с матрицами на «видовую матрицу модели
    glLoadIdentity(); //Единичная матрциа - текущая матрица

    glScaled(1.0, 1.0, 1.0);
    glRotated(time * speed, 0.0, 0.0, 1); // Матрица поворота

    //glTranslated(0.0, 0.0, 0.0); //Матрица переноса

    /* 
        T1, T2, T3
        T3 * T2 * T1 
    */
}

void WindowSize(GLFWwindow* window, int width, int height){
    windowSizeX = width;
    windowSizeY = height;
    glViewport(0, 0, windowSizeX, windowSizeY); // Visible draw size
}

void RegSpeed(GLFWwindow* window, int key, int scancode, int action, int mode) {
    
    if (action == GLFW_PRESS || action == GLFW_REPEAT) {
        if (key == GLFW_KEY_Q) { IncreaseSpeed(speed); }
        if (key == GLFW_KEY_E) { DecreaseSpeed(speed); }
    }
}