#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace P6 {
	class MyVector {
		public:
		float x, y, z;

		//Default Constructor
		MyVector() : x(0), y(0), z(0) {}

		//Component Contructor
		MyVector(const float _x, const float _y, const float _z) : x(_x), y(_y), z(_z) {}

		explicit operator glm::vec3() const { return glm::vec3(x, y, z);}

		MyVector operator+ (const MyVector rhs)
		{
			MyVector sum(this->x + rhs.x, this->y + rhs.y, this->z + rhs.z);
			return sum;
		}

		MyVector operator- (const MyVector rhs)
		{
			MyVector diff(this->x - rhs.x, this->y - rhs.y, this->z - rhs.z);
			return diff;
		}

		MyVector operator* (const MyVector rhs) //Component Product
		{
			MyVector compProd(this->x * rhs.x, this->y * rhs.y, this->x * rhs.z);
			return compProd;
		}

		MyVector operator* (float scalar) //Scalar Multiplication
		{
			MyVector scalarMulti(this->x * scalar, this->y * scalar, this->z * scalar);
			return scalarMulti;
		}

		void operator+= (const MyVector rhs);
		void operator-= (const MyVector rhs);
		void operator*= (const MyVector rhs); //Component Product
		void operator*= (float scalar); //Scalar Multiplication
		float dotProduct (const MyVector rhs) const; //Scalar Product
		MyVector cross(const MyVector rhs) const; //Vector Product
		float magnitude() const;
		MyVector direction() const;
		MyVector normalize();
	};
}