#include "DragForceGenerator.h"

void P6::DragForceGenerator::UpdateForce(P6Particle* particle, float time)
{
	MyVector force = MyVector(0, 0, 0);
	MyVector currV = particle->Velocity;

	float mag = currV.magnitude();
	if (mag <= 0.0f) return; //no drag if no velocity

	float dragF = (k1 * mag) + (k2 * mag);
	MyVector dir = currV.normalize(); //make normalize();
	particle->AddForce(dir * -dragF);
}
