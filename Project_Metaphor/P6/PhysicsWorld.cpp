#include "PhysicsWorld.h"

void P6::PhysicsWorld::AddParticle(P6Particle* toAdd)
{
	this->Particles.push_back(toAdd);
	forceRegistry.Add(toAdd, &Gravity);
	//forceRegistry.Add(toAdd, &spray);

}

void P6::PhysicsWorld::Update(float time)
{
	UpdateParticleList(); 

	forceRegistry.UpdateForces(time);

	for (std::list<P6Particle*>::iterator p = Particles.begin(); p != Particles.end(); p++)
	{
		(*p)->Update(time);
	}
}

void P6::PhysicsWorld::UpdateParticleList()
{
	Particles.remove_if([](P6Particle* p){ return p->IsDestroyed(); });
}
