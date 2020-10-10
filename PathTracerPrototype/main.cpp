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
 */

 // Header files
#include <iostream>
#include <fstream>
#include <vector>

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
	const int image_height = 256;

	// Create output file object, ppm
	ofstream ppm;

	// Output file name
	string fileName = "image";

	// Create file with .ppm extension
	ppm.open(fileName + ".ppm");

	// **** RENDER **** //

	// Output first line of file containing P3 header, image height, image width, and number of colours
	ppm << "P3\n" << image_width << ' ' << image_height << "\n255\n";

	// Iterate all pixels over image height, starting from the top of the image
	for (int j = image_height - 1; j >= 0; j--)
	{
		// Iterate all pixels over the image width
		for (int i = 0; i < image_width; i++)
		{
			// Determine the red component of the pixel (value depends on the image width)
			auto r = double(i) / (image_width - 1);
			
			// Convert red value to an integer
			int int_r = static_cast<int>(255.999 * r);

			// Determine the green component of the pixel (value depends on the image height)
			auto g = double(j) / (image_height - 1);

			// Convert green value to an integer
			int int_g = static_cast<int>(255.999 * g);

			// Set blue value to a constant 0.25
			auto b = 0.25;

			// Convert blue value to an ineger
			int int_b = static_cast<int>(255.999 * b);

			// Output components to pixel colours to the ppm file
			ppm << int_r << ' ' << int_g << ' ' << int_b << '\n';
		}
	}

	// Close the PPM file
	ppm.close();

	// Output message to console indicating that the file has been created
	cout << "Image rendered! " << fileName << ".ppm" << endl;

	// Return 0 - program is finished, all is OK
	return 0;





}