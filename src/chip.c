#ifndef _CHIP_H
#include "chip.h"
#endif

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static FILE *CheckValidROM(const char *filename, int *file_size);

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

void Chip_LoadROM(Chip *chip, const char *filename)
{
    int file_size;
    FILE *rom = CheckValidROM(filename, &file_size);
    uint8_t *memory = chip->memory;
    // Load ROM into RAM
    // TODO: Error check both these function calls
    fread(memory + MEMORY_START, file_size, 1, rom);
    fclose(rom);
}

// Checks that a file at the given filename exists,
// and is a suitable size for the CHIP-8 machine.
// Returns file pointer if the file exists, as well as
// setting the output parameter. Otherwise crashes.
FILE *CheckValidROM(const char *filename, int *file_size)
{
    FILE *file = fopen(filename, "rb");
    // Check for errors opening the file
    if (file == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", filename);
        exit(EXIT_FAILURE);
    }

    // Check that ROM has valid size
    fseek(file, 0L, SEEK_END);
    int rom_size = ftell(file);
    if (rom_size > MEMORY_SIZE - MEMORY_START)
    {
        fclose(file);
        fprintf(stderr, "%s is too large!\n", filename);
        exit(EXIT_FAILURE);
    }
    fseek(file, 0L, SEEK_SET);
    *file_size = rom_size;
    return file;
}