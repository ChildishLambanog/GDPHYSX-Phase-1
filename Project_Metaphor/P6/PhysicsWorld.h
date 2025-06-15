#pragma once
#include <list>
#include "P6Particle.h"

#include "ForceRegistry.h"
#include "GravityForceGenerator.h"

namespace P6 {
	class PhysicsWorld
	{
		public:
			ForceRegistry forceRegistry;

			std::list<P6Particle*> Particles;

			void AddParticle(P6Particle* toAdd);
			void Update(float time);
		private:
			void UpdateParticleList();
			GravityForceGenerator Gravity = GravityForceGenerator(MyVector(0, 0, 0)); //0, -9.8f, 0
	};
}


