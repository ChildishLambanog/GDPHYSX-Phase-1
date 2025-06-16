#include "OrthoCamera.h"


OrthoCamera::OrthoCamera(glm::vec3 pos) : Camera(pos) 
{
    //initializing the orthographic camera
	this->projection = glm::ortho(
        -400.0f,     //left
        400.0f,      //right
        -400.0f,     //bot
        400.0f,      //top
        -0.1f,     //z near
        800.f);    //z far
    this->WorldUp = glm::vec3(0.f, 1.0f, 0.f); //0.f, 1.0f, 0.f
    this->Front = glm::vec3(0.0f, 0.0f, -1.0f); //0.0f, -3.0f, -0.1f/1.0f
}

glm::mat4 OrthoCamera::getProjection() {
	return this->projection;
}