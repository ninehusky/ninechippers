#ifndef _CHIP_H
#include "chip.h"
#endif

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

Chip *Chip_Initialize()
{
    Chip *chip = (Chip *)(calloc(1, sizeof(Chip)));
    chip->memory = calloc(MEMORY_SIZE, sizeof(uint8_t));
    return chip;
}

void Chip_Free(Chip *chip)
{
    free(chip->memory);
    free(chip);
}

void Chip_LoadROM(const char *filename)
{
    FILE* file = fopen(filename, "rb");
    if (!file) {
        fprintf(stderr, "Could not open %s\n.", filename);
    }
}