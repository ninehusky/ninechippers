#include <stdio.h>

#include "opcodes.h"

// TODO: function table

void ExecuteOpcode(Chip *chip)
{
    opcode op = ((chip->memory[chip->program_counter] << 8) |
                 chip->memory[chip->program_counter + 1]);
    printf("Opcode: %04x\n", op);
    switch (op)
    {

    default:
        printf("Error: opcode %04x not implemented\n", op);
    }
    chip->program_counter += 2;
}
