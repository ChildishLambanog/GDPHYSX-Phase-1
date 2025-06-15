#include "RandomSprayForceGenerator.h"
P6::RandomSprayForceGenerator::RandomSprayForceGenerator(float minF, float maxF, float variance)
	: minForce(minF), maxForce(maxF), sidewaysVariance(variance)
{
	std::srand(static_cast<unsigned int>(std::time(nullptr))); // seed once
}

float P6::RandomSprayForceGenerator::RandomRange(float min, float max)
{
	float scale = rand() / (float)RAND_MAX;
	return min + scale * (max - min);
}

void P6::RandomSprayForceGenerator::UpdateForce(P6Particle* particle, float time)
{
	if (particle->mass <= 0) return;

	// Upward force (Y) between minForce and maxForce
	float upward = RandomRange(minForce, maxForce);

	// Slight random force on X and Z for sideways spray
	float sideX = RandomRange(-sidewaysVariance, sidewaysVariance);
	float sideZ = RandomRange(-sidewaysVariance, sidewaysVariance);

	MyVector force(sideX, upward, sideZ);
	particle->AddForce(force);
}