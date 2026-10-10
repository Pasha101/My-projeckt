#include "alu.hpp"

void update_zn_flags(Flags& flags, Byte result) {
    flags.z = (result == 0);
    flags.n = ((result & 0x80) != 0); // Check bit 7
}

Byte alu_add(Byte a, Byte b, Flags& flags) {
    uint16_t res = static_cast<uint16_t>(a) + static_cast<uint16_t>(b);
    flags.c = (res > 0xFF);
    Byte result = static_cast<Byte>(res & 0xFF);
    update_zn_flags(flags, result);
    return result;
}

Byte alu_sub(Byte a, Byte b, Flags& flags) {
    flags.c = (a < b); // Borrow flag
    Byte result = static_cast<Byte>(a - b);
    update_zn_flags(flags, result);
    return result;
}

Byte alu_and(Byte a, Byte b, Flags& flags) {
    Byte result = a & b;
    flags.c = false;
    update_zn_flags(flags, result);
    return result;
}

Byte alu_or(Byte a, Byte b, Flags& flags) {
    Byte result = a | b;
    flags.c = false;
    update_zn_flags(flags, result);
    return result;
}

Byte alu_xor(Byte a, Byte b, Flags& flags) {
    Byte result = a ^ b;
    flags.c = false;
    update_zn_flags(flags, result);
    return result;
}

Byte alu_not(Byte a, Flags& flags) {
    Byte result = ~a;
    flags.c = false;
    update_zn_flags(flags, result);
    return result;
}

Byte alu_shl(Byte a, Flags& flags) {
    flags.c = ((a & 0x80) != 0); // High bit shifted out becomes carry
    Byte result = static_cast<Byte>(a << 1);
    update_zn_flags(flags, result);
    return result;
}

Byte alu_shr(Byte a, Flags& flags) {
    flags.c = ((a & 0x01) != 0); // Low bit shifted out becomes carry
    Byte result = static_cast<Byte>(a >> 1);
    update_zn_flags(flags, result);
    return result;
}

Byte alu_inc(Byte a, Flags& flags) {
    return alu_add(a, 1, flags);
}

Byte alu_dec(Byte a, Flags& flags) {
    return alu_sub(a, 1, flags);
}