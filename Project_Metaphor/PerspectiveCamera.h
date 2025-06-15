#pragma once

#include "Camera.h"

class PerspectiveCamera : public Camera {
private:
	glm::mat4 projection;
public:
	PerspectiveCamera(glm::vec3 pos,float height, float width);
	glm::mat4 getProjection();
};