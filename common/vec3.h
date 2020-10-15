/* ==================================================================
 * SET10110 - ADVANCED GAMES ENGINEERING
 *
 * GRAEME B. WHITE - 40415739
 *
 * DATE OF CREATION: 10/10/2020
 * DATE LAST MODIFIED: 12/10/2020
 * ==================================================================
 * PATH-TRACING PROTOTYPE
 *
 * Prototype version of the path-tracer developed for SET10110 -
 * Advanced Games Engineering.
 *
 * Work is based on the path tracer developed in "Ray Tracing in one
 * Weekend" by P. Shirley - https://raytracing.github.io/
 *
 * ==================================================================
 * VEC3 CLASS AND FUNCTIONS
 * 
 * Allows a vector consisting of 3 components to be created.
 * 
 * File contains the vec3 class, class functions, type aliases, and
 * utility functions associated with vec3
 */

// Declare ifndef directive for VEC3_H
#ifndef VEC3_H

// Define VEC3_H
#define VEC3_H

// Header files
#include <cmath>
#include <iostream>

// Namespace
using std::sqrt;

/* ==================================================================
 * VEC3 CLASS
 * 
 * Class for a vector consisting of 3 
 * components: x, y, and z.
 * 
 * Has all the functions for creating a
 * vector, carrying out operations on a vector,
 * and returning values from a vector 
 * ==================================================================
 */
class vec3
{
	// Public functions
	public:
		/*
		 * DEFAULT VEC3 CONSTRUCTOR
		 * 
		 * When invoked, creates a vector where X, Y, 
		 * and Z components are all set to 0.0f
		 */
		vec3() : 
			_xyz{ 0.0f, 0.0f, 0.0f } {}

		/*
		 * VEC3 CONSTRUCTOR
		 *
		 * When invoked, creates a vector where X, Y,
		 * and Z components are all set to defined
		 * values from the arguments
		 */
		vec3(float x, float y, float z) : 
			_xyz{ x, y, z } {}

		/*
		 * GET X FUNCTION
		 * 
		 * Function returns the value of the X component
		 */
		float getX() const 
		{
			// Return the X component value
			return _xyz[0]; 
		}

		/*
		 * GET Y FUNCTION
		 * 
		 * Function returns the value of the Y component
		 */
		float getY() const 
		{ 
			// Return the Y component value
			return _xyz[1]; 
		}

		/*
		 * GET Z FUNCTION
		 * 
		 * Function returns the value of the Z component
		 */
		float getZ() const 
		{ 
			// Return the Z component value
			return _xyz[2]; 
		}

		/*
		 * INVERSE VECTOR OPERATIOR
		 *
		 * When invoked, the signs of all the values in
		 * the vector are inverted, e.g. positive value
		 * becomes negative and vice versa.
		 */
		vec3 operator-() const 
		{ 
			// Return the inverted vector
			return vec3(-_xyz[0], -_xyz[1], -_xyz[2]); 
		}

		/*
		 * GET VALUE AT ELEMENT OPERATOR
		 *
		 * When invoked, operator returns the value of the 
		 * element at index i
		 */
		float operator[](int i) const 
		{ 
			// Return the value at index i
			return _xyz[i]; 
		}

		/*
		 * GET VALUE AT ELEMENT OPERATOR
		 *
		 * When invoked, operator returns the value of the
		 * element at index i
		 */
		float& operator[](int i) 
		{ 
			// Return the value at index i
			return _xyz[i]; 
		}

		/*
		 * ADDITION OPERATOR
		 * 
		 * Operator adds the X, Y, and Z components of
		 * a vector, to the X, Y, and Z components of 
		 * this vector, then returns this vector
		 */
		vec3& operator+=(const vec3& v) 
		{
			// Add X components
			_xyz[0] += v._xyz[0];

			// Add Y components
			_xyz[1] += v._xyz[1];

			// Add Z components
			_xyz[2] += v._xyz[2];

			// Return this vector
			return *this;
		}

		/*
		 * MULTIPLY OPERATOR
		 *
		 * Operator multiplies the X, Y, and Z
		 * components of this vector by a defined 
		 * scalar, then returns this vector
		 */
		vec3& operator*=(const float s)
		{
			// Add X components
			_xyz[0] *= s;

			// Add Y components
			_xyz[1] *= s;

			// Add Z components
			_xyz[2] *= s;

			// Return this vector
			return *this;
		}

