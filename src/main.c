// Sets up emulation cycle for the CHIP-8

#include <stdio.h>
#include <stdlib.h>

#include "chip.h"

// Crashes program and prints error to stderr upon incorrect invocation
static void Usage();

int main(int argc, char const *argv[])
{
    if (argc != 2)
    {
        Usage(argv[0]);
    }

    Chip *chip = Chip_Initialize();
    Chip_LoadROM(chip, argv[1]);
    Chip_Free(chip);

    return EXIT_SUCCESS;
}

void Usage()
{
    fprintf(stderr, "Usage: ./ninechippers <filename>\n");
    exit(EXIT_FAILURE);
}
