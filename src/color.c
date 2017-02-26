#include "color.h"
#include "macros.h"

Color ColorScale(Color color, float scalar)
{
    color.r = clamp(color.r * scalar, 0, 1);
    color.g = clamp(color.g * scalar, 0, 1);
    color.b = clamp(color.b * scalar, 0, 1);
    return color;
}

Color ColorAdd(Color a, Color b)
{
    a.r = clamp(a.r + b.r, 0, 1);
    a.g = clamp(a.g + b.g, 0, 1);
    a.b = clamp(a.b + b.b, 0, 1);
    return a;
}
