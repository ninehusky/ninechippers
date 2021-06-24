#include <stdio.h>
#include <stdlib.h>

#include "opcodes.h"
#include "chip.h"

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

// Performs reg[lhs] -= reg[rhs], VF = borrow
static void _subtract(Chip *chip, int lhs_index, int rhs_index);

void ExecuteOpcode(Chip *chip)
{
    opcode op = _get_opcode(chip);
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

// 8xy1 - OR Vx, Vy
// Vx |= Vy
void OrRegisters(Chip *chip, opcode op)
{
    chip->registers[_get_x(op)] |= chip->registers[_get_y(op)];
}

// 8xy2 - AND Vx, Vy
// Vx &= Vy
void AndRegisters(Chip *chip, opcode op)
{
    chip->registers[_get_x(op)] &= chip->registers[_get_y(op)];
}

// 8xy3 - XOR Vx, Vy
// Vx ^= Vy
void XorRegisters(Chip *chip, opcode op)
{
    chip->registers[_get_x(op)] ^= chip->registers[_get_y(op)];
}

// 8xy4 - ADD Vx, Vy
// Vx = Vx + Vy, VF = carry
void AddRegisters(Chip *chip, opcode op)
{
    uint16_t sum = chip->registers[_get_x(op)] +
                   chip->registers[_get_y(op)];
    chip->registers[_get_x(op)] = sum;         // lossy conversion?
    chip->registers[0xF] = ((sum >> 4) & 0x1); // this should really be 1.
}

// 8xy5 - SUB Vx, Vy
// Vx = Vx - Vy, VF = NOT borrow
// If Vx > Vy, then VF is set to 1, otherwise 0.
// Then Vy is subtracted from Vx, and the results stored in Vx.
void SubtractRegisters(Chip *chip, opcode op)
{
    _subtract(chip, _get_x(op), _get_y(op));
}

// 8xy6 - SHR Vx, Vy
// VF is set to LSB of Vx, then VF >>= 1 (divide VF by 2)
void ShiftRegisterRight(Chip *chip, opcode op)
{
    chip->registers[0xF] = chip->registers[_get_x(op)] & 0x1;
    chip->registers[_get_x(op)] >>= 0x1;
}

// 8xy7 - SUBN Vx, Vy
// Vx = Vy - Vx, set VF = NOT borrow
void SubtractRegistersReverse(Chip *chip, opcode op)
{
    _subtract(chip, _get_y(op), _get_x(op));
}

// 8xy7 - SHL Vx, Vy
// Vx = Vx << 1, VF = MSB of Vx
void ShiftRegisterLeft(Chip *chip, opcode op)
{
    chip->registers[0xF] = ((chip->registers[_get_x(op)] & 0x80) >> 7);
    chip->registers[_get_x(op)] <<= 1;
}

// 9xy0 - SNE Vx, Vy
// The values of Vx and Vy are compared, and if they are not equal,
// the program counter is increased by 2.
void SkipIfUnequalRegisters(Chip *chip, opcode op)
{
    if (chip->registers[_get_x(op)] != chip->registers[_get_y(op)])
    {
        chip->program_counter += 2;
    }
}

// Annn - LD I, addr
// Set I = nnn
void SetAddressRegister(Chip *chip, opcode op)
{
    chip->address_register = _get_nnn(op);
}

// Bnnn - JP V0, addr
// Jump to location nnn + V0
void JumpToOpcodeRegisterSum(Chip *chip, opcode op)
{
    chip->program_counter = _get_nnn(op) + chip->registers[0x0];
}

// Cxkk - RND Vx, Byte
// Vx = random byte & kk
void RandomizeRegister(Chip *chip, opcode op)
{
    uint8_t kk = _get_byte(op);
    chip->registers[_get_x(op)] = rand() & kk;
}

// Dxyn - DRW Vx, Vy, nibble
//
// The interpreter reads n bytes from memory, starting at the address
// stored in I. These bytes are then displayed as sprites on screen at
// coordinates (Vx, Vy). Sprites are XORed onto the existing screen.
// If this causes any pixels to be erased, VF is set to 1,
// otherwise it is set to 0. If the sprite is positioned so part of it
// is outside the coordinates of the display, it wraps around to the
// opposite side of the screen.
void DisplaySprite(Chip *chip, opcode op)
{
}

// Ex9E - SKP Vx
// Skip next instruction if key with value of Vx is pressed.
void SkipIfKeyPressed(Chip *chip, opcode op)
{
}

// ExA1 - SKNP Vx
// Skip next instruction if key with value of Vx is not pressed.
void SkipIfKeyNotPressed(Chip *chip, opcode op)
{
}

// Fx07 - LD Vx, DT
// Set Vx = delay timer
void SetRegietserToDelayTimer(Chip *chip, opcode op)
{
    chip->registers[_get_x(op)] = chip->delay_timer;
}

// Fx0A - LD Vx, K
// Wait for a key press, then store the value of the key in Vx.
void SetRegisterUponKeyPress(Chip *chip, opcode op)
{
}

// Fx15 - LD DT, Vx
// Set delay timer = Vx.
// DT is set equal to the value of Vx.
void SetDelayTimerToRegister(Chip *chip, opcode op)
{
    chip->delay_timer = chip->registers[_get_x(op)];
}

// Fx18 - LD ST, Vx
// Set sound timer = Vx.
// ST is set equal to the value of Vx.
void SetSoundTimerToRegister(Chip *chip, opcode op)
{
    chip->sound_timer = chip->registers[_get_x(op)];
}

// Fx1E - ADD I, Vx
// Set I = I + Vx.
// The values of I and Vx are added, and the results are stored in I.
void AddToAddressRegister(Chip *chip, opcode op)
{
    chip->address_register += chip->registers[_get_x(op)];
}

// Fx29 - LD F, Vx
// Set I = location of sprite for digit Vx.
// The value of I is set to the location for the hexadecimal
// sprite corresponding to the value of Vx.
void SetAddressRegisterToSprite(Chip *chip, opcode op)
{
    uint16_t addr = FONT_SET_START +
                    FONT_SPRITE_SIZE * chip->registers[_get_x(op)];
    chip->address_register = addr;
}

// Fx33 - LD B, Vx
// Store BCD representation of Vx in memory locations I, I+1, and I+2.
// The interpreter takes the decimal value of Vx,
// and places the hundreds digit in memory at location in I,
// the tens digit at location I+1, and the ones digit at location I+2.
void StoreBCDRepresentation(Chip *chip, opcode op)
{
    uint8_t value = chip->registers[_get_x(op)];
    chip->memory[chip->address_register] = ((value / 100) % 10);
    chip->memory[chip->address_register + 1] = ((value / 10) % 10);
    chip->memory[chip->address_register + 2] = (value % 10);
}

// Fx55 - LD [I], Vx
// Store registers V0 through Vx in memory starting at location I.
// The interpreter copies the values of registers V0 through Vx into
// memory, starting at the address in I.
void StoreRegisters(Chip *chip, opcode op)
{
    uint8_t last_index = _get_x(op);
    for (int i = 0; i <= last_index; i++)
    {
        chip->memory[chip->address_register + i] = chip->registers[i];
    }
}

// Fx65 - LD Vx, [I]
// Read registers V0 through Vx from memory starting at location I.
// The interpreter reads values from memory starting at location I
// into registers V0 through Vx.
void ReadRegisters(Chip *chip, opcode op)
{
    uint8_t last_index = _get_x(op);
    for (int i = 0; i <= last_index; i++)
    {
        chip->registers[i] = chip->memory[chip->address_register + i];
    }
}

// HELPER FUNCTION MAYHEM:

static opcode _get_opcode(Chip *chip)
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

// Performs reg[lhs] -= reg[rhs], VF = borrow
static void _subtract(Chip *chip, int lhs_index, int rhs_index)
{
    uint8_t lh_value = chip->registers[lhs_index];
    uint8_t rh_value = chip->registers[rhs_index];
    chip->registers[0xF] = lh_value > rh_value; // TODO: uh oh
    chip->registers[lhs_index] -= chip->registers[rhs_index];
}
