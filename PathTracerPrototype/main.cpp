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

// STB Library header file
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image_write.h"

// Namespace
using namespace std;

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
	// Image Width
	const int image_width = 1920;

	// Image Height
	const int image_height = 1080;

	// Output file name
	string fileName = "image";

	// JPG Vector
	vector<uint8_t> jpgVector;

	// Clear the jpgVector
	jpgVector.clear();

	// **** RENDER IMAGE **** //

	// Iterate all pixels over image height, starting from the top of the image
	for (int j = image_height - 1; j >= 0; j--)
	{
		// Display progress to the console window
		cout << "\rScanlines remaining: " << j << ' ' << std::flush;

		// Iterate all pixels over the image width
		for (int i = 0; i < image_width; i++)
		{
			// For each pixel, determine the RGB values and create a colour vector
			colour pixel_colour(float(i) / (image_width - 1), float(j) / (image_height - 1), 0.25f);

			// Invoke the write colour function
			write_colour(pixel_colour, jpgVector);
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
	stbi_write_jpg(jpgFileName, image_width, image_height, 3, jpgVector.data(), 100);

	// Output message to console indicating that the JPG file has been created
	cout << "JPG File created" << endl;

	// Return 0 - program is finished, all is OK
	return 0;
}