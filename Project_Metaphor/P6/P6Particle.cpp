#include "P6Particle.h"

void P6::P6Particle::UpdatePosition(float time)
{
	//Position += (Velocity * time);
	this->Position += (this->Velocity * time) + ((this->Acceleration * time * time) * (1.0f / 2.0f));
}

void P6::P6Particle::Update(float time)
{
	this->UpdatePosition(time);
	this->UpdateVelocity(time);

	this->ResetForce();
}

void P6::P6Particle::UpdateVelocity(float time)
{
	this->Acceleration += accumulatedForce * (1.0f / mass);
	this->Velocity += (this->Acceleration * time);
	this->Velocity *= powf(damping, time); //Apply damping
}

void P6::P6Particle::Destroy()
{
	this->isDestroyed = true;
}

void P6::P6Particle::AddForce(MyVector force)
{
	this->accumulatedForce += force;
}

void P6::P6Particle::ResetForce()
{
	this->accumulatedForce = MyVector(0, 0, 0);
	this->Acceleration = MyVector(0, 0, 0);
}