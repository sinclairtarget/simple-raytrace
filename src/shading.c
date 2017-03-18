#include <math.h>

#include "shading.h"
#include "scene.h"
#include "macros.h"

Color Shade(Camera* camera, RayHit* hit)
{
    Vec3 lightDir = { 1, 1, 1 };
    Vec3 lightDirNorm = Vec3Norm(lightDir);
    float lightIntensity = 0.7f;

    // Caclulate lambertian component
    float angleCooefficient = max(0, Vec3Dot(hit->normal, lightDirNorm));
    Color lambertian = 
        ColorScale(hit->surfaceColor, lightIntensity * angleCooefficient);

    // Calculate blinn-phong component
    Vec3 camDir = Vec3Norm(Vec3Sub(camera->position, hit->point));
    Vec3 halfVector = Vec3Norm(Vec3Add(camDir, lightDir));

    float halfVectorAngleCooefficent =
        max(0, Vec3Dot(hit->normal, halfVector));
    halfVectorAngleCooefficent = 
        powf(halfVectorAngleCooefficent, hit->surfacePhongExponent);

    Color phong = ColorScale(hit->surfaceSpecularColor, 
                             lightIntensity * halfVectorAngleCooefficent);

    // Calculate ambient component
    Color ambient = 
        ColorScale(hit->surfaceColor, globalScene->ambientLightIntensity);

    // Resulting color is sum of all components
    return ColorAdd(ColorAdd(lambertian, phong), ambient);
}
