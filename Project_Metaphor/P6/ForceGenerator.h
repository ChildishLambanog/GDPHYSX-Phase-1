#ifndef P6PARTICLE_DEF
#define P6PARTICLE_DEF

#include "P6Particle.h"

#endif
namespace P6 {
	class ForceGenerator
	{
	public:
		virtual void UpdateForce(P6Particle* p, float time)
		{
			p->AddForce(MyVector(0, 0, 0));
		}
	};
}


