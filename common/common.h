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
#include <cstdlib>
#include <random>

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
inline float degreesToRadians(float degrees)
{
    // Determine and return the radian value 
    return degrees * pi / 180.0;
}


/*
 * RANDOM INT FUNCTION
 *
 * Function is used to create a random
 * float between 1 and 5
 */
inline int randomInt(int min, int max)
{
    // Random Device
    std::random_device rd;

    // Mersenne Twister pseudo-random generator 
    std::mt19937 mt(rd());

    // Distribution
    std::uniform_int_distribution<int> randomNum(min, max);

    // Return random float
    return randomNum(mt);
}

/*
 * RANDOM FLOAT FUNCTION
 *
 * Function is used to create a random
 * float between 0 and 1
 */
inline float randomFloat()
{
    // Random Device
    std::random_device rd;

    // Mersenne Twister pseudo-random generator 
    std::mt19937 mt(rd());

    // Distribution
    std::uniform_real_distribution<float> randomNum(0.0, 1.0);

    // Return random float
    return randomNum(mt);
}

/*
 * RANDOM FLOAT FUNCTION
 *
 * Function is used to create a random
 * float between a maximum and minimum
 * range
 */
inline float randomFloat(float min, float max)
{
    // Random Device
    std::random_device rd;

    // Mersenne Twister pseudo-random generator 
    std::mt19937 mt(rd());

    // Distribution
    std::uniform_real_distribution<float> randomNum(min, max);

    // Return random float
    return randomNum(mt);
}

/*
 * CLAMP FUNCTION
 * 
 * Function is used to ensure a value is between a specified
 * maximum and minimum range. If value, x, is greater, the 
 * maximum range value is returned. If x is less, the minimum
 * range value is returned. If x is within range, x is returned
 */
inline float clamp(float x, float min, float max)
{
    // Check if x is less than the minimum value
    if (x < min)
    {
        // X is less than the minimum, return the minimum value
        return min;
    }

    // Check if x is greeater than the maximum value
    if (x > max)
    {
        // x is greater than the maximum, return the maximum value
        return max;
    }

    // Return x value
    return x;
}

// **** COMMON HEADERS **** //

// Ray header file
#include"ray.h"

// Vec3 header file
#include "vec3.h"

// End ifndef directive for COMMON_H
#endif