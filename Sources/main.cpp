#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <chrono>
#include "BaseFunctions.hpp"
#include "Renderer/GLSL_files/load_GLSL.hpp"
#include "Renderer/ShaderProgram.hpp"
#include "Matrix/Matrix.hpp"

//Windows
GLFWwindow* FirstWindow;
int windowSizeX = 1920;
int windowSizeY = 1080;

//Camera rotation
float lastX = windowSizeX / 2.0f;
float lastY = windowSizeY / 2.0f;
float yaw = -90.0f;
float pitch = 0.0f;

//Camera position
float valueZ = 5.0f;
float valueX = 0.0f;
float valueY = 1.5f;

//Delta time
float speed = 5.0;
float lastFrameTime = 0.0;

int times = 0;

float floorVertices[] = {
    -1.0f, -1.0f, 0.0f,  // Левый нижний угол
     1.0f, -1.0f, 0.0f,  // Правый нижний угол
     1.0f,  1.0f, 0.0f,  // Правый верхний угол
    
    -1.0f, -1.0f, 0.0f,  // Левый нижний угол
     1.0f,  1.0f, 0.0f,  // Правый верхний угол
    -1.0f,  1.0f, 0.0f   // Левый верхний угол
};

GLfloat cube_vertices[] = {
    // Координаты X, Y, Z
    -0.5f, -0.5f, -0.5f,  0.5f, -0.5f, -0.5f,  0.5f,  0.5f, -0.5f, // XYZ to 1, 2, 3 points for triangle
     0.5f,  0.5f, -0.5f, -0.5f,  0.5f, -0.5f, -0.5f, -0.5f, -0.5f, // 2 traingle = vertices

    -0.5f, -0.5f,  0.5f,  0.5f, -0.5f,  0.5f,  0.5f,  0.5f,  0.5f,
     0.5f,  0.5f,  0.5f, -0.5f,  0.5f,  0.5f, -0.5f, -0.5f,  0.5f,

    -0.5f,  0.5f,  0.5f, -0.5f,  0.5f, -0.5f, -0.5f, -0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f, -0.5f, -0.5f,  0.5f, -0.5f,  0.5f,  0.5f,

     0.5f,  0.5f,  0.5f,  0.5f,  0.5f, -0.5f,  0.5f, -0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,  0.5f, -0.5f,  0.5f,  0.5f,  0.5f,  0.5f,

    -0.5f, -0.5f, -0.5f,  0.5f, -0.5f, -0.5f,  0.5f, -0.5f,  0.5f,
     0.5f, -0.5f,  0.5f, -0.5f, -0.5f,  0.5f, -0.5f, -0.5f, -0.5f,

    -0.5f,  0.5f, -0.5f,  0.5f,  0.5f, -0.5f,  0.5f,  0.5f,  0.5f,
     0.5f,  0.5f,  0.5f, -0.5f,  0.5f,  0.5f, -0.5f,  0.5f, -0.5f,
};

GLfloat cube_colors[] = {
    // Задняя грань (Красный) - 6 вершин
    1.0f, 0.0f, 0.0f,  1.0f, 0.0f, 0.0f,  1.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 0.0f,  1.0f, 0.0f, 0.0f,  1.0f, 0.0f, 0.0f,

    // Передняя грань (Зеленый)
    0.0f, 1.0f, 0.0f,  0.0f, 1.0f, 0.0f,  0.0f, 1.0f, 0.0f,
    0.0f, 1.0f, 0.0f,  0.0f, 1.0f, 0.0f,  0.0f, 1.0f, 0.0f,

    // Левая грань (Синий)
    0.0f, 0.0f, 1.0f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f, 1.0f,

    // Правая грань (Желтый)
    1.0f, 1.0f, 0.0f,  1.0f, 1.0f, 0.0f,  1.0f, 1.0f, 0.0f,
    1.0f, 1.0f, 0.0f,  1.0f, 1.0f, 0.0f,  1.0f, 1.0f, 0.0f,

    // Нижняя грань (Маджента)
    1.0f, 0.0f, 1.0f,  1.0f, 0.0f, 1.0f,  1.0f, 0.0f, 1.0f,
    1.0f, 0.0f, 1.0f,  1.0f, 0.0f, 1.0f,  1.0f, 0.0f, 1.0f,

    // Верхняя грань (Циан)
    0.0f, 1.0f, 1.0f,  0.0f, 1.0f, 1.0f,  0.0f, 1.0f, 1.0f,
    0.0f, 1.0f, 1.0f,  0.0f, 1.0f, 1.0f,  0.0f, 1.0f, 1.0f
};

