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
 * HITTABLE LIST CLASS
 *
 * Header file containing the hittable list class, which is an
 * extension of the abstract hittable class
 */

// Declare ifndef directive of HITTABLE_LIST_H
#ifndef HITTABLE_LIST_H

// Define HITTABLE_LIST_H
#define HITTABLE_LIST_H

// Headers
#include "hittable.h"
#include <memory>
#include <vector>

// Namespaces
using namespace std;

// Using
using std::shared_ptr;
using std::make_shared;

/* ==================================================================
 * HITTABLE LIST CLASS
 *
 * Class for hittable list objects. Extension of the hittable
 * abstract class.
 *
 *
 * ==================================================================
 */
class hittableList : public hittable
{
	// Public
public:
	/*
	 * DEFAULT HITTABLE LIST CONSTRUCTOR
	 *
	 * When invoked, creates an empty hittable list object
	 */
	hittableList() {}

	/*
	 * HITTABLE LIST CONSTRUCTOR
	 *
	 * Constructor creates a hittable list object and
	 * adds an object to the objects list
	 */
	hittableList(shared_ptr<hittable> object) { add(object); };

	/*
	 * CLEAR FUNCTION
	 *
	 * Function clears all entries from the
	 * list of objects
	 */
	void clear()
	{
		objects.clear();
	}

	/*
	 * ADD FUNCTION
	 *
	 * Function adds an object to the
	 * list of objects
	 */
	void add(shared_ptr<hittable> object)
	{
		objects.push_back(object);
	}

	/*
	 * HIT FUNCTION
	 *
	 * Function determines if an object has been hit by a ray
	 */
	virtual bool hit(const ray& r, float tMin, float tMax, hitRecord& rec) const override;


	// Private variables
private:
	// 
	vector<shared_ptr<hittable>> objects;
};

/*
 * HIT FUNCTION
 *
 * Function determines if an object has been hit by a ray
 */
bool hittableList::hit(const ray& r, float tMin, float tMax, hitRecord& rec) const
{
	// Temporary hit record
	hitRecord tempRec;

	// Hit Anything boolean
	bool hitAnything = false;

	// Determine closes ray parameter
	auto closestSoFar = tMax;

	// Examine each object in objects list
	for (const auto& object : objects)
	{
		// Check if object has been hit by a ray
		if (object->hit(r, tMin, closestSoFar, tempRec) == true)
		{
			// Object hit by ray, set hit anything to true
			hitAnything = true;

			// Set Closest so far to the ray parameter from tempRec
			closestSoFar = tempRec.t;

			// Set rec to the tempRec
			rec = tempRec;
		}
	}

	// Return value of hit anything;
	return hitAnything;
}

// End ifndef directive of HITTABLE_LIST_H
#endif HITTABLE_LIST_H