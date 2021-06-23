#include <stdio.h>

#include "opcodes.h"

void ExecuteOpcode(Chip *chip)
{
    opcode op = ((chip->memory[chip->program_counter] << 8) |
                 chip->memory[chip->program_counter + 1]);
    printf("Opcode: %04x\n", op);
    chip->program_counter += 2;
}