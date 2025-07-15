//This implementation simulates a bungee by letting the particle to move freely and adds no force if the particle
//is within the bungee's rest length. But if the particle is beyond the bungee's rest length it applies a restoring force.
//The restoring force applied is a spring like force that pulls the particle towards the anchor point. The stretch is the 
//computation of how much the particle is beyond the bungee's rest length which is then multiplied to spring constant to 
//get the restoring force.

#include "Bungee.h"

namespace P6 {
	void Bungee::UpdateForce(P6Particle* particle, float time)
	{
		MyVector pos = particle->Position;
		MyVector force = pos - anchorPoint;
		float mag = force.magnitude();

		if (mag <= restLength) //If the particle is not beyond the rest length of the bungee no force is applied
		{
			return;
		}

		float stretch = mag - restLength;

		float springForce = -springConstant * stretch;

		force = force.normalize();
		force = force * springForce;
		particle->AddForce(force);
	}
}