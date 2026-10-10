# ember — 4KB Computer & CPU Simulator

`ember` is an educational virtual machine and CPU simulator written in C++17 with strict compiler enforcement (`-Wall -Wextra -Werror` and AddressSanitizer/UBSan in Debug builds).

---

## 📦 Part 1: Lab 01 — A Box of Bytes (Memory Infrastructure)

### Overview
Lab 01 establishes the base 4KB flat memory storage and diagnostic tools for inspecting raw byte data.

### Given Infrastructure & Design
- **Memory Box:** Fixed array of 4096 bytes (`using Byte = std::uint8_t; const std::size_t MEM_SIZE = 4096;`).
- **Memory Functions:**
  - `mem_get(mem, addr)`: Reads a byte safely. Returns `0` if address is out of bounds (`addr >= 4096`).
  - `mem_set(mem, addr, val)`: Writes a byte safely. Returns `false` if address is out of bounds.
- **Diagnostics & Inspection:**
  - `dump()`: Hexdump visualization (16 bytes per row) showing Hex offset, Hex bytes, and an ASCII gutter printing printable characters or `.` for non-printable bytes.
  - `show_byte()`: Multi-format inspector showing a single byte in 4 views:
    - Decimal value (e.g., `65`)
    - Hexadecimal notation (e.g., `0x41`)
    - Binary notation (e.g., `0b01000001`)
    - ASCII character (e.g., `'A'`)

### Initial Lab 01 Terminal Session Example
```text
ember> set 0 65
ember> set 1 66
ember> get 0
65  0x41  0b01000001  'A'

ember> dump
0000  41 42 00 00 00 00 00 00 00 00 00 00 00 00 00 00  |AB..............|
```

---

## ⚙️ Part 2: Lab 02 — Bits Don't Lie (CPU, ALU & Flags)

### Overview
Lab 02 introduces a virtual 8-bit CPU, general-purpose registers, status flags (Z, N, C), and an Arithmetic Logic Unit (ALU).

### Architecture Additions
- **Registers:**
  - `PC` (16-bit Program Counter): Pointer to current memory address.
  - `A`, `B` (8-bit Registers): Data registers.
- **Status Flags:**
  - `Z` (Zero Flag): Set if operation result equals `0`.
  - `N` (Negative Flag): Set if bit 7 (MSB) of result is `1`.
  - `C` (Carry / Borrow Flag): Set on unsigned 8-bit overflow or underflow borrow.
- **CPU State:** `HALT` flag stops execution when opcode `0x01` is hit.
- **New Commands:**
  - `regs`: Prints CPU status (`PC A B Z N C HALT`).
  - `step`: Executes instruction at `mem[PC]` and increments `PC`.
  - `reg <a|b> <val>`: Directly modifies values in registers A or B.

### Supported Instruction Set Architecture (ISA)

| Opcode | Mnemonic | Operation | Flags Updated |
| :---: | :--- | :--- | :---: |
| `0x00` | `NOP` | No operation | None |
| `0x01` | `HALT` | Stop CPU execution | None |
| `0x10` | `ADD A, B` | `A = A + B` | Z, N, C |
| `0x11` | `SUB A, B` | `A = A - B` | Z, N, C |
| `0x12` | `AND A, B` | `A = A & B` | Z, N, C=0 |
| `0x13` | `OR A, B` | `A = A \| B` | Z, N, C=0 |
| `0x14` | `XOR A, B` | `A = A ^ B` | Z, N, C=0 |
| `0x15` | `NOT A` | `A = ~A` | Z, N, C=0 |
| `0x16` | `SHL A` | Shift Left (`A = A << 1`) | Z, N, C |
| `0x17` | `SHR A` | Shift Right (`A = A >> 1`) | Z, N, C |
| `0x18` | `INC A` | `A = A + 1` | Z, N, C |
| `0x19` | `DEC A` | `A = A - 1` | Z, N, C |

---

## 🧪 Worked Examples (ALU Overflow & Flags)

### 1. Addition Overflow (200 + 100 = 44, C = 1)
- **Input:** `A = 200` (`0xC8`), `B = 100` (`0x64`)
- **Instruction:** `ADD A, B` (`0x10`)
- **Calculation:** `200 + 100 = 300 = 0x12C % 256 = 44` (`0x2C`)
- **Result Flags:** `Z = 0`, `N = 0`, **`C = 1`** (since `300 > 255`).

### 2. Negative Result (10 - 20 = 246, N = 1, C = 1)
- **Input:** `A = 10` (`0x0A`), `B = 20` (`0x14`)
- **Instruction:** `SUB A, B` (`0x11`)
- **Calculation:** `10 - 20 = 246` (`0xF6`) in 8-bit Two's Complement
- **Result Flags:** `Z = 0`, **`N = 1`** (bit 7 set: `0b11110110`), **`C = 1`** (borrow).

---

## 💻 Full Lab 02 Terminal Session

```text
ember 0.2 - 4096 bytes of memory & CPU simulation. Type `help`.

ember> reg a 200
ember> reg b 100
ember> set 0 0x10
ember> regs
PC: 0000 | A: 0xc8 | B: 0x64 | Z: 0 N: 0 C: 0 | HALT: 0

ember> step
ember> regs
PC: 0001 | A: 0x2c | B: 0x64 | Z: 0 N: 0 C: 1 | HALT: 0
```

---

## 🛠️ Build and Run Instructions

```bash
# Configure build system
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug

# Compile executable
cmake --build build

# Execute
./build/ember.exe
```