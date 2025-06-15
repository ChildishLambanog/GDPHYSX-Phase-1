#include "ColorLight.h"

ColorLight::ColorLight()
{
	this->red = 1.0f;
	this->blue = 1.0f;
	this->green = 1.0f;
}

void ColorLight::perform(Shader* shaderProg)
{
	shaderProg->setFloat("red", this->red);
	shaderProg->setFloat("green", this->green);
	shaderProg->setFloat("blue", this->blue);
}

void ColorLight::setColor(float red, float green, float blue)
{
	this->red = red;
	this->green = green;
	this->blue = blue;
}

void ColorLight::setColor(glm::vec3 rgb)
{
	this->red = rgb.x;
	this->green = rgb.y;
	this->blue = rgb.z;
}
