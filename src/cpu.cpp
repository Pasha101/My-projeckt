#include "cpu.hpp"
#include "memory.hpp"
#include "alu.hpp"

#include <iostream>
#include <iomanip>

void print_regs(const Cpu& cpu) {
    std::cout << "PC: " << std::hex << std::setfill('0') << std::setw(4) << cpu.pc
              << " | A: 0x" << std::setw(2) << (int)cpu.a
              << " | B: 0x" << std::setw(2) << (int)cpu.b
              << std::dec
              << " | Z: " << cpu.flags.z
              << " N: " << cpu.flags.n
              << " C: " << cpu.flags.c
              << " | HALT: " << cpu.halted << "\n";
}

bool step(Cpu& cpu, Memory& mem) {
    if (cpu.halted) {
        std::cout << "CPU is halted.\n";
        return false;
    }

    if (cpu.pc >= MEM_SIZE) {
        std::cout << "PC out of bounds.\n";
        cpu.halted = true;
        return false;
    }

    Byte opcode = mem_get(mem, cpu.pc);
    cpu.pc++;

    switch (opcode) {
        case 0x00: // NOP
            break;
        case 0x01: // HALT
            cpu.halted = true;
            break;
        case 0x10: // ADD A, B
            cpu.a = alu_add(cpu.a, cpu.b, cpu.flags);
            break;
        case 0x11: // SUB A, B
            cpu.a = alu_sub(cpu.a, cpu.b, cpu.flags);
            break;
        case 0x12: // AND A, B
            cpu.a = alu_and(cpu.a, cpu.b, cpu.flags);
            break;
        case 0x13: // OR A, B
            cpu.a = alu_or(cpu.a, cpu.b, cpu.flags);
            break;
        case 0x14: // XOR A, B
            cpu.a = alu_xor(cpu.a, cpu.b, cpu.flags);
            break;
        case 0x15: // NOT A
            cpu.a = alu_not(cpu.a, cpu.flags);
            break;
        case 0x16: // SHL A
            cpu.a = alu_shl(cpu.a, cpu.flags);
            break;
        case 0x17: // SHR A
            cpu.a = alu_shr(cpu.a, cpu.flags);
            break;
        case 0x18: // INC A
            cpu.a = alu_inc(cpu.a, cpu.flags);
            break;
        case 0x19: // DEC A
            cpu.a = alu_dec(cpu.a, cpu.flags);
            break;
        default:
            std::cout << "Unknown opcode: 0x" << std::hex << (int)opcode << std::dec << "\n";
            return false;
    }

    return true;
}