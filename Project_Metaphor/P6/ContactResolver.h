#pragma once
#ifndef P6CONTACT_DEF
#define P6CONTACT_DEF

#include "ParticleContact.h"
#endif

#include <Vector>
#include <list>

namespace P6 
{
	class ContactResolver
	{
		public:
			unsigned int max_iterations;
			ContactResolver(unsigned _maxIterations) : max_iterations(_maxIterations) {}
			void ResolveContacts(std::vector<ParticleContact*> contacts, float time);

		protected:
			unsigned int current_iteration = 0;
			

	};
}