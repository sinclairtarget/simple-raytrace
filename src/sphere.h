#include "vec3.h"
#include "ray.h"

typedef struct {
    Vec3 center;
    float radius;
} Sphere;

Sphere* SphereCreate(Vec3 center, float radius);

/* 
 * If the ray intersects the sphere, returns the first intersection (i.e. the
 * intersection closest to the ray's origin).
 * 
 * If the ray does not intersect the sphere, returns nothing.
 */
RayHit* RayIntersect(Sphere* sphere, Ray* ray);

// String representation for debugging.
char* SphereToString(Sphere* sphere);
