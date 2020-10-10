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
 * Outputs an image in PPM format and JPG format
 */

 // Header files
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

// STB Library
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image_write.h"

// Namespace
using namespace std;

/*
 * MAIN FUNCTION
 *
 * The first function that is invoked when the application is loaded.
 * 
 * Creates a basic image equivalent of "Hello, World!" in .ppm format,
 * depending on the height and width of the image settings.
 */
int main()
{
	// **** IMAGE PROPERTIES **** //
	// Image Width
	const int image_width = 512;

	// Image Height
	const int image_height = 512;

	// Create output file object, ppm
	ofstream ppm;

	// Output file name
	string fileName = "image";

	// Create file with .ppm extension
	ppm.open(fileName + ".ppm");

	// JPG Vector
	vector<uint8_t> jpgVector;

	// **** RENDER IMAGE **** //

	// Output first line of file containing P3 header, image height, image width, and number of colours
	ppm << "P3\n" << image_width << ' ' << image_height << "\n255\n";

	// Iterate all pixels over image height, starting from the top of the image
	for (int j = image_height - 1; j >= 0; j--)
	{
		// Display progress to the console window
		cout << "\rScanlines remaining: " << j << ' ' << std::flush;

		// Iterate all pixels over the image width
		for (int i = 0; i < image_width; i++)
		{
			// Determine the red component of the pixel (value depends on the image width)
			auto r = double(i) / (image_width - 1);
			
			// Convert red value to an unsigned 8bit ineger - using 255.999 instead of 256 as a dirty way of rounding the value to an integer
			uint8_t int_r = static_cast<uint8_t>(255.999 * r);

			// Add the red value to the JPG Vector
			jpgVector.push_back(int_r);

			// Determine the green component of the pixel (value depends on the image height)
			auto g = double(j) / (image_height - 1);

			// Convert green value to an unsigned 8bit ineger
			uint8_t int_g = static_cast<uint8_t>(255.999 * g);

			// Add the green value to the JPG vector
			jpgVector.push_back(int_g);

			// Set blue value to a constant 0.25
			auto b = 0.25;

			// Convert blue value to an unsigned 8bit ineger
			uint8_t int_b = static_cast<uint8_t>(255.999 * b);

			// Add the blue value to the JPG vector
			jpgVector.push_back(int_b);

			// Output components to pixel colours to the ppm file
			ppm << int_r << ' ' << int_g << ' ' << int_b << '\n';
		}
	}
	// End the line on the console window
	cout << endl;

	// Close the PPM file
	ppm.close();

	// Output message to console indicating that the PPM file has been created
	cout << "PPM File created" << endl;

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