#pragma once
#include "P6/P6Particle.h"
#include "Model3D.h"
using namespace P6;
class RenderParticle
{
public:
	P6Particle* particle;
	Model3D* model;
	P6::MyVector color;

	/*
	to test 

	std::vector<GLfloat> fullVertexData;
	GLuint* VAO;
	Shader* shaderProgs;
	
	*/

	
	// GLuint* texture;

	RenderParticle(P6Particle* particle, Model3D* model) : particle(particle), model(model)
	{
		color = P6::MyVector(1.0f, 1.0f, 1.0f); // Default color white
	}
	RenderParticle(P6Particle* p, Model3D* m, P6::MyVector color) : particle(p), model(m), color(color) {}
	void Draw();

	void Draw(Shader* shaderProg, GLuint* VAO, std::vector<GLfloat>* fullVertexData,GLuint* tex, std::string name);

//	void setTexInt(GLuint* texture) { this->texture = texture; }
};