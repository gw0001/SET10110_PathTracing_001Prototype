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

// STB Library header file
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image_write.h"

// Namespace
using namespace std;

///*
// * HIT SPHERE FUNCTION
// *
// * Function is used to determine if a sphere
// * has been hit by a ray
// */
//float hitSphere(const point3& centre, float radius, const ray& r)
//{
//	// Hit sphere value
//	float hitSphereValue = 0;
//
//	// Determine the vector from the ray origin to the sphere centre
//	vec3 oc = r.getOrigin() - centre;
//
//	// Determine 'a' component of discriminant of quadratic formula
//	auto a = r.getDirection().lengthSquared();
//
//	// Determine 'b' component of discriminant of quadratic formula
//	auto halfB = dot(oc, r.getDirection());
//
//	// Determine 'c' component of discriminant of quadratic formula
//	auto c = oc.lengthSquared() - radius * radius;
//
//	// Determine the discriminant of the quadratic formula
//	auto discriminant = halfB * halfB - a * c;
//
//	// Check if the determinant is less than 0, to determine if a collision has taken place
//	if (discriminant < 0)
//	{
//		// No collision, set hitSphereValue to -1.0
//		hitSphereValue = -1.0;
//	}
//	else
//	{
//		// Collision with sphere, determine the hitSphereValue
//		hitSphereValue = (-halfB - sqrt(discriminant)) / a;
//	}
//
//	// Return the value held by the check variable
//	return hitSphereValue;
//}


/*
 * RAY COLOUR FUNCTION
 *
 * Function is used to determine and return the
 * colour of a ray
 */
colour rayColour(ray& r, const hittable& world)
{
	// Create empty ray colour vector
	colour rayColour;

	// Hit Record
	hitRecord rec;

	// Check if an object in the world has been hit
	if (world.hit(r, 0, infinity, rec))
	{
		// Set the ray colour
		rayColour = 0.5 * (rec.normal + colour(1, 1, 1));
	}
	else
	{
		// No collision with object, determine the unit direction of the ray
		vec3 unitDirection = unitVector(r.getDirection());

		// Obtain ray parameter, t
		auto  t = 0.5 * (unitDirection.getY() + 1.0);

		// Determine the ray colour
		rayColour = (1.0 - t) * colour(1.0, 1.0, 1.0) + t * colour(0.5, 0.7, 1.0);
	}

	// Return the ray colour
	return rayColour;
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

	// Output file name
	string fileName = "sphere";

	// JPG Vector
	vector<uint8_t> jpgVector;

	// Clear the jpgVector
	jpgVector.clear();

	// **** WORLD PROPERTIES **** //
	hittableList world;
	world.add(make_shared<sphere>(point3(0, 0, -1), 0.5));
	world.add(make_shared<sphere>(point3(0, -100.5, -1), 100));

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
		cout << "\rScanlines remaining: " << j << ' ' << flush;

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
			colour pixelColour = rayColour(r, world);

			// Invoke the write colour function
			writeColour(pixelColour, jpgVector);
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