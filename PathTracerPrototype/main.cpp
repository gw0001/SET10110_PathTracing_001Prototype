/* ==================================================================
 * SET10110 - ADVANCED GAMES ENGINEERING
 *
 * GRAEME B. WHITE - 40415739
 * 
 * DATE OF CREATION: 10/10/2020
 * DATE LAST MODIFIED: 14/10/2020
 * ==================================================================
 * PATH-TRACING PROTOTYPE
 *
 * Prototype version of the path-tracer developed for SET10110 -
 * Advanced Games Engineering.
 *
 * Work is based on the path tracer developed in "Ray Tracing in one
 * Weekend" by P. Shirley - https://raytracing.github.io/
 * 
 * Program currently outputs an image equivalent of "Hello, world!"
 * 
 * Outputs an image in JPG format.
 */

// Header files
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

// Common Library header files
#include "common/common.h"
#include "common/colour.h"
#include "common/hittableList.h"
#include "common/sphere.h"
#include "common/camera.h"
#include "common/material.h"

// STB Library header file
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image_write.h"

// Namespace
using namespace std;

/*
 * RAY COLOUR FUNCTION
 *
 * Function is used to determine and return the
 * colour of a ray
 */
colour rayColour(ray& r, const hittable& world, int depth)
{
	// Create empty ray colour vector
	colour colourOfRay;

	// Hit Record
	hitRecord rec;

	// Check if depth is less than 0
	if (depth <= 0)
	{
		// Ray bounce limit, no more light gathered. Set colour to (0.0, 0.0, 0.0)
		colourOfRay = colour(0.0, 0.0, 0.0);
	}
	// Check if an object in the world has been hit (0.001 as tMin to fix shadow acne)
	else if (world.hit(r, 0.001, infinity, rec))
	{
		// Set the scattered colour to black
		colour scatteredColour(0.0, 0.0, 0.0);

		// Empty scattered ray object
		ray scattered;

		// Empty attenuation colour
		colour attenuation;

		// Check if a scattered ray is created upon collision
		if (rec.materialPointer->scatter(r, rec, attenuation, scattered))
		{
			// Scattered ray is true, obtain the scattered ray colour
			scatteredColour = attenuation * rayColour(scattered, world, depth - 1);
		}
		
		// Set the colour of the ray to the scattered ray colour
		colourOfRay = scatteredColour;

	}
	// No collision with object
	else
	{
		// Determine the unit direction of the ray
		vec3 unitDirection = unitVector(r.getDirection());

		// Obtain ray parameter, t
		auto  t = 0.5 * (unitDirection.getY() + 1.0);

		// Determine the ray colour
		colourOfRay = (1.0 - t) * colour(1.0, 1.0, 1.0) + t * colour(0.5, 0.7, 1.0);
	}

	// Return the ray colour
	return colourOfRay;
}

 /*
  * MAIN FUNCTION
  *
  * The first function that is invoked when the application is loaded.
  *
  * Creates a basic image equivalent of "Hello, World!"depending on the
  * height and width of the image settings.
  */
int main()
{
	// **** IMAGE PROPERTIES **** //
	
	// Aspect ratio
	const auto aspectRatio = 16.0 / 9.0;
	
	// Image width
	const int imageWidth = 1920;

	// Determine the image height, based on the image width and aspect ratio
	const int imageHeight = static_cast<int>(imageWidth / aspectRatio);

	// Samples Per Pixel
	const int samplesPerPixel = 100;

	// Maximum depth
	const int maxDepth = 50;

	// Output file name
	string fileName = "proto09";

	// Image Vector
	vector<uint8_t> imgVector;

	// Clear the jpgVector
	imgVector.clear();

	// **** WORLD PROPERTIES **** //
	
	// World hittable list object
	hittableList world;

	//// Ground sphere - Lambertian material
	//auto groundSphere = make_shared<lambertian>(colour(0.8, 0.8, 0.0));

	//// Centre Sphere - Lambertian material
	//auto centreSphere = make_shared<lambertian>(colour(0.7, 0.3, 0.3));

	//// Left Sphere - Metal material
	//auto leftSphere = make_shared<metal>(colour(0.8, 0.8, 0.8), 0.3);

	//// Right Sphere - metal material
	//auto rightSphere = make_shared<metal>(colour(0.8, 0.6, 0.2), 1.0);

	// V A P O R W A V E A S T H E T I C
	// Ground sphere - Lambertian material
	auto groundSphere = make_shared<lambertian>(colour(0.988, 0.0, 0.992));

	// Centre Sphere - Lambertian material
	auto centreSphere = make_shared<lambertian>(colour(0.867, 0.992, 0.281));

	// Left Sphere - Metal material
	auto leftSphere = make_shared<metal>(colour(0.0, 0.699, 0.996), 0.25);

	// Right Sphere - metal material
	auto rightSphere = make_shared<metal>(colour(0.0, 0.086, 0.926), 0.8);


	// Add ground sphere to the world list
	world.add(make_shared<sphere>(point3(0.0, -100.5, -1.0), 100.0, groundSphere));

	// Add centre sphere to the world list
	world.add(make_shared<sphere>(point3(0.0, 0.0, -1.0), 0.5, centreSphere));

	// Add left sphere to the world list
	world.add(make_shared<sphere>(point3(-1.0, 0.0, -1.0), 0.5, leftSphere));

	// Add right sphere to the world list
	world.add(make_shared<sphere>(point3(1.0, 0.0, -1.0), 0.5, rightSphere));

	// **** CAMERA SETTINGS **** //
	
	// Camera object
	camera cam;
	
	// **** RENDER IMAGE **** //

	// Iterate all pixels over image height, starting from the top of the image
	for (int j = imageHeight - 1; j >= 0; j--)
	{
		// Display progress to the console window
		cout << "\rScanlines remaining: " << j << ' ' << flush;

		// Iterate all pixels over the image width
		for (int i = 0; i < imageWidth; i++)
		{
			// Initialise pixel colour
			colour pixelColour(0.0f, 0.0f, 0.0f);

			// Iterate pixel over samples per pixel
			for (int s = 0; s < samplesPerPixel; s++)
			{
				// Determine u coordinate of pixel
				auto u = (i + randomFloat()) / (imageWidth - 1);

				// Determine v coordinate of pixel
				auto v = (j + randomFloat()) / (imageHeight - 1);

				// Cast ray from the pixel at (u,v)
				ray r = cam.getRay(u, v);

				// Determine the pixel colour based on the ray
				pixelColour += rayColour(r, world, maxDepth);
			}

			// Invoke the write colour function
			writeColour(pixelColour, imgVector, samplesPerPixel);
		}
	}

	// End the line on the console window
	cout << endl;

	// **** CREATE JPG FILE **** //

	// Desired output file name and extension
	string jpgFile = fileName + ".jpg";
	
	// Empty array of characters, for stbi_write_image
	char* jpgFileName = new char[jpgFile.size() + 1];
	
	// Copy contents of jpgFile string to jpgFileName char array
	copy(jpgFile.begin(), jpgFile.end(), jpgFileName);

	// Add terminating zero character to the end of the character array
	jpgFileName[jpgFile.size()] = '\0'; 

	// Create JPG file from the JPG Vector
	stbi_write_jpg(jpgFileName, imageWidth, imageHeight, 3, imgVector.data(), 100);

	// Output message to console indicating that the JPG file has been created
	cout << "JPG File created" << endl;

	// Return 0 - program is finished, all is OK
	return 0;
}