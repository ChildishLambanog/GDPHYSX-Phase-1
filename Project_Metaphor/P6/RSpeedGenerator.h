#pragma once
#ifndef FORCEGENERATOR_DEF
#define FORCEGENERATOR_DEF
#include "ForceGenerator.h"
#endif
#include <cstdlib>
#include <ctime>
#include <iostream>

namespace P6 {
	class RSpeedGenerator : public ForceGenerator
	{

	
		private:
			float randAccel;
			bool triggered = false; // if pass the 60% mark

			float startPoint = -800; // generator reference on particle start
			float boosty = 0.0f; // boost speed on the 60% mark
			int multiplier = 100;
		public:
			RSpeedGenerator(int AccelPoint) 
			{	
				this->randAccel = AccelPoint;
				this->randAccel *= multiplier; // scale the random acceleration
			}
			float getBoost() const
			{

				srand(time(0));

				float mx = 8.0f,
					mn = 1.1f;
				int bRes = std::abs( (int)mn - std::rand() % (int)(mx - mn + 1));

				return (bRes == 0) ? 1 : bRes;
			}
			void UpdateForce(P6Particle* particle, float time) override;
			
		

	};
}

