#ifndef _OPCODES_H
#define _OPCODES_H

#include "chip.h"
#include "opcodes.h"

// Executes the opcode pointed at by the Chip-8's program counter.
// Updates the Chip-8's state as a result.
void ExecuteOpcode(Chip *chip);

typedef uint16_t opcode;

/******************************** OPCODES ***********************/
// Clear the display.
void ClearDisplay(Chip *chip, opcode op);

// Return from a subroutine.
void ReturnFromSubroutine(Chip *chip, opcode op);

// Jump to the address embedded within the opcode.
void JumpToOpcodeAddress(Chip *chip, opcode op);

// Call subroutine embedded within the opcode.
void CallOpcodeSubroutine(Chip *chip, opcode op);

// Skip next instruction if Vx = kk.
void SkipIfByteEqualToRegister(Chip *chip, opcode op);

// Skip next instruction if Vx != kk.
void SkipIfByteNotEqualToRegister(Chip *chip, opcode op);

// Skip next instruction if Vx = Vy.
void SkipIfRegistersEqual(Chip *chip, opcode op);

// Set Vx = kk.
void SetRegisterToByte(Chip *chip, opcode op);

// Set Vx = Vx + kk.
void AddByteToRegister(Chip *chip, opcode op);

// Set Vx = Vy. 
void SetRegisterToRegister(Chip *chip, opcode op);

// Performs an OR operation, i.e., Vx |= Vy.
void OrRegisters(Chip *chip, opcode op);

// Performs an AND operation, i.e., Vx &= Vy.
void AndRegisters(Chip *chip, opcode op);

// Performs an XOR operation, i.e., Vx ^= Vy.
void XorRegisters(Chip *chip, opcode op);

// Set Vx = Vx + Vy, set VF = carry.
void AddRegisters(Chip *chip, opcode op);

// Set Vx = Vx - Vy, set VF = NOT borrow.
void SubtractRegisters(Chip *chip, opcode op);

// Set Vx = Vx >> 1.
void ShiftRegisterRight(Chip *chip, opcode op);

// Set Vx = Vy - Vx, set VF = NOT borrow
void SubtractRegistersReverse(Chip *chip, opcode op);

// Set Vx = Vx << 1
void ShiftRegisterLeft(Chip *chip, opcode op);

// Skip next instruction if Vx != Vy.
void SkipIfUnequalRegisters(Chip *chip, opcode op);

// Set I = nnn
void SetAddressRegister(Chip *chip, opcode op);

// Jump to nnn + V0
void JumpToOpcodeRegisterSum(Chip *chip, opcode op);

// Vx = random byte & kk
void RandomizeRegister(Chip *chip, opcode op);

// Display n-byte sprite pointed at by Chip's address register
void DisplaySprite(Chip *chip, opcode op);

// Skip next instruction if key with value of Vx is pressed.
void SkipIfKeyPressed(Chip *chip, opcode op);

// Skip next instruction if key with value of Vx is not pressed.
void SkipIfKeyNotPressed(Chip *chip, opcode op);

// Set Vx = delay timer value.
void SetRegisterToDelayTimer(Chip *chip, opcode op);

// Wait for key press, store value of key in Vx
void SetRegisterUponKeyPress(Chip *chip, opcode op);

// Set delay timer to Vx
void SetDelayTimerToRegister(Chip *chip, opcode op);

// Set sound timer to Vx
void SetSoundTimerToRegister(Chip *chip, opcode op);

// I += Vx
void AddToAddressRegister(Chip *chip, opcode op);

// I = location of sprite for digit Vx
void SetAddressRegisterToSprite(Chip *chip, opcode op);

// store bcd representation of Vx in memory locations at
// I, I + 1, and I + 2.
void StoreBCDRepresentation(Chip *chip, opcode op);

// Store registers V0 through Vx in memory starting at I
void StoreRegisters(Chip *chip, opcode op);

// Read into registers V0 through Vx in memory starting at I
void ReadRegisters(Chip *chip, opcode op);

#endif