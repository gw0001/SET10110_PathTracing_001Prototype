/* ==================================================================
 * SET10110 - ADVANCED GAMES ENGINEERING
 *
 * GRAEME B. WHITE - 40415739
 *
 * DATE OF CREATION: 13/10/2020
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
 * ==================================================================
 * MATERIAL HEADER FILE
 *
 * Header file containing an abstract material class,
 * Lambertian diffuse class, and metal class.
 * 
 * Each class has the necessary functions and variables
 */

#ifndef MATERIAL_H
#define MATERIAL_H

// Header file
#include "common.h"

// Forward Declaratioon of Hit Record struct
struct hitRecord;

/* ==================================================================
 * ABSTRACT MATERIAL CLASS
 * 
 * Abstract of the material class. Contains abstract scatter
 * function to determine if a scattered ray is produced upon a ray
 * colliding with an object, based on the material
 * ==================================================================
 */
class material 
{
    // Public function
    public:

        /*
         * SCATTER FUNCTION
         * 
         * Function to determine if a ray will produce a scatter ray upon 
         * collision with an object
         */
        virtual bool scatter(const ray& rayIn, const hitRecord& rec, colour& attenuation, ray& scattered) const = 0;
};

/* ==================================================================
 * LAMBERTIAN DIFFUSE CLASS
 * 
 * Lambertian diffuse material class. Contains all functions and 
 * variables for this material
 * ==================================================================
 */
class lambertian : public material 
{
    // Public
    public:
        /*
         * LAMBERTIAN CONSTRUCTOR
         * 
         * When invoked, creates a Lambertian diffuse material object
         * and sets the albedo colour
         */
        lambertian(const colour& a) : _albedo(a) {}

        /*
         * SCATTER FUNCTION
         *
         * Function to determine if a ray will produce a scatter ray upon
         * collision with an object. Contains 3 different approaches
         * to rendering lambertian material. 2 methods commented out
         */
        virtual bool scatter(const ray& rayIn, const hitRecord& rec, colour& attenuation, ray& scattered) const override 
        {
            // Obtain scatter direction - simple Lambertian dissuse material
            //vec3 scatter_direction = rec.normal + randomUnitVector();

            // Obtain scatter direction - simple Lambertian dissuse material
            //vec3 scatter_direction = rec.normal + randomInUnitSphere();

            // Obtain scatter direction - simple Lambertian dissuse material
            vec3 scatter_direction = rec.normal + randomInHemisphere(rec.normal);

            // Obtain the scattered ray
            scattered = ray(rec.p, scatter_direction);

            // Set the albedo colour
            attenuation = _albedo;

            // Return true
            return true;
        }

    // Private variables
    private:
        // Albedo colour
        colour _albedo;
};

/* ==================================================================
 * METAL CLASS
 *
 * Metal material class, capable of reflecting rays. Contains all
 * functions and variables for this material
 * ==================================================================
 */
class metal : public material 
{
    // Public functions
    public:
        /*
         * METAL CONSTRUCTOR
         * 
         * When invoked, creates a metal material object and sets the 
         * albedo colour and fuzz amount
         */
        metal(const colour& a, float f) : _albedo(a), _fuzz(f < 1 ? f : 1) {}

        /*
         * SCATTER FUNCTION
         *
         * Function to determine if a ray will produce a scatter ray upon
         * collision with an object
         */
        virtual bool scatter(const ray& r_in, const hitRecord& rec, colour& attenuation, ray& scattered) const override
        {
            // Obtain the reflected vector
            vec3 reflected = reflect(unitVector(r_in.getDirection()), rec.normal);

            // Obtain the scattered ray
            scattered = ray(rec.p, reflected + _fuzz * randomInHemisphere(rec.normal));
            
            // Set the attenuation
            attenuation = _albedo;

            // Return true if the scattered ray is in the same hemisphere as the normal
            return (dot(scattered.getDirection(), rec.normal) > 0);
        }

    // Private varialbes
    public:
        // Albedo colour
        colour _albedo;

        // Fuzz value
        float _fuzz;
};

/* ==================================================================
 * DIELECTRIC CLASS
 *
 * Dilectric material class, capable of refracting rays. Contains all
 * functions and variables for this material
 * ==================================================================
 */
class dielectric : public material
{
    // Public functions
    public:
        /*
         * DIELECTRIC CONSTRUCTOR
         * 
         * When invoked, creates a dielectric material 
         */
        dielectric(float ir)
                : _indexOfRefraction(ir) {};

        /*
         * SCATTER FUNCTION
         * 
         * Function determines if a scatter ray is created when a ray 
         * collides with the object
         */
        virtual bool scatter(const ray& rayIn, const hitRecord& rec, colour& attenuation, ray& scattered) const override
        {
            // Set attenuation colour
            attenuation = colour(1.0, 1.0, 1.0);

            // Determine the Refraction ratio
            float refractionRatio;
            //double refractionRatio = rec.frontFace ? (1.0 / _indexOfRefraction) : _indexOfRefraction;

            // Check if front face has been hit
            if (rec.frontFace == true)
            {
                // Front face hit, determine the ratio between air and dielectric material
                refractionRatio = 1.0 / _indexOfRefraction;
            }
            else
            {
                // Front face not hit, set refraction ratio to index of refraction (ray inside material)
                refractionRatio = _indexOfRefraction;
            }

            // Obtain the unit direction based on the ray
            vec3 unitDirection = unitVector(rayIn.getDirection());

            // Determine Cos Theta
            double cosTheta = fmin(dot(-unitDirection, rec.normal), 1.0);

            // Determine Sin of Theta
            double sinTheta = sqrt(1.0 - cosTheta * cosTheta);

            // Obtain the value of Cannot Refract
            bool cannotRefract = refractionRatio * sinTheta > 1.0;
            
            // Empty direction vector
            vec3 direction;

            // Check if ray cannot be refracted or if reflectances is greater than a random float between 0 and 1
            if (cannotRefract || reflectance(cosTheta, refractionRatio) > randomFloat())
            {
                // Cannot refract, obtain reflection
                direction = reflect(unitDirection, rec.normal);
            }
            else
            {
                // Can refract, obtain refraction
                direction = refract(unitDirection, rec.normal, refractionRatio);
            }

            // Obtain the scattered ray
            scattered = ray(rec.p, direction);

            // Obtain the refracted ray
            vec3 refracted = refract(unitDirection, rec.normal, refractionRatio);

            // Determine the scattered ray
            scattered = ray(rec.p, refracted);

            // Return true
            return true;
        }

    // Private functions
    private:

        // Index of refraction
        float _indexOfRefraction;

        /*
         * REFLECTANCE FUNCTION
         * 
         * Function uses Schlick's approximation for reflectance
         */
        static float reflectance(float cosine, float refractanceIndex)
        {
            // Determine value of r0
            auto r0 = (1 - refractanceIndex) / (1 + refractanceIndex);

            // Determine value of r0 squared
            auto r0Squared = r0 * r0;

            // Return 
            return r0Squared + (1 - r0Squared) * pow((1 - cosine), 5);
        }
};

// End ifndef directive for MATERIAL_H
#endif