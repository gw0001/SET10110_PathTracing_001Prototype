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
			_origin = point3(0.0f, 0.0f, 0.0f);

			// Horizontal axis of the camera
			_horizontal = vec3(viewportWidth, 0, 0);

			// Vertical axis of the camera
			_vertical = vec3(0, viewportHeight, 0);

			// Determine the lower left corner of the camera
			_lowerLeftCorner = _origin - _horizontal / 2 - _vertical / 2 - vec3(0, 0, focalLength);
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