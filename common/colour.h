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
 * COLOUR FUNCTION
 *
 * Header file contains the function to determine and write the RGB
 * value to the jpgVector
 */

// Declare ifndef directive for COLOUR_H
#ifndef COLOUR_H

// Define COLOUR_H
#define COLOUR_H

// Header files
#include "vec3.h"
#include <iostream>
#include <vector>

//Namespace
using namespace std;
/*
 * WRITE COLOUR FUNCTION
 * 
 * Function takes in an ostream object and pixel colour vector, 
 * then writes the pixel colour to the ostream object.
 */
void writeColour(colour pixel_colour, vector<uint8_t> &jpgVector) 
{
    // Convert red value to an unsigned 8bit ineger
    uint8_t intR = static_cast<uint8_t>(255.999 * pixel_colour.getX());

    // Add the red value to the JPG Vector
    jpgVector.push_back(intR);

    // Convert green value to an unsigned 8bit ineger
    uint8_t intG = static_cast<uint8_t>(255.999 * pixel_colour.getY());

    // Add the green value to the JPG Vector
    jpgVector.push_back(intG);

    // Convert blue value to an unsigned 8bit ineger
    uint8_t intB = static_cast<uint8_t>(255.999 * pixel_colour.getZ());

    // Add the blue value to the JPG Vector
    jpgVector.push_back(intB);
}

// End ifndef directive for COLOUR_H
#endif COLOUR_H