#include "ParticleSystem.h"

void ParticleSystem::EmitParticle(P6::MyVector position, P6::MyVector velocity, float lifespan, Model3D* model) 
{
    auto* p = new P6::P6Particle(position.x, position.y, position.z);
    p->Velocity = velocity;
    p->SetLifespan(lifespan);

    auto* renderP = new RenderParticle(p, model);
    particles.push_back(renderP);
}

void ParticleSystem::Update(float deltaTime) 
{
    for (auto it = particles.begin(); it != particles.end(); ) 
    {
        RenderParticle* rp = *it;
        rp->particle->Update(deltaTime);

        if (rp->particle->IsDestroyed()) 
        {
            delete rp->particle;
            delete rp;
            it = particles.erase(it);
        }

        else 
        {
            ++it;
        }
    }
}

void ParticleSystem::Render(Shader* shaderProg, GLuint* VAO, std::vector<GLfloat>* vertexData, GLuint* tex, std::string name) 
{
    for (auto* rp : particles) 
    {
        rp->Draw(shaderProg, VAO, vertexData, tex, name);
    }
}

ParticleSystem::~ParticleSystem() 
{
    for (auto* rp : particles) 
    {
        delete rp->particle;
        delete rp;
    }
}