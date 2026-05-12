#include "camera.h"

Camera::Camera(glm::vec3 startPos)
{
    Position = startPos;
    WorldUp = glm::vec3(0, 1, 0);

    Yaw = -90.0f;
    Pitch = 0.0f;

    Speed = 5.0f;
    Sensitivity = 0.1f;

    updateVectors();
}

glm::mat4 Camera::GetViewMatrix()
{
    return glm::lookAt(Position, Position + Front, Up);
}

void Camera::ProcessKeyboard(int direction, float deltaTime)
{
    float velocity = Speed * deltaTime;

    if (direction == 0) // W
        Position += Front * velocity;
    if (direction == 1) // S
        Position -= Front * velocity;
    if (direction == 2) // A
        Position -= Right * velocity;
    if (direction == 3) // D
        Position += Right * velocity;
    if (direction == 4) // space
        Position += WorldUp * velocity;
    if (direction == 5) // down
        Position += WorldUp * -velocity;

}

void Camera::ProcessMouse(float xoffset, float yoffset)
{
    xoffset *= Sensitivity;
    yoffset *= Sensitivity;

    Yaw += xoffset;
    Pitch += yoffset;

    if (Pitch > 89.0f) Pitch = 89.0f;
    if (Pitch < -89.0f) Pitch = -89.0f;

    updateVectors();
}

void Camera::updateVectors()
{
    glm::vec3 front;
    front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    front.y = sin(glm::radians(Pitch));
    front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));

    Front = glm::normalize(front);
    Right = glm::normalize(glm::cross(Front, WorldUp));
    Up = glm::normalize(glm::cross(Right, Front));
}