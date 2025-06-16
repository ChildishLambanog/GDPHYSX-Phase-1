#include "FountainDemo.h"

FountainDemo::FountainDemo(P6::PhysicsWorld* world, Model3D* model, int maxSparks)
    : world(world), sparkModel(model), maxSparks(maxSparks) {

}

//void FountainDemo::Update(float deltaTime) {
//    spawnTimer += deltaTime;
//
//    // Spawn new sparks
//    while (renderParticles.size() < maxSparks && spawnTimer >= spawnCooldown) {
//        spawnTimer = 0.0f;
//
//        P6::P6Particle* spark = new P6::P6Particle(0, 0, 0); //spawn from origin
//        spark->Velocity = P6::MyVector(
//            (rand() % 100 - 50) / 50.0f,              // x: -1.0 to 1.0
//            (rand() % 100) / 50.0f + 3.0f,            // y: 3.0 to 5.0
//            (rand() % 100 - 50) / 50.0f               // z: -1.0 to 1.0
//        );
//        spark->SetLifespan(1.5f + (rand() % 50) / 100.0f); // lifespan 1.5ÅEs
//
//        world->AddParticle(spark);
//
//        auto* renderP = new RenderParticle(spark, sparkModel, P6::MyVector(1, 1, 0)); // yellow spark
//        renderParticles.push_back(renderP);
//    }
//
//    // Remove destroyed particles
//    renderParticles.erase(
//        std::remove_if(renderParticles.begin(), renderParticles.end(),
//            [](RenderParticle* rp) {
//                if (rp->particle->IsDestroyed()) {
//                    delete rp;
//                    return true;
//                }
//                return false;
//            }),
//        renderParticles.end()
//    );
//}

void FountainDemo::Update(float deltaTime) {
    spawnTimer += deltaTime;

    // Spawn new sparks if under max count
    while (renderParticles.size() < maxSparks && spawnTimer >= spawnCooldown) {
        spawnTimer = 0.0f;

        // Create new particle
        P6::P6Particle* spark = new P6::P6Particle(0, 0, 0);


        // Position: elevated near bottom (e.g., y = 2.0)
        spark->Position = P6::MyVector(0, -320.0f, 0); // You can randomize X/Z for spread if desired

        // Velocity: spray effect
        spark->Velocity = P6::MyVector(
            (rand() % 200 - 100) / 100.0f, // X: -1 to 1
            (rand() % 200) / 100.0f + 4.0f, // Y: 4 to 6 m/s upward
            (rand() % 200 - 100) / 100.0f  // Z: -1 to 1
        );

        // Lifespan: 1 to 10 seconds
        float lifespan = 1.0f + static_cast<float>(rand() % 900) / 100.0f; // 1.0 to 10.0
		std::cout << "Lifespan: " << lifespan << std::endl;
        spark->SetLifespan(lifespan);

        // Radius: 2m to 10m
        float radius = 2.0f + static_cast<float>(rand() % 800) / 100.0f; // 2.0 to 10.0

      

        //setSizeArea
       // sparkModel->setScale(glm::vec3(radius, radius, radius));
        //test


        // Mass and damping
        spark->mass = 1.0f;
        
        //  Initial spray force
        P6::MyVector sprayForce(
			(rand() % 200 - 100) * 100,         // X: -100 to 100 N * 1000 for larger force
            ((rand() % 200) + 300) * 100,         // Y: 300 to 500 N
            (rand() % 2000 - 1000)          // Z: -100 to 100 N
        );
        spark->AddForce(sprayForce);
       
        std::cout << "Spray force: X=" << sprayForce.x << std::endl;

        // Add to world
        world->AddParticle(spark);

        // Random color (RGB each 0.0ÅE.0)
        P6::MyVector color(
            static_cast<float>(rand() % 100) / 100.0f,
            static_cast<float>(rand() % 100) / 100.0f,
            static_cast<float>(rand() % 100) / 100.0f
        );

        // Create render particle and store
        RenderParticle* renderP = new RenderParticle(spark, sparkModel, color,radius);
        renderParticles.push_back(renderP);
    }

    // Remove dead particles
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

void FountainDemo::Render(Shader* shaderProg, GLuint* VAO, std::vector<GLfloat>* vertexData, GLuint* tex, std::string name) {
    for (auto* rp : renderParticles) {
        rp->Draw(shaderProg, VAO, vertexData, tex, name);
    }
}

FountainDemo::~FountainDemo() {
    for (auto* rp : renderParticles) {
        delete rp;
    }
}