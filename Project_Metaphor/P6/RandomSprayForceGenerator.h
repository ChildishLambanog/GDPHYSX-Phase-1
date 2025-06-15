
#ifndef FORCEGENERATOR_DEF
#define FORCEGENERATOR_DEF

#include "ForceGenerator.h"
#endif // !RSPFORCEGENERATOR
#include <cstdlib> // for rand()
#include <ctime>   // for seeding
namespace P6 {
	class RandomSprayForceGenerator : public ForceGenerator
	{
	private:
		float minForce;
		float maxForce;
		float sidewaysVariance;

		// Helper function to get random float between two values
		float RandomRange(float min, float max);

	public:
		RandomSprayForceGenerator(float minF, float maxF, float variance);

		void UpdateForce(P6Particle* particle, float time) override;
	};
}
