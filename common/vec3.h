/* ==================================================================
 * SET10110 - ADVANCED GAMES ENGINEERING
 *
 * GRAEME B. WHITE - 40415739
 *
 * DATE OF CREATION: 10/10/2020
 * DATE LAST MODIFIED: 11/10/2020
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
			xyz{ 0.0f, 0.0f, 0.0f } {}

		/*
		 * VEC3 CONSTRUCTOR
		 *
		 * When invoked, creates a vector where X, Y,
		 * and Z components are all set to defined
		 * values from the arguments
		 */
		vec3(float x, float y, float z) : 
			xyz{ x, y, z } {}

		/*
		 * GET X FUNCTION
		 * 
		 * Function returns the value of the X component
		 */
		float getX() const 
		{
			// Return the X component value
			return xyz[0]; 
		}

		/*
		 * GET Y FUNCTION
		 * 
		 * Function returns the value of the Y component
		 */
		float getY() const 
		{ 
			// Return the Y component value
			return xyz[1]; 
		}

		/*
		 * GET Z FUNCTION
		 * 
		 * Function returns the value of the Z component
		 */
		float getZ() const 
		{ 
			// Return the Z component value
			return xyz[2]; 
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
			return vec3(-xyz[0], -xyz[1], -xyz[2]); 
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
			return xyz[i]; 
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
			return xyz[i]; 
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
			xyz[0] += v.xyz[0];

			// Add Y components
			xyz[1] += v.xyz[1];

			// Add Z components
			xyz[2] += v.xyz[2];

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
			xyz[0] *= s;

			// Add Y components
			xyz[1] *= s;

			// Add Z components
			xyz[2] *= s;

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
			float length = (xyz[0] * xyz[0]) + (xyz[1] * xyz[1]) + (xyz[2] * xyz[2]);
			
			// Return length
			return length;
		}

	// Private
	private:
		// XYZ component array
		float xyz[3];
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
	return vec3(vec1.getY() * vec2.getZ() - vec1.getZ() * vec1.getY(),
		vec1.getZ() * vec2.getX() - vec1.getX() * vec2.getZ(),
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

// End ifndef directive for VEC3_H
#endif VEC3_H