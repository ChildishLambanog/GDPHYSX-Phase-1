#include "DirectionLight.h"

DirectionLight::DirectionLight(glm::vec3 lightPos, glm::vec3 lightColor, float ambientStr, glm::vec3 ambientColor, 
                               float specStr, float specPhong, glm::vec3 direction, float brightness) :
                               Light(lightPos, lightColor, ambientStr, specStr, specPhong)
{
    this->direction = direction;
    this->brightness = brightness;
}

void DirectionLight::perform(GLuint* shaderProg)
{
    GLuint  lightLoc = glGetUniformLocation(*shaderProg, "lightPos");
    glUniform3fv(lightLoc, 1, glm::value_ptr(lightPos));

    GLuint lightColorLoc = glGetUniformLocation(*shaderProg, "lightColor");
    glUniform3fv(lightColorLoc, 1, glm::value_ptr(lightColor));

    GLuint ambientStrLoc = glGetUniformLocation(*shaderProg, "ambientStr");
    glUniform1f(ambientStrLoc, ambientStr);

    GLuint ambientColorLoc = glGetUniformLocation(*shaderProg, "ambientColor");

    glUniform3fv(ambientColorLoc, 1, glm::value_ptr(ambientColor));

    GLuint specStrLoc = glGetUniformLocation(*shaderProg, "specStr");
    glUniform1f(specStrLoc, specStr);

    GLuint specPhongLoc = glGetUniformLocation(*shaderProg, "specPhong");
    glUniform1f(specPhongLoc, specPhong);

    GLuint directionLoc = glGetUniformLocation(*shaderProg, "direction");
    glUniform3fv(directionLoc, 1, glm::value_ptr(direction));
}

void DirectionLight::attachSpecifics(Shader* shaderProg) //attaching the needed specific values for direction light
{
    shaderProg->setVec3("direction", direction);
    shaderProg->setFloat("dl_brightness", this->brightness);
}

void DirectionLight::setBrightness(float brightness)
{
    this->brightness = brightness;
}
