// Sets up emulation cycle for the CHIP-8

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <SDL2/SDL.h>

#include "chip.h"
#include "opcodes.h"

#define WIDTH
#define HEIGHT

// Crashes program and prints error to stderr upon incorrect invocation
static void Usage();

int main(int argc, char const *argv[])
{
    if (argc != 2)
    {
        Usage(argv[0]);
    }

    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        fprintf(stderr, "SDL couldn't initialize.\n");
    }

    SDL_Window *window = SDL_CreateWindow("ninechipper", SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          100, 100, SDL_WINDOW_OPENGL);

    bool running = true;
    while (running)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                running = false;
                break;
            }
        }
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    // Chip *chip = Initialize_Chip();
    // LoadROM(chip, argv[1]);
    // // _PrintMemory(chip);

    // // Fetch, decode, execute
    // for (int i = MEMORY_START; i < MEMORY_SIZE; i++)
    // {
    //     ExecuteOpcode(chip);
    // }

    // Free_Chip(chip);

    return EXIT_SUCCESS;
}

void Usage()
{
    fprintf(stderr, "Usage: ./ninechippers <filename>\n");
    exit(EXIT_FAILURE);
}
