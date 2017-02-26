#include "shading.h"
#include "scene.h"
#include "macros.h"

Color Shade(Camera* camera, RayHit* hit)
{
    Vec3 lightDir = { 1, 1, 1 };
    Vec3 lightDirNorm = Vec3Norm(lightDir);
    float lightIntensity = 0.7f;

    float angleCooefficient = max(0, Vec3Dot(hit->normal, lightDirNorm));
    Color lambertian = 
        ColorScale(hit->surfaceColor, lightIntensity * angleCooefficient);

    Color ambient = 
        ColorScale(hit->surfaceColor, globalScene->ambientLightIntensity);

    return ColorAdd(lambertian, ambient);
}
