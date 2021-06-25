// Sets up emulation cycle for the CHIP-8

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <SDL2/SDL.h>

#include "chip.h"
#include "opcodes.h"
#include "display.h"

#define WIDTH 640
#define HEIGHT 320

// Crashes program and prints error to stderr upon incorrect invocation
static void Usage();

int main(int argc, char const *argv[])
{
    if (argc != 2)
    {
        Usage(argv[0]);
    }

    Chip *chip = InitializeChip();
    LoadROM(chip, argv[1]);

    Display *display = InitializeDisplay();
    if (!display)
    {
        return EXIT_FAILURE;
    }

    bool running = true;
    while (running)
    {
        // Process events given by SDL
        if (!ProcessEvents(chip))
        {
            break;
        }
        // Fetch, decode, execute
        for (int i = MEMORY_START; i < MEMORY_SIZE; i++)
        {
            ExecuteOpcode(chip);
        }

        // Render to screen
        // TODO: if chip->draw_flag
        RenderDisplay(display, chip);
    }

    // Clean up resources
    CleanUpDisplay(display);
    FreeChip(chip);

    return EXIT_SUCCESS;
}

void Usage()
{
    fprintf(stderr, "Usage: ./ninechippers <filename>\n");
    exit(EXIT_FAILURE);
}
