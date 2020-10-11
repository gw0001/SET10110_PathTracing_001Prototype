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
 * COMMON HEADER FILE
 *
 * Header file containing common usings, constants, utility
 * functions, and headers
 */

// Delcare ifndef directive for COMMON_H
#ifndef COMMON_H

// Define COMMON_H
#define COMMON_H

// Headers
#include <cmath>
#include <limits>
#include <memory>

// **** COMMON USINGS **** //
using std::shared_ptr;
using std::make_shared;
using std::sqrt;

// **** COMMON CONTSTANTS **** //

// Infinity
const float infinity = std::numeric_limits<float>::infinity();

// pi
const float pi = 3.1415926535897932385;

// **** COMMON UTILITY FUNCTIONS **** //

/*
 * DEGREES TO RADIANS
 * 
 * Function converts value in degrees to radians
 * and returns the radian value
 */
inline double degreesToRadians(float degrees)
{
    // Determine and return the radian value 
    return degrees * pi / 180.0;
}

// **** COMMON HEADERS **** //

// Ray header file
#include"ray.h"

// Vec3 header file
#include "vec3.h"

// End ifndef directive for COMMON_H
#endif COMMON_H