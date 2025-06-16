#include "RenderParticle.h"

void RenderParticle::Draw()
{
	model->setPosition(glm::vec3(particle->Position));

	model->color = glm::vec4((glm::vec3)this->color,1.f); //IDK 
	model->draw();
}

void RenderParticle::Draw(Shader* shaderProg, GLuint* VAO, std::vector<GLfloat>* fullVertexData, GLuint* tex, std::string name)
{
	model->setPosition(glm::vec3(particle->Position));
	model->color = glm::vec4((glm::vec3)this->color, 1.f); //IDK
	model->setScale(glm::vec3(size, size, size)); // Set the scale of the model


	model->setTexture(shaderProg, tex, name);
	model->mainDraw(shaderProg, VAO, fullVertexData);
}
