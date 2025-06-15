#pragma once
#include "MyVector.h"

namespace P6 {
	class P6Particle {
		public:
			float mass = 1;
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
			MyVector accumulatedForce = MyVector(0, 0, 0); //this is the force gathered b4 FixedUpdate

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