int main(void)
{
    //Base model
    MyFile::file_read BASE_vertex_shader(std::string("../../../Sources/Renderer/GLSL_files/BaseModel/vertex_shader.glsl"));
    MyFile::file_read BASE_fragment_shader(std::string("../../../Sources/Renderer/GLSL_files/BaseModel/fragment_shader.glsl"));

    //Infinite floor
    MyFile::file_read Floor_vertex_shader(std::string("../../../Sources/Renderer/GLSL_files/InfiniteFloor/vertex_shader.glsl"));
    MyFile::file_read Floor_fragment_shader(std::string("../../../Sources/Renderer/GLSL_files/InfiniteFloor/fragment_shader.glsl"));

    GLFWwindow* FirstWindow;
    /* Initialize the library */
    if (!glfwInit()) {
        std::cout << "glfwInit failed\n";
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    FirstWindow = glfwCreateWindow(windowSizeX, windowSizeY, "Somethink", NULL, NULL);
    if (!FirstWindow)
    {
        std::cout << "glfwCreateWindow failed\n";
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(FirstWindow);

    //ExitWindow by pressing ESC

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Can't load\n";
        return -1;
    }

    //WindowColor
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

    //Class ShaderProgram 
    Renderer::ShaderProgram BaseProgram(BASE_vertex_shader.getSource(), BASE_fragment_shader.getSource());

    if (!BaseProgram.isComipled()) {
        std::cout << "Can't create base shader program!\n";
    }

    //Get linked Program adress
    int modelLoc = glGetUniformLocation(BaseProgram.getProgramID(), "u_Model");
    if (modelLoc == -1) {
        std::cout << "Can't find uniform u_Model\n";
    }

    int viewLoc = glGetUniformLocation(BaseProgram.getProgramID(), "u_View");
    if (viewLoc == -1) {
        std::cout << "Can't find uniform u_View\n";
    }

    int projLoc = glGetUniformLocation(BaseProgram.getProgramID(), "u_Projection");
    if (projLoc == -1) {
        std::cout << "Can't find uniform u_Projection\n";
    }

    Renderer::ShaderProgram FloorProgram(Floor_vertex_shader.getSource(), Floor_fragment_shader.getSource());

    if (!FloorProgram.isComipled()) {
        std::cout << "Can't create floor shader program!\n";
    }

    int Floor_viewLoc = glGetUniformLocation(FloorProgram.getProgramID(), "u_View");
    if (Floor_viewLoc == -1) {
        std::cout << "Can't find uniform u_View\n";
    }

    int Floor_projLoc = glGetUniformLocation(FloorProgram.getProgramID(), "u_Projection");
    if (Floor_projLoc == -1) {
        std::cout << "Can't find uniform u_Projection\n";
    }

    //Generating in buffer

        //Buffer for points
        GLuint points_vbo = 0;
        glGenBuffers(1, &points_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices), cube_vertices, GL_DYNAMIC_DRAW);

        //Buffer for colors
        GLuint colors_vbo = 0;
        glGenBuffers(1, &colors_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(cube_colors), cube_colors, GL_DYNAMIC_DRAW);
       

        //Create and enable VAO, enable all configuration
        GLuint VectorArrayObject = 0;
        glGenVertexArrays(1, &VectorArrayObject);
        glBindVertexArray(VectorArrayObject);

        glEnableVertexAttribArray(0);                               //Enable slot 0 "Shaders.h (layout(location 0)" 
        glBindBuffer(GL_ARRAY_BUFFER, points_vbo);                  //Take in buffer
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);   //Made rules

        glEnableVertexAttribArray(1);                               //Enable slot 1 "Shaders.h (layout(location 0)"
        glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
        

    // FLOOR

        GLuint floorVBO, floorVAO;
        glGenVertexArrays(1, &floorVAO);
        glGenBuffers(1, &floorVBO);

        glBindVertexArray(floorVAO);

        glBindBuffer(GL_ARRAY_BUFFER, floorVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(floorVertices), floorVertices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), NULL);
        glEnableVertexAttribArray(0);

        glBindVertexArray(0);

    glfwSetKeyCallback(FirstWindow, RegSpeed);
    
    glfwSetCursorPosCallback(FirstWindow, mouse_callback);

    Matrix4x4 move = Matrix4x4::Move(0.0f, 0.51f, 0.0f);
    vec3 up = { 0.0f, 1.0f, 0.0f };
    float moveStep = 0.0f;
    //Matrix4x4 Orthographic_projection = orthoProjection(windowSizeX, windowSizeY);

    glfwSwapInterval(1);

    while (!glfwWindowShouldClose(FirstWindow))
    {
        glfwSetInputMode(FirstWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        glEnable(GL_DEPTH_TEST);
        /*
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        */

        //Delta time
        float current_Time = (float)glfwGetTime();
        float delta_Time = current_Time - (float)lastFrameTime;
        lastFrameTime = current_Time;
        moveStep = speed * delta_Time;
        
        
        vec3 front;
        front.x = cos(radians(yaw)) * cos(radians(pitch));
        front.y = sin(radians(pitch));
        front.z = sin(radians(yaw)) * cos(radians(pitch));
        front = Normalize(front);

        vec3 Wfront;
        Wfront.x = cos(radians(yaw));
        Wfront.y = 0;
        Wfront.z = sin(radians(yaw));

        vec3 right = Normalize(Cross_product(Wfront, up));

        if (glfwGetKey(FirstWindow, GLFW_KEY_W) == GLFW_PRESS || glfwGetKey(FirstWindow, GLFW_KEY_W) == GLFW_REPEAT) {
            valueX += Wfront.x * moveStep;
            valueZ += Wfront.z * moveStep;
        }
        if (glfwGetKey(FirstWindow, GLFW_KEY_S) == GLFW_PRESS || glfwGetKey(FirstWindow, GLFW_KEY_S) == GLFW_REPEAT) {
            valueX -= Wfront.x * moveStep;
            valueZ -= Wfront.z * moveStep;
        }

        if (glfwGetKey(FirstWindow, GLFW_KEY_A) == GLFW_PRESS || glfwGetKey(FirstWindow, GLFW_KEY_A) == GLFW_REPEAT) { 
            valueX -= right.x * moveStep;
            valueZ -= right.z * moveStep;
        }
        if (glfwGetKey(FirstWindow, GLFW_KEY_D) == GLFW_PRESS || glfwGetKey(FirstWindow, GLFW_KEY_D) == GLFW_REPEAT) { 
            valueX += right.x * moveStep;
            valueZ += right.z * moveStep;
        }

        if (glfwGetKey(FirstWindow, GLFW_KEY_SPACE) == GLFW_PRESS || glfwGetKey(FirstWindow, GLFW_KEY_SPACE) == GLFW_REPEAT) { 
            valueY += 1.0f * moveStep;
        }
        if (glfwGetKey(FirstWindow, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS || glfwGetKey(FirstWindow, GLFW_KEY_LEFT_SHIFT) == GLFW_REPEAT) { 
            if(valueY > 0.5f){
                valueY -= 1 * moveStep;
            }
        }
        if (glfwGetKey(FirstWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            glfwSetWindowShouldClose(FirstWindow, true);
        }

        vec3 eye = {valueX, valueY, valueZ};            
        vec3 target = eye + front; 

        Matrix4x4 Camera = Matrix4x4::Camera(eye, target, up);
        Matrix4x4 projection = perspectiveProjection(70.0f, windowSizeX, windowSizeY, 0.1f, 100.0f);
        Matrix4x4 final = move;

        //Base model
        BaseProgram.use();

        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, final.data);
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, Camera.data);
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, projection.data);

        glBindVertexArray(VectorArrayObject);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);

        //Floor
        
        FloorProgram.use();
        
        glUniformMatrix4fv(Floor_viewLoc, 1, GL_FALSE, Camera.data);
        glUniformMatrix4fv(Floor_projLoc, 1, GL_FALSE, projection.data);

        glBindVertexArray(floorVAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);

        glfwSwapBuffers(FirstWindow);
        glfwPollEvents();
        
    }
     
    glfwTerminate();
    return 0;
}