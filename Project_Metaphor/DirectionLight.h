#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Light.h"
#include "Shader.h"

class DirectionLight : public Light{
private:
	glm::vec3 direction;
	float brightness;

public:
	void perform(GLuint* shaderProg);
	void attachSpecifics(Shader* shaderProg);
	void setBrightness(float brightness);
	DirectionLight(glm::vec3 lightPos, glm::vec3 lightColor, float ambientStr, glm::vec3 ambientColor,
		float specStr, float specPhong, glm::vec3 direction, float brightness);
};