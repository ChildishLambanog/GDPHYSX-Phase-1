#pragma once
#include "P6Particle.h"
#include "PhysicsWorld.h"
#include "../RenderParticle.h" //replace with render particle class for easier rendering
#include"../Model3D.h" // replace with model class
class ParticleSystem
{
private:
    std::vector<RenderParticle*> particles;

public:
    void EmitParticle(P6::MyVector position, P6::MyVector velocity, float lifespan, Model3D* model);
    void Update(float deltaTime);
    void Render(Shader* shaderProg, GLuint* VAO, std::vector<GLfloat>* vertexData, GLuint* tex, std::string name);
    ~ParticleSystem();

};

