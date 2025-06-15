#pragma once
#include <list>
#include "P6Particle.h"

#include "ForceRegistry.h"
#include "GravityForceGenerator.h"
#include "RandomSprayForceGenerator.h"

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
			GravityForceGenerator Gravity = GravityForceGenerator(MyVector(0, -980.f, 0)); //0, -9.8f, 0
			//P6::RandomSprayForceGenerator spray = P6::RandomSprayForceGenerator(500.0f, 10000.0f, 200.0f);
	};
}


