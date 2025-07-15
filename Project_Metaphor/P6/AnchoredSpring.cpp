#include "AnchoredSpring.h"

void AnchoredSpring::UpdateForce(P6Particle* particle, float time)
{
	MyVector pos = particle->Position;
	MyVector force = pos - anchorPoint;
	float mag = force.magnitude();

	float springForce = -springConstant * abs(mag - restLength);

	force = force.normalize();
	force = force * springForce;
	particle->AddForce(force);
}
