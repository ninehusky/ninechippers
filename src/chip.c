#include "chip.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// Checks that a file at the given filename exists,
// and is a suitable size for the CHIP-8 machine.
// Returns file pointer if the file exists, as well as
// setting the output parameter. Otherwise crashes.
static FILE *CheckValidROM(const char *filename, int *file_size);

// Loads the font set into the Chip-8.
static void LoadFontSet(Chip *chip);

static const uint8_t FONT_SET[FONT_SET_LENGTH] =
    {
        0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
        0x20, 0x60, 0x20, 0x20, 0x70, // 1
        0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
        0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
        0x90, 0x90, 0xF0, 0x10, 0x10, // 4
        0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
        0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
        0xF0, 0x10, 0x20, 0x40, 0x40, // 7
        0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
        0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
        0xF0, 0x90, 0xF0, 0x90, 0x90, // A
        0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
        0xF0, 0x80, 0x80, 0x80, 0xF0, // C
        0xE0, 0x90, 0x90, 0x90, 0xE0, // D
        0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
        0xF0, 0x80, 0xF0, 0x80, 0x80  // F
};

Chip *InitializeChip()
{
    Chip *chip = (Chip *)(calloc(1, sizeof(Chip)));
    chip->program_counter = MEMORY_START;
    // TODO: assume registers and stack are part of struct?
    chip->memory = calloc(MEMORY_SIZE, sizeof(uint8_t));
    LoadFontSet(chip);
    return chip;
}

void FreeChip(Chip *chip)
{
    free(chip->memory);
    free(chip);
}

void LoadROM(Chip *chip, const char *filename)
{
    int file_size;
    FILE *rom = CheckValidROM(filename, &file_size);
    uint8_t *memory = chip->memory;
    // Load ROM into RAM
    // TODO: Error check both these function calls
    fread(memory + MEMORY_START, file_size, 1, rom);
    fclose(rom);
}

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

void _PrintMemory(Chip *chip)
{
    for (uint8_t *curr = chip->memory + MEMORY_START;
         curr < chip->memory + MEMORY_SIZE;
         curr++)
    {
        printf("%02x ", *curr);
    }
}

static void LoadFontSet(Chip *chip)
{
    for (int i = 0; i < FONT_SET_LENGTH; i++)
    {
        chip->memory[i + FONT_SET_START] = FONT_SET[i];
    }
}