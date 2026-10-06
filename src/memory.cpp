// memory.cpp — YOUR WORK (Lab 1, M3).
#include "memory.hpp"

// Read the byte at `addr`. If `addr` is outside the box, return 0.
Byte mem_get(const Memory& mem, std::size_t addr) {
    if (addr >= MEM_SIZE) {
        return 0;
    }
    return mem.data[addr];
}

// Write `value` at `addr`. Return false if `addr` is outside the box.
bool mem_set(Memory& mem, std::size_t addr, Byte value) {
    if (addr >= MEM_SIZE) {
        return false;
    }
    mem.data[addr] = value;
    return true;
}