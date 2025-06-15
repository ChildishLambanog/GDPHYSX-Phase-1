#include "MyVector.h"
#include <cmath>

namespace P6 {

	void MyVector::operator+= (const MyVector rhs)
	{
		this->x += rhs.x;
		this->y += rhs.y;
		this->z += rhs.z;
	}

	void MyVector::operator-= (const MyVector rhs)
	{
		this->x -= rhs.x;
		this->y -= rhs.y;
		this->z -= rhs.z;
	}

	void MyVector::operator*= (const MyVector rhs) //Component Product
	{
		this->x *= rhs.x;
		this->y *= rhs.y;
		this->z *= rhs.z;
	}

	void MyVector::operator*= (float scalar) //Scalar Multiplication
	{
		this->x *= scalar;
		this->y *= scalar;
		this->z *= scalar;
	}

	float MyVector::dotProduct(const MyVector rhs) const
	{
		return ((this->x * rhs.x) + (this->y * rhs.y) + (this->z * rhs.z));
	}

	MyVector MyVector::cross(const MyVector rhs) const
	{
		return MyVector(
			(this->y * rhs.z) - (this->z * rhs.y),
			(this->z * rhs.x) - (this->x * rhs.z),
			(this->x * rhs.y) - (this->y * rhs.x)
		);
	}

	float MyVector::magnitude() const
	{
		return std::sqrt(
			(this->x * this->x) +
			(this->y * this->y) +
			(this->z * this->z)
		);
	}

	MyVector MyVector::direction() const
	{
		float magnitude = this->magnitude();
		
		if (magnitude == 0)
		{
			return MyVector(0, 0, 0);
		}

		else
		{
			return MyVector(
				this->x / magnitude,
				this->y / magnitude,
				this->z / magnitude
			);
		}
	}


	MyVector MyVector::normalize()
	{
		float magnitude = this->magnitude();

		if (magnitude == 0)
		{
			return MyVector(0, 0, 0);
		}

		else
		{
			return MyVector(
				this->x / magnitude,
				this->y / magnitude,
				this->z / magnitude
			);
		}
	}
}