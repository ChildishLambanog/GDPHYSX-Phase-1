#pragma once
#include "MyVector.h"

namespace P6 {
	class P6Particle {
	public:
		float radius = 1.0f; //Radius of the particle in meters
		float restitution = 1.0f; //How bouncy the particle is ranges from 0-1


		float mass = 1;
		float finishFlag = -1.0f; //new addition
		MyVector Position;
		MyVector Velocity;
		MyVector Acceleration;

		float damping = 0.9f; //Approximate drag 0.9f

		P6Particle(float x, float y, float z) : Position(x, y, z), Velocity(0, 0, 0), Acceleration(0, 0, 0) {}
	protected:
		void UpdatePosition(float time);
		void UpdateVelocity(float time);
	protected:
		bool isDestroyed = false;
		MyVector accumulatedForce = MyVector(0, 0, 0);

	public:
		void AddForce(MyVector force);
		void ResetForce();
		void Update(float time);
		void Destroy();
		bool IsDestroyed() { return isDestroyed; }
			//For Phase 1:
		protected:
			float lifespan = 5.0f; // default lifespan in seconds
		public:
			void SetLifespan(float time) { lifespan = time; }
			float GetLifespan() const { return lifespan; }
	};
}
