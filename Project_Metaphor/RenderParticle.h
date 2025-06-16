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

	float size;

	RenderParticle(P6Particle* particle, Model3D* model) : particle(particle), model(model)
	{
		color = P6::MyVector(1.0f, 1.0f, 1.0f); // Default color white
	}
	RenderParticle(P6Particle* p, Model3D* m, P6::MyVector color) : particle(p), model(m), color(color) {}

	RenderParticle(P6Particle* p, Model3D* m, P6::MyVector color, float size) : particle(p), model(m), color(color), size(size)
	{
		
	}

	void Draw();

	void Draw(Shader* shaderProg, GLuint* VAO, std::vector<GLfloat>* fullVertexData,GLuint* tex, std::string name);
};