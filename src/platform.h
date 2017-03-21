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
 * The size of the window is expressed directly.
 */
RectSize CreateWindow(float width, float height);

/*
 * Creates and shows a window. Returns the window dimensions as a RectSize.
 *
 * The size of the window can be expressed as a ratio to screen size.
 */
RectSize CreateWindowProportional(float proportionalWidth, 
                                  float proportionalHeight);

/*
 * Pulls all events from the event queue and dispatches them.
 */
void ProcessEvents();

/*
 * Sets a pixel in the window back buffer.
 *
 * The origin of the coordinate system is the upper-left corner of the window.
 */
void SetColor(int x, int y, Color color);

/*
 * Draws the window back buffer to the screen.
 */
void Draw();

#endif
