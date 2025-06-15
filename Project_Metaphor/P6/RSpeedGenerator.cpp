#include "RSpeedGenerator.h"

void P6::RSpeedGenerator::UpdateForce(P6Particle* particle, float time)
{

	if (particle->mass <= 0) return;

	if (particle->Position.x - startPoint >= 600 && triggered == false)
	{
		triggered = true; // mark as triggered
		boosty = getBoost(); // get the boost value
		randAccel *= boosty; // apply the boost to the random acceleration
		 // apply the boost force
	
		//particle->AddForce(MyVector(randAccel,0,0) * particle->mass);
	}
	
	particle->AddForce(MyVector(randAccel,0,0) * particle->mass);
	
}

