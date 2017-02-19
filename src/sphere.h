#include "Vec3.h"

typedef struct {
    Vec3 center;
    float radius;
} Sphere;

Sphere* SphereCreate(Vec3 center, float radius);

// String representation for debugging.
char* SphereToString(Sphere* sphere);
