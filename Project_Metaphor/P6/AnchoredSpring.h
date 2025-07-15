#pragma once
#include "ForceGenerator.h"
#include "MyVector.h"

using namespace P6;

class AnchoredSpring : public ForceGenerator
{
	private:
		MyVector anchorPoint;
		float springConstant;
		float restLength;
	public:
		AnchoredSpring(MyVector pos, float _springConst, float _restLen) :
			anchorPoint(pos), springConstant(_springConst), restLength(_restLen) {}

		void UpdateForce(P6Particle* particle, float time) override;
};

