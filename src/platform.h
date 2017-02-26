#ifndef PLATFORM_H
#define PLATFORM_H

#include "graphics.h"

/*
 * Defines the platform-agnostic windowing and drawing API.
 */

/*
 * Perform platform-specific initialization. 
 *
 * This must be called before anything else!
 */
void Init();

/*
 * Creates and shows a window. Returns the window dimensions as a RectSize.
 *
 * The size of the window can be expressed as a ratio to screen size.
 */
RectSize CreateWindow(float proportionalWidth, float proportionalHeight);

/*
 * Pulls all events from the event queue and dispatches them.
 */
void ProcessEvents();

/*
 * Draws a pixel in the window.
 *
 * The origin of the coordinate system is the upper-left corner of the window.
 */
void Draw(int x, int y, Color color);

#endif
