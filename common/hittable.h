/* ==================================================================
 * SET10110 - ADVANCED GAMES ENGINEERING
 *
 * GRAEME B. WHITE - 40415739
 *
 * DATE OF CREATION: 11/10/2020
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
 * HITTABLE ABSTRACTION
 *
 * Header file containing an abstract hittable class
 */

// Declare ifndef directive for HITTABLE_H
#ifndef HITTABLE_H

// Define HITTABLE_H
#define HITTABLE_H

// Header files
#include "ray.h"

/*
 * ==================================================================
 * HIT RECORD STRUCT
 * 
 * Struct containing variables for 
 * ==================================================================
 */
struct hitRecord
{
	// Collision point
	point3 p;

	// Normal
	vec3 normal;

	// Ray parameter
	float t;

	// Front face boolean
	bool frontFace;

	/*
	 * SET FACE AND NORMAL FUNCTION
	 * 
	 * Function is used to determine if a face is facing
	 * the front (towards the camera) or facing the back,
	 * and set the normal depending on the face
	 */
	inline void setFaceNormal(const ray& r, const vec3& outwardNormal)
	{
		// Check dot product between ray direction and outward normal
		if (dot(r.getDirection(), outwardNormal) < 0)
		{
			// Set frontFace to true
			frontFace = true;
		}
		else
		{
			// Set frontFace to false
			frontFace = false;
		}

		// Set the value of the normal, depending on the value of frontFace
		if (frontFace = true)
		{
			// Front face, Set normal to the outward normal
			normal = outwardNormal;
		}
		else
		{
			// Back face, set normalt to the inverse of the outward normal
			normal = -outwardNormal;
		}
	}
};

/*
 * ==================================================================
 * HITTABLE CLASS
 * 
 * Abstract class containing a hittable function, used to determine
 * if an object has been hit by a ray
 * ==================================================================
 */
class hittable
{
	public:
		virtual bool hit(const ray& r, float tMin, float tMax, hitRecord& rec) const = 0;
};

// End ifndef directive for HITTABLE_H
#endif HITTABLE_H