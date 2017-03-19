#include <stdlib.h>
#include <math.h>

#include "shading.h"
#include "scene.h"
#include "macros.h"

Color Shade(Camera* camera, RayHit* hit)
{
    Vec3 lightDirNorm = Vec3Norm(globalScene->lightDirection);
    float lightIntensity = 0.7f;

    // Calculate ambient component
    Color ambient = 
        ColorScale(hit->surfaceColor, globalScene->ambientLightIntensity);

    // Return early if point is in shadow
    Ray* shadowRay = RayCreate(hit->point, lightDirNorm);
    RayHit* shadowHit = RayCast(shadowRay, EPSILON);
    if (shadowHit != NULL)
        return ambient;

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

    // Resulting color is sum of all components
    return ColorAdd(ColorAdd(lambertian, phong), ambient);
}
