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
 * HITTABLE SPEHRE CLASS
 *
 * Header file containing the hittable sphere class, which is an 
 * extension of the abstract hittable class
 */

// Declare ifndef directive for HITTABLE_SPHERE_H
#ifndef SPHERE_H

// Define HITTABLE_SPHERE_H
#define SPHERE_H

// Header files
#include "hittable.h"
#include "vec3.h"

/* ==================================================================
 * SPHERE CLASS
 * 
 * Class for sphere objects. Extension of the hittable abstract
 * class.
 * 
 * Contains constructors and functions for sphere class objects.
 * ==================================================================
 */
class sphere : public hittable
{
	// Public
	public:
		/*
		 * DEFAULT SPHERE CONSTRUCTOR
		 * 
		 * When invoked, constructs an empty sphere object
		 */
		sphere() {}

		/*
		 * SPHERE CONSTRUCTOR
		 * 
		 * Creates a sphere with centre c and radius r
		 */
		sphere(point3 c, float r) :
			centre(c), radius(r) {};

		/*
		 * HIT FUNCTION
		 *
		 * Overridden function from abstract hittable class.
		 * Used to determine if a sphere has been hit by
		 * a ray
		 */
		virtual bool hit(const ray& r, float tMin, float tMax, hitRecord& rec) const override;

		/*
		 * GET CENTRE FUNCTION
		 * 
		 * Function returns the centre of the sphere
		 */
		vec3 getCentre() const;


		/*
		 * GET RADIUS FUNCTION
		 *
		 * Function returns the centre of the sphere
		 */
		float getRadius() const;

	// Private
	private:
		// Sphere centre
		point3 centre;

		// Sphere radius
		float radius;
};

/*
 * GET CENTRE FUNCTION
 *
 * Function returns the centre of the sphere
 */
vec3 sphere::getCentre() const
{
	return centre;
}

/*
 * GET RADIUS FUNCTION
 *
 * Function returns the centre of the sphere
 */
float sphere::getRadius() const
{
	return radius;
}

/*
 * HIT FUNCTION
 *
 * Overridden function from abstract hittable class.
 * Used to determine if a sphere has been hit by
 * a ray
 */
bool sphere::hit(const ray& r, float tMin, float tMax, hitRecord& rec) const
{
	// Hit sphere value
	bool hitSphere = false;

	// Determine the vector from the ray origin to the sphere centre
	vec3 oc = r.getOrigin() - centre;

	// Determine 'a' component of discriminant of quadratic formula
	auto a = r.getDirection().lengthSquared();

	// Determine 'b' component of discriminant of quadratic formula
	auto halfB = dot(oc, r.getDirection());

	// Determine 'c' component of discriminant of quadratic formula
	auto c = oc.lengthSquared() - radius * radius;

	// Determine the discriminant of the quadratic formula
	auto discriminant = (halfB * halfB) - (a * c);

	// Check if the determinant is greater than 0, to determine if a collision has taken place
	if (discriminant > 0)
	{
		// Determine the root of the discriminant
		auto root = sqrt(discriminant);

		// Determine temporary ray parameter t with negative the square root of the dicriminant
		auto tempT = (-halfB - root) / a;

		// Check if ray paramteter is within tMin and tMax
		if (tempT < tMax && tempT > tMin) 
		{
			// Set recorded ray parameter to value held by tempT
			rec.t = tempT;

			// Determine the point of collision
			rec.p = r.at(rec.t);

			// Determine the outwardNormal
			vec3 outwardNormal = (rec.p - sphere::getCentre()) / sphere::getRadius();

			// Determine if the face is facing the front, determine the normal, and record the normal
			rec.setFaceNormal(r, outwardNormal);

			// Set hitableSphere to true
			hitSphere = true;
			
			// Return value of hitSphere
			return hitSphere;
		}

		// Determine temporary ray parameter t with positive the square root of the dicriminant
		tempT = (-halfB + root) / a;

		// Check if ray paramteter is within tMin and tMax
		if (tempT < tMax && tempT > tMin) 
		{
			// Set recorded ray parameter to value held by tempT
			rec.t = tempT;

			// Determine the point of collision
			rec.p = r.at(rec.t);

			// Determine the outwardNormal
			vec3 outwardNormal = (rec.p - sphere::getCentre()) / sphere::getRadius();

			// Determine if the face is facing the front, determine the normal, and record the normal
			rec.setFaceNormal(r, outwardNormal);

			// Set hitableSphere to true
			hitSphere = true;

			// Return value of hitSphere
			return hitSphere;
		}
	}

	// Return the value held by the check variable
	return hitSphere;
}

// End ifndef directive for HITTABLE_SPHERE_H
#endif SPHERE_H