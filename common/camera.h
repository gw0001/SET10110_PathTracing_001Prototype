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
 * CAMERA HEADER FILE
 *
 * Header file for camera class
 */

// Delcare ifndef directive for CAMERA_H
#ifndef CAMERA_H

// Define CAMERA_H
#define CAMERA_H

// Headers
#include "common.h"

/* ==================================================================
 * CAMERA CLASS
 * 
 * Class for a camera object. Contains the public functions and 
 * private variables required for the class
 * ==================================================================
 */
class camera
{
	// Public functions
	public:

		/*
		 * CAMERA CONSTRUCTOR
		 * 
		 * When invoked, creates a camera object and automatically
		 * sets values for aspect ratio, view port height, viewport
		 * width, and focal length. Also determines and sets the 
		 * origin, horizontal axis, vertical axis and the lower 
		 * left corner.
		 */
		camera(point3& lookFrom, point3 lookAt, vec3 verticalUp, float verticalFoV, float aspectRatio)
		{
			// Determine theta in radians
			auto theta = degreesToRadians(verticalFoV);

			// Determine h
			auto h = tan(theta / 2);

			// Dtermine the viewport height
			auto viewportHeight = 2 * h;

			// Determine the viewport width
			auto viewportWidth = aspectRatio * viewportHeight;

			// Determine w component of orthogonal camera
			auto w = unitVector(lookFrom - lookAt);

			// Determine u component of orthogonal camera
			auto u = unitVector(cross(verticalUp, w));

			// Determine v component of orthogonal camera
			auto v = cross(w, u);

			// Set the origin of the camera
			_origin = lookFrom;

			// Set the horizontal axis of the camera
			_horizontal = viewportWidth * u;

			// Set the vertical axis of the camera
			_vertical = viewportHeight * v;

			// Determine and set the lower left corner of the camera viewport
			_lowerLeftCorner = _origin - _horizontal / 2 - _vertical / 2 - w;
		}

		/*
		 * GET RAY FUNCTION
		 * 
		 * Function returns a ray from the camera, based on u, v coordinates
		 */
		ray getRay(float u, float v) const
		{
			// Return ray, based on camera position
			return ray(_origin, _lowerLeftCorner + u * _horizontal + v * _vertical - _origin);
		}

	// Private variables
	private:
		// Camera origin
		point3 _origin;

		// Lower left corner of camera
		point3 _lowerLeftCorner;

		// Horizontal axis
		vec3 _horizontal;

		// Vertical axis
		vec3 _vertical;
};

// End ifndef directive for CAMERA_H
#endif