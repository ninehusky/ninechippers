#include <SDL2/SDL.h>
#include <stdint.h>

#include "display.h"

Display *InitializeDisplay()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        fprintf(stderr, "error initializing SDL: %s\n", SDL_GetError());
        return NULL;
    }

    Display *display = (Display *)(malloc(sizeof(Display)));

    SDL_Window *win = SDL_CreateWindow(DISPLAY_TITLE, SDL_WINDOWPOS_CENTERED,
                                       SDL_WINDOWPOS_CENTERED,
                                       DISPLAY_WIDTH_IN_PIXELS * DISPLAY_SCALE,
                                       DISPLAY_HEIGHT_IN_PIXELS * DISPLAY_SCALE,
                                       SDL_WINDOW_OPENGL);
    if (!win)
    {
        fprintf(stderr, "error creating window: %s\n", SDL_GetError());
        return NULL;
    }

    display->window = win;

    SDL_Renderer *renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);

    if (!renderer)
    {
        fprintf(stderr, "error creating renderer: %s\n", SDL_GetError());
        return NULL;
    }

    display->renderer = renderer;

    SDL_Texture *texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC,
                                             DISPLAY_WIDTH_IN_PIXELS, DISPLAY_HEIGHT_IN_PIXELS);
    if (!texture)
    {
        fprintf(stderr, "error creating texture: %s\n", SDL_GetError());
        return NULL;
    }
    display->texture = texture;

    SDL_RenderClear(renderer);
    return display;
}

bool ProcessEvents(Chip *chip)
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            return false;
        }
    }
    return true;
}

void RenderDisplay(Display *display, Chip *chip)
{
    SDL_RenderClear(display->renderer);
    SDL_Rect rect;
    for (int i = 0; i < DISPLAY_HEIGHT_IN_PIXELS; i++)
    {
        for (int j = 0; j < DISPLAY_WIDTH_IN_PIXELS; j++)
        {
            uint8_t current_pixel = chip->screen[i][j];
            rect.x = i * DISPLAY_SCALE;
            rect.y = j * DISPLAY_SCALE;
            rect.w = DISPLAY_SCALE;
            rect.h = DISPLAY_SCALE;
            if (current_pixel == 0x1)
            {
                SDL_SetRenderDrawColor(display->renderer, 0xff, 0xff, 0xff, SDL_ALPHA_OPAQUE);
            }
            else
            {
                SDL_SetRenderDrawColor(display->renderer, 0x0, 0x0, 0x0, SDL_ALPHA_OPAQUE);
            }
            SDL_RenderDrawRect(display->renderer, &rect);
        }
    }
    SDL_RenderPresent(display->renderer);
}

void CleanUpDisplay(Display *display)
{
    SDL_DestroyTexture(display->texture);
    SDL_DestroyRenderer(display->renderer);
    SDL_DestroyWindow(display->window);
    SDL_Quit();
    free(display);
}