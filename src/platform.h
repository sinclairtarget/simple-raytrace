/*
 * Defines the platform-agnostic windowing and drawing API.
 */

// The size of a rectangle.
typedef struct {
    int width;
    int height;
} RectSize;

/*
 * Perform platform-specific initialization. 
 *
 * This must be called before anything else!
 */
void init();

/*
 * Creates and shows a window. Returns the window dimensions as a RectSize.
 *
 * The size of the window can be expressed as a ratio to screen size.
 */
RectSize createWindow(float proportionalWidth, float proportionalHeight);

/*
 * Pulls all events from the event queue and dispatches them.
 */
void processEvents();

/*
 * Draws a pixel in the window.
 *
 * The origin of the coordinate system is the lower-left corner of the window.
 */
void draw(int x, int y, float r, float g, float b, float a);
