#ifndef DISPLAY_H_
#define DISPLAY_H_

#include <stdbool.h>
#include <SDL2/SDL.h>

#include "chip.h"

#define DISPLAY_SCALE 10

#define DISPLAY_TITLE "ninechipper"

typedef struct
{
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *texture;
} Display;

// Create and set up the SDL Window
Display *InitializeDisplay();

// Process game events, updates keyboard
bool ProcessEvents(Chip *chip);

// Render current state of Chip8 to screen
void RenderDisplay(Display *display, Chip *chip);

// Cleans up resources upon exit
void CleanUpDisplay(Display *display);

#endif