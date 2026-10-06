// dump.cpp — hex + ASCII, like the Unix tool `hexdump -C`.
#include "dump.hpp"

#include <iomanip>
#include <iostream>

const std::size_t BYTES_PER_LINE = 16;

static bool is_printable(Byte b) { return b >= 0x20 && b <= 0x7E; }

void dump(const Memory& mem) {
    for (std::size_t row = 0; row < MEM_SIZE; row += BYTES_PER_LINE) {

        // The address column: 0000, 0010, 0020, ...
        std::cout << std::hex << std::setfill('0') << std::setw(4) << row << "  ";

        // The hex column: 16 bytes, two digits each.
        for (std::size_t col = 0; col < BYTES_PER_LINE; ++col) {
            Byte b = mem.data[row + col];
            std::cout << std::setw(2) << (int)b << ' ';
        }

        std::cout << " |";

        // The ASCII gutter.
        for (std::size_t col = 0; col < BYTES_PER_LINE; ++col) {
            Byte b = mem.data[row + col];
            if (is_printable(b)) {
                std::cout << b;
            } else {
                std::cout << '.';
            }
        }

        std::cout << "|\n";
    }

    std::cout << std::dec << std::setfill(' ');
}

void show_byte(Byte b) {
    // 1. Decimal representation
    std::cout << (int)b << "  ";

    // 2. Hexadecimal representation (0x..)
    std::cout << "0x" << std::hex << std::setfill('0') << std::setw(2) << (int)b << std::dec << "  ";

    // 3. Binary representation (0b........)
    std::cout << "0b";
    for (int i = 7; i >= 0; --i) {
        std::cout << ((b >> i) & 1);
    }
    std::cout << "  ";

    // 4. Character representation in quotes ('A' or '.')
    char ch = is_printable(b) ? (char)b : '.';
    std::cout << '\'' << ch << "'\n";
}