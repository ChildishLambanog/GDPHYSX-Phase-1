
#pragma once
#ifndef FORCEGENERATOR_DEF
#define FORCEGENERATOR_DEF
#include "ForceGenerator.h"
#endif
#include <cstdlib>

#include <iostream>
#include "MyVector.h"

namespace P6
{

	class Bungee : public ForceGenerator
	{
	private:
		MyVector anchorPoint; //Point where the particle is anchored
		float springConstant; //Spring constant of the bungee
		float restLength;     //Maximum length of the bungee
	public:
		Bungee(MyVector pos, float _springConst, float _restLen) :
			anchorPoint(pos), springConstant(_springConst), restLength(_restLen) {}

		void UpdateForce(P6Particle* particle, float time) override;
	};
}
