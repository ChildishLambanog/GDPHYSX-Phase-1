#include "FountainDemo.h"

FountainDemo::FountainDemo(P6::PhysicsWorld* world, Model3D* model, int maxSparks) : world(world), sparkModel(model), maxSparks(maxSparks) 
{

}

void FountainDemo::Update(float deltaTime) 
{
    spawnTimer += deltaTime;

    //Spawn new sparks if under max count
    while (renderParticles.size() < maxSparks && spawnTimer >= spawnCooldown) 
    {
        spawnTimer = 0.0f;

        //Create new particle at a fixed position (can randomize X/Z for spread)
        P6::P6Particle* spark = new P6::P6Particle(0, 0, 0);
        spark->Position = P6::MyVector(0, -320.0f, 0);

        //Assign a random velocity for spray effect
        spark->Velocity = P6::MyVector(
            (rand() % 200 - 100) / 100.0f,  //X: -1 to 1
            (rand() % 200) / 100.0f + 4.0f, //Y: 4 to 6 m/s upward
            (rand() % 200 - 100) / 100.0f   //Z: -1 to 1
        );

        //Assign random lifespan (1.0 to 10.0 seconds)
        float lifespan = 1.0f + static_cast<float>(rand() % 900) / 100.0f; // 1.0 to 10.0
		//std::cout << "Lifespan: " << lifespan << std::endl;
        spark->SetLifespan(lifespan);

        //Assign random radius (2.0 to 10.0)
        float radius = 2.0f + static_cast<float>(rand() % 800) / 100.0f; // 2.0 to 10.0

        //Set the Mass
        spark->mass = 1.0f;

        //Apply initial spray force
        P6::MyVector sprayForce(
            (rand() % 200 - 100) * 1000,         //X: -100 to 100 N
            ((rand() % 200) + 300) * 1000,       //Y: 300 to 500 N
            (rand() % 200 - 100) * 1000          //Z: -100 to 100 N (was -1000 to 1000, but with *1000 for parity)
        );
        spark->AddForce(sprayForce);
        //std::cout << "Spray force: X=" << sprayForce.x << std::endl;

        //Add the particle to the physics world
        world->AddParticle(spark);

        //Assign a random color
        P6::MyVector color(
            static_cast<float>(rand() % 100) / 100.0f,
            static_cast<float>(rand() % 100) / 100.0f,
            static_cast<float>(rand() % 100) / 100.0f
        );

        //Create render particle and store it
        RenderParticle* renderP = new RenderParticle(spark, sparkModel, color,radius);
        renderParticles.push_back(renderP);
    }

    //Remove and delete the dead particles
    renderParticles.erase(
        std::remove_if(renderParticles.begin(), renderParticles.end(),
            [](RenderParticle* rp) {
                if (rp->particle->IsDestroyed()) {
                    delete rp;
                    return true;
                }
                return false;
            }),
        renderParticles.end()
    );
}

void FountainDemo::Render(Shader* shaderProg, GLuint* VAO, std::vector<GLfloat>* vertexData, GLuint* tex, std::string name) //Renders all active particles in the fountain.
{
    for (auto* rp : renderParticles) 
    {
        rp->Draw(shaderProg, VAO, vertexData, tex, name);
    }
}

FountainDemo::~FountainDemo() //Destructor that cleans up all the dynamically allocated render particles
{
    for (auto* rp : renderParticles) 
    {
        delete rp;
    }
}