		/*
		 * DIVISION OPERATOR
		 *
		 * Operator divides the X, Y, and Z
		 * components of this vector by a defined
		 * scalar, then returns this vector
		 */
		vec3& operator/=(const float s)
		{
			// Determine and return the divided vector
			return *this *=1/s;
		}

		/*
		 * LENGTH FUNCTION
		 *
		 * Function returns the length of a vector
		 */
		float length() const
		{
			// Return the length, by taking the square root of the squared length
			return sqrt(lengthSquared());
		}

		/*
		 * LENGTH SQUARED FUNCTION
		 * 
		 * Funtion determines the squared length of a 
		 * vector 
		 */
		float lengthSquared() const
		{
			// Determine the length squared via pythagoras theorem
			float length = (_xyz[0] *_xyz[0]) + (_xyz[1] * _xyz[1]) + (_xyz[2] * _xyz[2]);
			
			// Return length
			return length;
		}

		/*
		 * RANDOM FUNCTION
		 *
		 * Funtion creates a vector where each component
		 * has random values between 0 and 1
		 */
		inline static vec3 random() 
		{
			// Return vector with random values
			return vec3(randomFloat(), randomFloat(), randomFloat());
		}

		/*
		 * RANDOM VECTOR FUNCTION
		 *
		 * Funtion creates a vector where each component
		 * has random values between a specified maximum
		 * and minimum value
		 */
		inline static vec3 randomVector(double min, double max)
		{
			// Return vector with random values between a set range
			return vec3(randomFloat(min, max), randomFloat(min, max), randomFloat(min, max));
		}

	// Private
	private:
		// XYZ component array
		float _xyz[3];
};

/* ==================================================================
 * TYPE ALIASES
 *
 * Type aliases for the vec3 class
 * ==================================================================
 */

// 3D Point
using point3 = vec3;

// RGB Colour Value
using colour = vec3;

/* ==================================================================
 * VEC3 UTILITY FUNCTIONS
 *
 * Utility functions
 * ==================================================================
 */

 /*
  * LEFT SHIFT OPERATOR
  * 
  * Operator returns the X, Y, and Z values to an output stream
  */
inline std::ostream& operator<<(std::ostream& out, const vec3& vec) 
{
	// Return the output stream containing the vector information
	return out << vec.getX() << ' ' << vec.getY() << ' ' << vec.getZ();
}

/*
 * ADDITION OPERATOR
 *
 * Operator allows the values of two vectors to be added and the value
 * of the new vector is returned as a new vector
 */
inline vec3 operator+(const vec3& vec1, const vec3& vec2) 
{
	// Determine and return the result of the addition of both vectors
	return vec3((vec1.getX() + vec2.getX()), 
		(vec1.getY() + vec2.getY()), 
		(vec1.getZ() + vec2.getZ()));
}

/*
 * SUBTRACTION OPERATOR
 *
 * Operator allows the values of two vectors to be subtracted and the value
 * of the new vector is returned as a new vector
 */
inline vec3 operator-(const vec3& vec1, const vec3& vec2)
{
	// Determine and return the result of the subtraction of both vectors
	return vec3((vec1.getX() - vec2.getX()), 
		(vec1.getY() - vec2.getY()), 
		(vec1.getZ() - vec2.getZ()));
}

/*
 * MULTIPLY OPERATOR
 *
 * Operator allows the values of two vectors to be multiplied and the value
 * of the new vector is returned as a new vector
 */
inline vec3 operator*(const vec3& vec1, const vec3& vec2)
{
	// Determine and return the result of the multiplication of both vectors
	return vec3((vec1.getX() * vec2.getX()), 
		(vec1.getY() * vec2.getY()), 
		(vec1.getZ() * vec2.getZ()));
}

/*
 * MULTIPLY OPERATOR
 *
 * Operator allows a vector to be multiplied by a scalar and returns
 * the value of the new vector
 */
inline vec3 operator*(float s, const vec3& vec) 
{
	// Determine and return the value of the vector multiplied by the scalar
	return vec3(s * vec.getX(), 
		s * vec.getY(), 
		s * vec.getZ());
}

/*
 * MULTIPLY OPERATOR
 *
 * Operator allows a vector to be multiplied by a scalar and returns
 * the value of the new vector
 */
