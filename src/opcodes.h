#ifndef _OPCODES_H
#define _OPCODES_H

#include "chip.h"
#include "opcodes.h"

typedef uint16_t opcode;

// Executes the opcode pointed at by the Chip-8's program counter.
// Updates the Chip-8's state as a result.
void ExecuteOpcode(Chip *chip);


/******************************** OPCODES ***********************/
// Clear the display.
void ClearDisplay(Chip *chip);

// Return from a subroutine.
void ReturnFromSubroutine(Chip *chip);

// Jump to the address embedded within the opcode.
void JumpToOpcodeAddress(Chip *chip);

// Call subroutine embedded within the opcode.
void CallOpcodeSubroutine(Chip *chip);

// Skip next instruction if Vx = kk.
void SkipIfByteEqualToRegister(Chip *chip);

// Skip next instruction if Vx != kk.
void SkipIfByteNotEqualToRegister(Chip *chip);

// Skip next instruction if Vx = Vy.
void SkipIfRegistersEqual(Chip *chip);

// Set Vx = kk.
void SetRegisterToByte(Chip *chip);

// Set Vx = Vx + kk.
void AddByteToRegister(Chip *chip);

// Set Vx = Vy. 
void SetRegisterToRegister(Chip *chip);

// Performs an OR operation, i.e., Vx |= Vy.
void OrRegisters(Chip *chip);

// Performs an AND operation, i.e., Vx &= Vy.
void AndRegisters(Chip *chip);

// Performs an XOR operation, i.e., Vx ^= Vy.
void XorRegisters(Chip *chip);

// Set Vx = Vx + Vy, set VF = carry.
void AddRegisters(Chip *chip);

// Set Vx = Vx - Vy, set VF = NOT borrow.
void SubtractRegisters(Chip *chip);

// Set Vx = Vx >> 1.
void ShiftRegisterRight(Chip *chip);

// Set Vx = Vy - Vx, set VF = NOT borrow
void SubtractRegistersReverse(Chip *chip);

// Set Vx = Vx << 1
void ShiftRegisterLeft(Chip *chip);

// Skip next instruction if Vx != Vy.
void SkipIfUnequalRegisters(Chip *chip);

// Set I = nnn
void SetAddressRegister(Chip *chip);

// Jump to nnn + V0
void JumpToOpcodeRegisterSum(Chip *chip);

// Vx = random byte & kk
void RandomizeRegister(Chip *chip);

// Display n-byte sprite starting at something I won't worry about
// TODO: worry about it
void DisplaySprite(Chip *chip);

// Skip next instruction if key with value of Vx is pressed.
void SkipIfKeyPressed(Chip *chip);

// Skip next instruction if key with value of Vx is not pressed.
void SkipIfKeyNotPressed(Chip *chip);

// Set Vx = delay timer value.
void SetRegisterToDelayTimer(Chip *chip);

// Wait for key press, store value of key in Vx
void SetRegisterUponKeyPress(Chip *chip);

// Set delay timer to Vx
void SetDelayTimerToRegister(Chip *chip);

// Set sound timer to Vx
void SetSoundTimerToRegister(Chip *chip);

// I += Vx
void AddToAddressRegister(Chip *chip);

// I = location of sprite for digit Vx
void SetAddressRegisterToSprite(Chip *chip);

// store bcd representation of Vx in memory locations at
// I, I + 1, and I + 2.
void StoreBCDRepresentation(Chip *chip);

// Store registers V0 through Vx in memory starting at I
void StoreRegisters(Chip *chip);

// Read into registers V0 through Vx in memory starting at I
void ReadRegisters(Chip *chip);

#endif