#include "Camera.h"

Camera::Camera(glm::vec3 pos)
{
    this->cameraPos = pos;
    this->viewMatrix = glm::lookAt(this->cameraPos, this->cameraPos + this->Front, this->WorldUp);
}

void Camera::setCameraPos(glm::vec3 camPos) 
{
    this->cameraPos = camPos;
}

void Camera::setFront(glm::vec3 Front) 
{
    this->Front = Front;
}

glm::vec3 Camera::getFront() 
{
    return this->Front;
}

glm::vec3 Camera::getWorldUp() 
{
    return this->WorldUp;
}
	
glm::mat4 Camera::getViewMat() 
{
    return this->viewMatrix;
}

glm::vec3 Camera::getCameraPos() 
{
    return this->cameraPos;
}