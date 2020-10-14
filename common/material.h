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
        lambertian(const colour& a) : albedo(a) {}

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
            attenuation = albedo;

            // Return true
            return true;
        }

    // Private variables
    private:
        // Albedo colour
        colour albedo;
};

/* ==================================================================
 * METAL CLASS
 *
 * Metal material class. Contains all functions and variables for 
 * this material
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
         * albedo colour
         */
        metal(const colour& a, float f) : albedo(a), fuzz(f < 1 ? f : 1) {}

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
            scattered = ray(rec.p, reflected + fuzz * randomInHemisphere(rec.normal));
            
            // Set the attenuation
            attenuation = albedo;

            // Return true if the scattered ray is in the same hemisphere as the normal
            return (dot(scattered.getDirection(), rec.normal) > 0);
        }

    // Private varialbes
    public:
        // Albedo colour
        colour albedo;

        // Fuzz value
        float fuzz;
};

// End ifndef directive for MATERIAL_H
#endif MATERIAL_H