/* ==================================================================
 * SET10110 - ADVANCED GAMES ENGINEERING
 *
 * GRAEME B. WHITE - 40415739
 * 
 * DATE OF CREATION: 10/10/2020
 * DATE LAST MODIFIED: 10/10/2020
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
#include "common/colour.h"
#include "common/vec3.h"
#include "common/ray.h"

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
colour ray_colour(ray& r)
{
	// Determine the unit direction of the ray
	vec3 unitDirection = unit_vector(r.getDirection());

	// Determine t based on the unit direction
	auto t = 0.5 * (unitDirection.getY() + 1.0);

	// Determine the colour of the pixel with a linear blend, then return the value
	return (1.0 - t) * colour(1.0, 1.0, 1.0) + t * colour(0.5, 0.7, 1.0);
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
	const int imageWidth = 400;

	// Determine the image height, based on the image width and aspect ratio
	const int imageHeight = static_cast<int>(imageWidth / aspectRatio);

	// Output file name
	string fileName = "blue";

	// JPG Vector
	vector<uint8_t> jpgVector;

	// Clear the jpgVector
	jpgVector.clear();

	// **** CAMERA SETTINGS **** //
	
	// Camaiewport height
	auto viewportHeight = 2.0;

	// Viewport width
	auto viewportWidth = aspectRatio * viewportHeight;

	// Camera focal length
	auto focalLength = 1.0;

	// Camera Origin
	auto origin = point3(0.0f, 0.0f, 0.0f);

	// Horizontal axis of the camera
	auto horizontal = vec3(viewportWidth, 0, 0);

	// Vertical axis of the camera
	auto vertical = vec3(0, viewportHeight, 0);

	// Determine the lower left corner of the camera
	auto lowerLeftCorner = origin - horizontal / 2 - vertical / 2 - vec3(0, 0, focalLength);

	// **** RENDER IMAGE **** //

	// Iterate all pixels over image height, starting from the top of the image
	for (int j = imageHeight - 1; j >= 0; j--)
	{
		// Display progress to the console window
		cout << "\rScanlines remaining: " << j << ' ' << std::flush;

		// Iterate all pixels over the image width
		for (int i = 0; i < imageWidth; i++)
		{
			// Determine U value of the pixel
			auto u =float(i) / (imageWidth - 1);

			// Determine V value of the pixel
			auto v = float(j) / (imageHeight - 1);

			// Create ray from pixel
			ray r(origin, lowerLeftCorner + u * horizontal + v * vertical - origin);

			// Determine the pixel colour based on the ray
			colour pixelColour = ray_colour(r);

			// Invoke the write colour function
			write_colour(pixelColour, jpgVector);
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
	stbi_write_jpg(jpgFileName, imageWidth, imageHeight, 3, jpgVector.data(), 100);

	// Output message to console indicating that the JPG file has been created
	cout << "JPG File created" << endl;

	// Return 0 - program is finished, all is OK
	return 0;
}