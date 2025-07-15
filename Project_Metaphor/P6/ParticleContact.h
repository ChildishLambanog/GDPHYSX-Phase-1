#pragma once
#ifndef P6PARTICLE_DEF
#define P6PARTICLE_DEF

#include "P6Particle.h"

#endif

namespace P6
{
	class ParticleContact
	{
		public:
			P6Particle* particles[2];
			float restitution;
			MyVector contactNormal;
			void Resolve(float time);
			float depth; //new addition
			float GetSeparatingSpeed();
		protected:
			void ResolveVelocity(float time);
			void ResolveInterpenetration(float time);
	};
}