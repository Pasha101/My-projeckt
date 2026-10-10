#pragma once

#include <cstdint>
#include "memory.hpp"

// CPU Status Flags
struct Flags {
    bool z{false}; // Zero flag (set if result is 0)
    bool n{false}; // Negative flag (set if bit 7 of result is 1)
    bool c{false}; // Carry flag (set if unsigned overflow occurs)
};

// Helper function to update Z and N flags based on 8-bit result
void update_zn_flags(Flags& flags, Byte result);

// ALU operations (operate on 8-bit values and update flags)
Byte alu_add(Byte a, Byte b, Flags& flags);
Byte alu_sub(Byte a, Byte b, Flags& flags);
Byte alu_and(Byte a, Byte b, Flags& flags);
Byte alu_or(Byte a, Byte b, Flags& flags);
Byte alu_xor(Byte a, Byte b, Flags& flags);
Byte alu_not(Byte a, Flags& flags);
Byte alu_shl(Byte a, Flags& flags);
Byte alu_shr(Byte a, Flags& flags);
Byte alu_inc(Byte a, Flags& flags);
Byte alu_dec(Byte a, Flags& flags);