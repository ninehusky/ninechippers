// Sets up emulation cycle for the CHIP-8

#include <stdio.h>
#include <stdlib.h>

#include "chip.h"

#define TRUE 1 // holy shit

// Crashes program and prints error to stderr upon incorrect invocation
static void Usage();

int main(int argc, char const *argv[])
{
    if (argc != 2)
    {
        Usage(argv[0]);
    }

    Chip *chip = Initialize_Chip();
    LoadROM(chip, argv[1]);
    _PrintMemory(chip);
    Free_Chip(chip);

    // Fetch, decode, execute
    while (TRUE)
    {
    }

    return EXIT_SUCCESS;
}

void Usage()
{
    fprintf(stderr, "Usage: ./ninechippers <filename>\n");
    exit(EXIT_FAILURE);
}
