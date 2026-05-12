#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include "three_d_obj.h"
#include "camera.h"

// --------------------
// Camera
// --------------------
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

// --------------------
// Timing
// --------------------
float lastFrame = 0.0f;
float deltaTime = 0.0f;

// --------------------
// Mouse state
// --------------------
float lastX = 400, lastY = 300;
bool firstMouse = true;

// --------------------
// Cursor toggle state
// --------------------
bool cursorLocked = true;
bool pPressedLastFrame = false;

// --------------------
// Window size (IMPORTANT)
// --------------------
int screenWidth = 800;
int screenHeight = 600;

// --------------------
// Resize callback (FIX FOR FULLSCREEN)
// --------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    screenWidth = width;
    screenHeight = height;
    glViewport(0, 0, width, height);
}

// --------------------
// Mouse callback
// --------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (!cursorLocked) return;

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;

    lastX = xpos;
    lastY = ypos;


    camera.ProcessMouse(xoffset, yoffset);
}

// --------------------
// Input handling
// --------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(0, deltaTime);

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(1, deltaTime);

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(2, deltaTime);

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(3, deltaTime);

    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        camera.ProcessKeyboard(4, deltaTime);

    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        camera.ProcessKeyboard(5, deltaTime);
}

// --------------------
// Cursor toggle (P key)
// --------------------
void updateCursor(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS && !pPressedLastFrame)
    {
        cursorLocked = !cursorLocked;

        if (cursorLocked)
        {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            firstMouse = true;
        }
        else
        {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        }

        pPressedLastFrame = true;
    }

    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_RELEASE)
        pPressedLastFrame = false;
}

// --------------------
// MAIN
// --------------------
int main()
{
    std::cout << "Engine starting 1...\n";

    if (!glfwInit())
    {
        std::cout << "Failed to init GLFW\n";
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window =
        glfwCreateWindow(screenWidth, screenHeight, "Renderer Engine", nullptr, nullptr);

    if (!window)
    {
        std::cout << "Failed to create window\n";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    // IMPORTANT: callbacks BEFORE loop
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to init GLAD\n";
        return -1;
    }

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    // set initial viewport
    glViewport(0, 0, screenWidth, screenHeight);

    // --------------------
    // Scene
    // --------------------
    Cube3D cube;
    cube.init();

    // --------------------
    // GAME LOOP
    // --------------------
    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(window);
        updateCursor(window);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 projection = glm::perspective(
            glm::radians(45.0f),
            (float)screenWidth / (float)screenHeight,
            0.1f,
            100.0f
        );

        cube.render(
            glfwGetTime(),
            camera.GetViewMatrix(),
            projection
        );

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    cube.cleanup();
    glfwTerminate();
    return 0;
}