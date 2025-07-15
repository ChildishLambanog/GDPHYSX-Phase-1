//This implementation simulates a chain because it lets the particle to move within the chain's rest length where it computes 
//if whether the particle is within the chain's rest length. If the particle is within the chain's rest length it will not
//apply any force and let the particle move freely. But if the particle is beyond the chain's rest length it clamps the 
//particle to the end of the chain's rest length.

#include "Chain.h"
namespace P6 {
	void Chain::UpdateForce(P6Particle* particle, float time)
	{
		MyVector pos = particle->Position;
		MyVector force = pos - anchorPoint;
		float mag = force.magnitude();

		if (mag <= restLength) //If the particle is within the chain's rest length do nothing
		{
			return;
		}

		MyVector direction = force.normalize();
		particle->Position = anchorPoint + (direction * restLength);
	}
}