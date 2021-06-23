// TODO: update the makefile lol

#include <stdint.h>

#define NUM_REGISTERS 16

#define MEMORY_SIZE 4096

typedef struct
{
    uint8_t registers[NUM_REGISTERS];
    uint16_t address_register;
    uint8_t delay_timer;
    uint8_t sound_timer;
    uint16_t program_counter;
    uint8_t stack_pointer;
    uint8_t *memory;
    uint8_t *screen;
} Chip;

// Allocates and returns a pointer to a new Chip-8.
// In particular, initializes its values to a Chip-8
// that has not ran any ROM code.
Chip *Chip_Initialize();

void Chip_Free(Chip *chip);

void Chip_LoadROM(const char* filename);
