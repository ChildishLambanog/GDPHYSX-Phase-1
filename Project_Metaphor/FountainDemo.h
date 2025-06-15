#pragma once
#include <vector>
#include <algorithm>
#include "P6/PhysicsWorld.h"
#include "RenderParticle.h"
//#include"P6/ForceRegistry.h"
#include "Model3D.h"

class FountainDemo {
private:
    P6::PhysicsWorld* world;
    std::vector<RenderParticle*> renderParticles;

    int maxSparks;
    float spawnCooldown = 0.05f;
    float spawnTimer = 0.0f;
    //P6::RandomSprayForceGenerator spray = P6::RandomSprayForceGenerator(500.0f, 800.0f, 100.0f);
    Model3D* sparkModel;

public:
    FountainDemo(P6::PhysicsWorld* world, Model3D* model, int maxSparks);
//P6::ForceRegistry forceRegistry;
    void Update(float deltaTime);
    void Render(Shader* shaderProg, GLuint* VAO, std::vector<GLfloat>* vertexData, GLuint* tex, std::string name);
    
    ~FountainDemo();
};
