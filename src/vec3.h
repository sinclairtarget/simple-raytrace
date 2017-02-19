#ifndef VEC3_H
#define VEC3_H

typedef struct {
    float x;
    float y;
    float z;
} Vec3;

// Vector addition.
Vec3 Vec3Add(Vec3 a, Vec3 b);

// Dot product.
float Vec3Dot(Vec3 a, Vec3 b);

// Returns a string representation of the vector for debugging.
char* Vec3ToString(Vec3 v);

#endif
