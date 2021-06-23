#include <stdio.h>

#include "opcodes.h"

// TODO: function table

// Returns opcode pointed at by the chip's program counter
static opcode _get_opcode(Chip *chip);

// Returns lowest 12 bits of instruction, usually an address
static uint8_t _get_nnn(opcode op);

// Returns lowest 4 bits of instruction
static uint8_t _get_nibble(opcode op);

// Returns lower 4 bits of the high byte of the instruction
static uint8_t _get_x(opcode op);

// Returns upper 4 bits of the low byte of the instruction
static uint8_t _get_y(opcode op);

// Returns lowest 8 bits of instruction
static uint8_t _get_byte(opcode op);

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

// 00E0 - CLS

// 00EE - RET
// The interpreter sets the program counter to the address at
// the top of the stack, then subtracts 1 from the
// stack pointer.
void ReturnFromSubroutine(Chip *chip, opcode op)
{
    chip->program_counter = chip->stack[chip->stack_pointer];
    chip->stack_pointer--;
}

// 1nnn - JP addr
// Sets program counter to nnn (addr)
void JumpToOpcodeAddress(Chip *chip, opcode op)
{
    chip->program_counter = _get_nnn(op);
}

// 2nnn - CALL addr
// The interpreter increments the stack pointer,
// then puts the current PC on the top of the stack.
// The PC is then set to nnn.
void CallOpcodeSubroutine(Chip *chip, opcode op)
{
    chip->stack_pointer++;
    chip->stack[chip->stack_pointer] = chip->program_counter;
    chip->program_counter = _get_nnn(op);
}

// 3xkk - SE Vx, byte
// Skip next instruction if Vx = kk.
void SkipIfByteEqualToRegister(Chip *chip, opcode op)
{
    uint8_t register_value = chip->registers[_get_x(op)];
    uint8_t kk = _get_byte(op);
    if (register_value == kk)
    {
        chip->program_counter += 2;
    }
}

// 4xkk - SE Vx, byte
// Skip next instruction if Vx != kk.
void SkipIfByteNotEqualToRegister(Chip *chip, opcode op)
{
    uint8_t register_value = chip->registers[_get_x(op)];
    uint8_t kk = _get_byte(op);
    if (register_value != kk)
    {
        chip->program_counter += 2;
    }
}

// 5xy0 - SE Vx, Vy
// If Vx = Vy, increments the program counter by 2.
void SkipIfRegistersEqual(Chip *chip, opcode op)
{
    uint8_t x_value = chip->registers[_get_x(op)];
    uint8_t y_value = chip->registers[_get_y(op)];
    if (x_value == y_value)
    {
        chip->program_counter += 2;
    }
}

// 6xkk - LD Vx, byte
// Set Vx = kk.
// The interpreter puts the value kk into register Vx.
void SetRegisterToByte(Chip *chip, opcode op)
{
    uint8_t x = _get_x(op);
    uint8_t kk = _get_byte(op);
    chip->registers[x] = kk;
}

// 7xkk - ADD Vx, byte
// Set Vx = Vx + kk.
// Adds the value kk to the value of register Vx,
// then stores the result in Vx.
void AddByteToRegister(Chip *chip, opcode op)
{
    uint8_t byte = _get_byte(op);
    chip->registers[_get_x(op)] += byte;
}

// 8xy0 - LD Vx, Vy
// Set Vx = Vy.
// Stores the value of register Vy in register Vx.
void SetRegisterToRegister(Chip *chip, opcode op)
{
    chip->registers[_get_x(op)] = chip->registers[_get_y(op)];
}

// HELPER FUNCTION MAYHEM:

static opcode _GetOpcode(Chip *chip)
{
    opcode op = ((chip->memory[chip->program_counter] << 8) |
                 chip->memory[chip->program_counter + 1]);
    return op;
}

static uint8_t _get_nnn(opcode op)
{
    return (op & 0xFFF);
}

static uint8_t _get_nibble(opcode op)
{
    return (op & 0xF);
}

static uint8_t _get_x(opcode op)
{
    return ((op & 0xF00) >> 8);
}

static uint8_t _get_y(opcode op)
{
    return ((op & 0xF0) >> 4);
}

static uint8_t _get_byte(opcode op)
{
    return (op & 0xFF);
}
