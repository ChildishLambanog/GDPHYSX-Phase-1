#include "PerspectiveCamera.h"

PerspectiveCamera::PerspectiveCamera(glm::vec3 pos,float height,float width) : Camera(pos) 
{
    //initializing the perspective camera
    this-> projection = glm::perspective(
        glm::radians(60.f),   //FOV
        height / width,       //aspect ratio
        0.1f,                 //znear > 0
        1000.f);              //zfar
    this->WorldUp = glm::vec3(0.f, 1.0f, 0.f);
    this->Front = glm::vec3(0.0f, 0.0f, 1.0f);
}

glm::mat4 PerspectiveCamera::getProjection() 
{
    return this->projection;
}