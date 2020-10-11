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
 * RAY CLASS AND FILES
 *
 * Header file contains the public functions and private variables
 * for constructing a ray object
 */

// Declare ifndef directive for RAY_H
#ifndef RAY_H

// Define RAY_H
#define RAY_H

// Header files
#include "vec3.h"

/* ==================================================================
 * RAY CLASS
 * 
 * Class contains the functions and variables related to the ray
 * class
 * ==================================================================
 */
class ray
{
	// Public functions
	public:
		/*
		 * DEFAULT RAY CONSTRUCTOR
		 * 
		 * When invoked, creates an empty ray object
		 */
		ray() {}

		/*
		 * RAY CONSTRUCTOR
		 * 
		 * Function takes in an origin and direction vectors,
		 * then sets the origin and direction variables of the
		 * ray
		 */
		ray(const point3& origin, const vec3& direction) 
		 :orig(origin), dir(direction) {}

		/*
		 * GET ORIGIN FUNCTION
		 *
		 * Function returns the origin of the ray
		 */
		point3 getOrigin() const
		{
			// Return the origin point
			return orig;
		}

		/*
		 * GET ORIGIN FUNCTION
		 *
		 * Function returns the direction of the ray
		 */
		vec3 getDirection() const
		{
			// Return the direction of the ray
			return dir;
		}

		/*
		 * AT FUNCTION
		 *
		 * Function returns the ray's position
		 * at ray parameter, t
		 */
		point3 at(float t) const
		{
			// Determine and return the ray's position at ray parameter t
			return orig + t * dir;
		}

	// Private variables
	private:

		// Ray point of origin
		point3 orig;

		// Ray direction
		vec3 dir;
};

// End ifndef directive for RAY_H
#endif RAY_H