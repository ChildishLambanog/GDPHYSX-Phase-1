#include "ParticleContact.h"

namespace P6 {
	float ParticleContact::GetSeparatingSpeed()
	{
		MyVector velocity = particles[0]->Velocity;

		if (particles[1])
		{
			velocity -= particles[1]->Velocity;
		}

		return velocity.dotProduct(contactNormal); //check if this is the right function
	}

	void ParticleContact::Resolve(float time)
	{
		ResolveVelocity(time);
		ResolveInterpenetration(time);
	}

	void ParticleContact::ResolveVelocity(float time)
	{
		float separatingSpeed = GetSeparatingSpeed();

		if (separatingSpeed > 0) //If SS > 0 then its already moving away so ignore
		{
			return;
		}

		float newSS = -restitution * separatingSpeed;
		float deltaSpeed = newSS - separatingSpeed;

		float totalMass = (float)1 / particles[0]->mass;

		if (particles[1])
		{
			totalMass += (float)1 / particles[1]->mass;
		}

		if (totalMass <= 0)
		{
			return;
		}

		float impulseMag = deltaSpeed / totalMass;
		MyVector Impulse = contactNormal * impulseMag;

		MyVector v_A = Impulse * ((float)1 / particles[0]->mass);
		particles[0]->Velocity = particles[0]->Velocity + v_A;

		if (particles[1])
		{
			MyVector v_B = Impulse * ((float)-1 / particles[1]->mass);
			particles[1]->Velocity = particles[1]->Velocity + v_B;
		}
	}

	void ParticleContact::ResolveInterpenetration(float time)
	{
		if (depth <= 0)
		{
			return;
		}

		float totalMass = (float)1 / particles[0]->mass;

		if (particles[1])
		{
			totalMass += (float)1 / particles[1]->mass;
		}

		if (totalMass <= 0)
		{
			return;
		}

		float totalMoveByMass = depth / totalMass;
		MyVector moveByMass = contactNormal * totalMoveByMass;

		MyVector P_a = moveByMass * ((float)1 / particles[0]->mass);
		particles[0]->Position += P_a;

		if (particles[1])
		{
			MyVector P_b = moveByMass * (-(float)1 / particles[1]->mass);
			particles[1]->Position += P_b;
		}

		depth = 0;
	}
}