inline vec3 operator*(const vec3& vec, float s)
{
	// Determine and return the value of the vector multiplied by the scalar
	return s * vec;
}

/*
 * DIVIDE OPERATOR
 *
 * Operator allows a vector to be divided by a scalar and returns
 * the value of the new vector
 */
inline vec3 operator/(vec3 vec, float s)
{
	// Determine and return the value of the vector multiplied by the scalar
	return (1/s) * vec;
}

/*
 * DOT PRODUCT FUNCTION
 *
 * Function determines the dot product of two vectors
 * and returns the value
 */
inline float dot(const vec3& vec1, const vec3& vec2) 
{
	// Determine and return the value of the dot product
	return vec1.getX() * vec2.getX()
		+ vec1.getY() * vec2.getY()
		+ vec1.getZ() * vec2.getZ();
}

/*
 * CROSS PRODUCT FUNCTION
 *
 * Function determines the cross product of two vectors
 * and returns the value
 */
inline vec3 cross(const vec3& vec1, const vec3& vec2) 
{
	// Determine and return the value of the cross product
	return vec3(
		// X component of cross product
		vec1.getY() * vec2.getZ() - vec1.getZ() * vec2.getY(),

		// Y component of cross product
		vec1.getZ() * vec2.getX() - vec1.getX() * vec2.getZ(),

		// Z component of cross product
		vec1.getX() * vec2.getY() - vec1.getY() * vec2.getX());
}

/*
 * UNIT VECTOR FUNCTION
 * 
 * Funtion determines the unit vector and returns the value
 */
inline vec3 unitVector(vec3 vec) 
{
	// Determine and return the unit vector
	return vec / vec.length();
}

/*
 * RANDOM IN UNIT SPHERE FUNCTION
 *
 * Funtion picks a random point and determines if it is
 * within a unit sphere
 */
vec3 randomInUnitSphere()
{
	// While loop
	while (true) 
	{
		// Obtain random point between -1 and 1
		auto p = vec3::randomVector(-1, 1);

		// Check if point is in the unit sphere
		if (p.lengthSquared() >= 1)
		{
			// Point is not in the sphere, reject the point and continue
			continue;
		}

		// Return the value of P
		return p;
	}
}

/*
 * RANDOM UNIT VECTOR FUNCTION
 * 
 * Function returns a random unit vector
 */
vec3 randomUnitVector() 
{
	// Obtain random vector with values between 0 and 2*pi
	auto a = randomFloat(0, 2 * pi);

	// Obtain random vector with values between -1 and 1
	auto z = randomFloat(-1, 1);

	// Determine r
	auto r = sqrt(1 - z * z);

	// Return Unit Vector
	return vec3(r * cos(a), r * sin(a), z);
}

/*
 * RANDOM IN HEMISPHERE FUNCTION
 *
 * Function returns a random vector from 
 * hemisphere
 */
vec3 randomInHemisphere(const vec3& normal) 
{
	// Obtain random vector from sphere
	vec3 inUnitSphere = randomInUnitSphere();

	// Check if random vector is in the same hemisphere as the normal
	if (dot(inUnitSphere, normal) > 0.0)
	{
		// In the same hemisphere, return the random vector
		return inUnitSphere;
	}
	else
	{
		// Not in the same hemisphere, return the inverse of the random vector
		return -inUnitSphere;
	}
}

/*
 * REFLECT FUNCTION
 *
 * Function used to determine the reflected
 * vector
 */
vec3 reflect(const vec3& v, const vec3& n) 
{
	// Determine and return the reflected vector
	return v - 2 * dot(v, n) * n;
}

/*
 * REFRACT FUNCTION
 * 
 * Function based on Snell's law to produce a 
 * refracted vector
 */
vec3 refract(const vec3& uv, const vec3& n, float eta1DivEta2)
{
	// Determine angle between vector and normal
	auto cosTheta = dot(-uv, n);

	// Determine the vector perpendicular to the refracted normal
	vec3 rOutPerpendicular = eta1DivEta2 * (uv + cosTheta * n);

	// Determine the parallel component of the refracted normal
	vec3 rOutParallel = -sqrt(fabs(1.0 - rOutPerpendicular.lengthSquared())) * n;

	// Determine and return the refracted vector
	return rOutPerpendicular + rOutParallel;
}

// End ifndef directive for VEC3_H
#endif