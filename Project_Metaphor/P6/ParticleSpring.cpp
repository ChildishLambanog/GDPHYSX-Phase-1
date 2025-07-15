#include "ParticleSpring.h"

void ParticleSpring::UpdateForce(P6Particle* particle, float time)
{
	MyVector pos = particle->Position;

	MyVector force = pos - otherParticle->Position;
	float mag = force.magnitude();
	float springForce = -springConstant * abs(mag - restLength);
	force = force.normalize();
	force = force * springForce;
	particle->AddForce(force);
}
