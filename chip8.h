#include <cstdint>

class Chip8{
public:
    uint8_t registers[16]{};
    uint8_t memory[4096]{};
    uint16_t programCounter{};
    uint32_t graphics[64 * 32]{};
    uint16_t opcode;
    char const *instructions[36]{
        "00e0",
        "00ee",
        "0xxx",
        "1xxx",
        "2xxx",
        "3xxx",
        "4xxx",
        "5xx0",
        "6xxx",
        "7xxx",
        "8xx0",
        "8xx1",
        "8xx2",
        "8xx3",
        "8xx4",
        "8xx5",
        "8xx6",
        "8xx7",
        "8xxe",
        "9xx0",
        "axxx",
        "bxxx",
        "cxxx",
        "dxxx",
        "ex9e",
        "exa1",
        "fx07",
        "fx0a",
        "fx15",
        "fx18",
        "fx1e",
        "fx29",
        "fx33",
        "fx55",
        "fx65",
    };
    Chip8();
    void Increment();
    void LoadROM(char const *filename);
};