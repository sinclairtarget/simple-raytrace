#ifndef VEC3_H
#define VEC3_H

typedef struct {
    float x;
    float y;
    float z;
} Vec3;

// Unary negation.
Vec3 Vec3Neg(Vec3 v);

// Vector normalization.
Vec3 Vec3Norm(Vec3 v);

// Vector addition.
Vec3 Vec3Add(Vec3 a, Vec3 b);

// Vector subtraction.
Vec3 Vec3Sub(Vec3 a, Vec3 b);

// Scalar multiplication.
Vec3 Vec3Scale(Vec3 v, float scalar);

// Dot product.
float Vec3Dot(Vec3 a, Vec3 b);

// Cross product.
Vec3 Vec3Cross(Vec3 a, Vec3 b);

// Returns a string representation of the vector for debugging.
char* Vec3ToString(Vec3 v);

#endif
