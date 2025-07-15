#pragma once
#include "ParticleLink.h"

using namespace P6;

class Rod : public ParticleLink
{
	public: 
		float length = 1;
		float restitution = 0;
		ParticleContact* GetContact() override;
};

