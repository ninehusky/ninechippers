#ifndef _CHIP_H
#define _CHIP_H

#include <stdint.h>

#define NUM_REGISTERS 16
#define MEMORY_SIZE 4096
#define STACK_SIZE 16
#define MEMORY_START 0x200

typedef struct
{
    uint8_t registers[NUM_REGISTERS];
    uint16_t address_register;
    uint8_t delay_timer;
    uint8_t sound_timer;
    uint16_t program_counter;
    uint16_t stack[STACK_SIZE];
    uint8_t stack_pointer;
    uint8_t *memory;
    uint8_t *screen;
} Chip;

// Allocates and returns a pointer to a new Chip-8.
// In particular, initializes its values to a Chip-8
// that has not ran any ROM code.
Chip *Initialize_Chip();

// Frees the given Chip-8.
void Free_Chip(Chip *chip);

// Loads a ROM with the given filename into the Chip-8.
// Crashes if the ROM is too large, or if there is an
// error opening the ROM.
void LoadROM(Chip *chip, const char *filename);

// Prints the contents of the Chip-8's memory to stdout.
void _PrintMemory(Chip *chip);

#endif