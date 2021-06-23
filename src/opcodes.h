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
void cls(Chip *chip);

// Return from a subroutine.
void ret(Chip *chip);

// Jump to the address embedded within the opcode.
void jp_addr(Chip *chip);

// Call subroutine embedded within the opcode.
void call_addr(Chip *chip);

// Skip next instruction if Vx = kk.
void skip_equal(Chip *chip);

// Skip next instruction if Vx != kk.
void skip_unequal(Chip *chip);

// Skip next instruction if Vx = Vy.
void skip_equal_registers(Chip *chip);

// Set Vx = kk.
void set_register_to_byte(Chip *chip);

// Set Vx = Vx + kk.
void add_byte(Chip *chip);

// Set Vx = Vy. 
void set_register_to_register(Chip *chip);

// Performs an OR operation, i.e., Vx |= Vy.
void or_registers(Chip *chip);

// Performs an AND operation, i.e., Vx &= Vy.
void and_registers(Chip *chip);

// Performs an XOR operation, i.e., Vx ^= Vy.
void and_registers(Chip *chip);

// Set Vx = Vx + Vy, set VF = carry.
void add_registers(Chip *chip);

// Set Vx = Vx - Vy, set VF = NOT borrow.
void sub_registers(Chip *chip);

// Set Vx = Vx >> 1.
void shift_right(Chip *chip);

// Set Vx = Vy - Vx, set VF = NOT borrow
void subn_registers(Chip *chip);

// Set Vx = Vx << 1
void shift_left(Chip *chip);

// Skip next instruction if Vx != Vy.
void skip_unequal_registers(Chip *chip);

// Set I = nnn
void set_address_register(Chip *chip);

// Jump to nnn + V0
void jump_with_register(Chip *chip);

// Vx = random byte & kk
void randomize_register(Chip *chip);

// Display n-byte sprite starting at something I won't worry about
// TODO: worry about it
void display_sprite(Chip *chip);

// Skip next instruction if key with value of Vx is pressed.
void skip_if_pressed(Chip *chip);

// Skip next instruction if key with value of Vx is not pressed.
void skip_if_not_pressed(Chip *chip);

// Set Vx = delay timer value.
void set_register_to_delay_timer(Chip *chip);

// Wait for key press, store value of key in Vx
void store_key_in_register(Chip *chip);

// Set delay timer to Vx
void set_delay_timer_to_register(Chip *chip);

// Set sound timer to Vx
void set_sound_timer_to_register(Chip *chip);

// I += Vx
void add_to_address_register(Chip *chip);

// I = location of sprite for digit Vx
void set_address_register_to_sprite(Chip *chip);

// store bcd representation of Vx in memory locations at
// I, I + 1, and I + 2.
void store_bcd_representation(Chip *chip);

// Store registers V0 through Vx in memory starting at I
void store_registers(Chip *chip);

// Read into registers V0 through Vx in memory starting at I
void read_registers(Chip *chip);



#endif