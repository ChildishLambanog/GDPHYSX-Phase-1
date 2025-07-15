#pragma once
#ifndef FORCEGENERATOR_DEF
#define FORCEGENERATOR_DEF
#include "ForceGenerator.h"
#endif
#include "MyVector.h"

namespace P6
{
class Chain : public ForceGenerator
{
	private:
		MyVector anchorPoint; //Point where the particle is anchored
		float restLength;	  //Maximum length of the chain
	public:
		Chain(MyVector pos, float _restLen) :
			anchorPoint(pos), restLength(_restLen) {}

		void UpdateForce(P6Particle* particle, float time) override;
};
}
