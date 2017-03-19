#include <stdlib.h>
#include <math.h>

#include "shading.h"
#include "scene.h"
#include "macros.h"

#define MAX_REFLECTION_DEPTH 1

Color Shade(Camera* camera, RayHit* hit, int reflectionDepth)
{
    Vec3 lightDirNorm = Vec3Norm(globalScene->lightDirection);
    float lightIntensity = 0.7f;

    // Calculate ambient component
    Color ambient = 
        ColorScale(hit->surfaceColor, globalScene->ambientLightIntensity);

    // Return early if point is in shadow
    Ray* shadowRay = RayCreate(hit->point, lightDirNorm);
    RayHit* shadowHit = RayCast(shadowRay, EPSILON);
    free(shadowRay);
    if (shadowHit != NULL) {
        free(shadowHit);
        return ambient;
    }

    // Caclulate lambertian component
    float angleCooefficient = max(0, Vec3Dot(hit->normal, lightDirNorm));
    Color lambertian = 
        ColorScale(hit->surfaceColor, lightIntensity * angleCooefficient);

    // Calculate blinn-phong component
    Vec3 camDir = Vec3Norm(Vec3Sub(camera->position, hit->point));
    Vec3 halfVector = Vec3Norm(Vec3Add(camDir, lightDirNorm));

    float halfVectorAngleCooefficent =
        max(0, Vec3Dot(hit->normal, halfVector));
    halfVectorAngleCooefficent = 
        powf(halfVectorAngleCooefficent, hit->surfacePhongExponent);

    Color phong = ColorScale(hit->surfaceSpecularColor, 
                             lightIntensity * halfVectorAngleCooefficent);

    // Calculate reflective component
    Color reflective = BLACK_COLOR;
    if (!ColorEqual(hit->reflectiveColor, BLACK_COLOR) 
        && reflectionDepth < MAX_REFLECTION_DEPTH) {
        Vec3 d = Vec3Neg(camDir);
        Vec3 r = 
            Vec3Sub(d, Vec3Scale(hit->normal, 2 * Vec3Dot(d, hit->normal)));
        Ray* reflectionRay = RayCreate(hit->point, r);
        RayHit* reflectionHit = RayCast(reflectionRay, EPSILON);

        if (reflectionHit != NULL) {
            reflective = Shade(camera, reflectionHit, reflectionDepth + 1);
            reflective = ColorMultiply(hit->reflectiveColor, reflective);
            free(reflectionHit);
        }

        free(reflectionRay);
    }

    // Resulting color is sum of all components
    return ColorAdd(ColorAdd(lambertian, phong), 
                    ColorAdd(ambient, reflective));
}
