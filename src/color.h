#ifndef COLOR_H
#define COLOR_H

// An RGB color.
typedef struct {
    float r;
    float g;
    float b;
    float a;
} Color;

// Scales the R, G, and B components of the color.
Color ColorScale(Color color, float scalar);

// Component-wise addition, including alpha channel
Color ColorAdd(Color a, Color b);

#endif
