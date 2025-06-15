#include "PointLight.h"

PointLight::PointLight(glm::vec3 lightPos, glm::vec3 lightColor, float ambientStr, glm::vec3 ambientColor, 
                       float specStr, float specPhong, float brightness) :
                       Light(lightPos,lightColor, ambientStr, specStr, specPhong)
{
	this->brightness = brightness;
}

void PointLight::perform(GLuint* shaderProg)
{
    GLuint  lightLoc = glGetUniformLocation(*shaderProg, "lightPos");
    glUniform3fv(lightLoc, 1, glm::value_ptr(lightPos));

    GLuint lightColorLoc = glGetUniformLocation(*shaderProg, "lightColor");
    glUniform3fv(lightColorLoc, 1, glm::value_ptr(lightColor));

    GLuint ambientStrLoc = glGetUniformLocation(*shaderProg, "ambientStr");
    glUniform1f(lightColorLoc, ambientStr);

    GLuint ambientColorLoc = glGetUniformLocation(*shaderProg, "ambientColor");

    glUniform3fv(lightColorLoc, 1, glm::value_ptr(ambientColor));

    GLuint specStrLoc = glGetUniformLocation(*shaderProg, "specStr");
    glUniform1f(specStrLoc, specStr);

    GLuint specPhongLoc = glGetUniformLocation(*shaderProg, "specPhong");
    glUniform1f(specPhongLoc,specPhong);

    GLuint brightnessLoc = glGetUniformLocation(*shaderProg, "brightness");
    glUniform1f(brightnessLoc, brightness);
}

void PointLight::attachSpecifics(Shader* shaderProg) //attaching the needed specific values for point light
{
    shaderProg->setFloat("brightness", brightness);
}

void PointLight::setPosition(glm::vec3 position)
{
    this->lightPos = position;
}

void PointLight::setBrightness(float brightness)
{
    this->brightness = brightness;
}
