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
 * 
 * ==================================================================
 */
class camera
{
	// Public functions
	public:
		/*
		 * CAMERA CONSTRUCTOR
		 */
		camera()
		{
			// Aspect ratio
			const auto aspectRatio = 16.0 / 9.0;

			// Camaiewport height
			auto viewportHeight = 2.0;

			// Viewport width
			auto viewportWidth = aspectRatio * viewportHeight;

			// Camera focal length
			auto focalLength = 1.0;

			// Camera Origin
			origin = point3(0.0f, 0.0f, 0.0f);

			// Horizontal axis of the camera
			horizontal = vec3(viewportWidth, 0, 0);

			// Vertical axis of the camera
			vertical = vec3(0, viewportHeight, 0);

			// Determine the lower left corner of the camera
			lowerLeftCorner = origin - horizontal / 2 - vertical / 2 - vec3(0, 0, focalLength);
		}

		/*
		 * GET RAY FUNCTION
		 */
		ray getRay(float u, float v) const
		{
			return ray(origin, lowerLeftCorner + u * horizontal + v * vertical - origin);
		}

	// Private variables
	private:
		// Camera origin
		point3 origin;

		// Lower left corner of camera
		point3 lowerLeftCorner;

		// Horizontal axis
		vec3 horizontal;

		// Vertical axis
		vec3 vertical;
};

// End ifndef directive for CAMERA_H
#endif CAMERA_H