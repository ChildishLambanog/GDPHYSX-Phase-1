#pragma once
#include "ParticleContact.h"
using namespace P6;

class ParticleLink
{
	public:
		P6Particle* particles[2];
		virtual ParticleContact* GetContact() { return nullptr; };
	protected:
		float CurrentLength();
};

