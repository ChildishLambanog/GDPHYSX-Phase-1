#pragma once
#include "ForceGenerator.h"
#include "MyVector.h"
#include "P6Particle.h"

using namespace P6;

class ParticleSpring : public ForceGenerator
{
	private: 
		P6Particle* otherParticle;
		float springConstant;
		float restLength;
	public:
		ParticleSpring(P6Particle* particle, float _springConst, float _restLen) :
			otherParticle(particle), springConstant(_springConst), restLength(_restLen) {}
		void UpdateForce(P6Particle* particle, float time) override;
};

