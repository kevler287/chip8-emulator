#include <cstdint>
#include <map>
#include <string>

class Chip8
{
public:
    uint8_t registers[16]{};
    uint16_t indexRegister{};
    uint16_t programCounter{};
    uint16_t stack[16]{};
    uint8_t stackPointer{};

    uint8_t memory[4096]{};
    uint32_t display[64 * 32]{};

    uint16_t opcode;
    std::map<char const *, void (Chip8::*)()> opTable;
    Chip8();
    bool Tick();
    void LoadROM(char const *filename);

private:
    void OP_clearDisplay();
    void OP_return();
    void OP_0xxx();
    void OP_1xxx();
    void OP_2xxx();
    void OP_3xxx();
    void OP_4xxx();
    void OP_5xx0();
    void OP_6xxx();
    void OP_7xxx();
    void OP_8xx0();
    void OP_8xx1();
    void OP_8xx2();
    void OP_8xx3();
    void OP_8xx4();
    void OP_8xx5();
    void OP_8xx6();
    void OP_8xx7();
    void OP_8xxe();
    void OP_9xx0();
    void OP_axxx();
    void OP_bxxx();
    void OP_cxxx();
    void OP_dxxx();
    void OP_ex9e();
    void OP_exa1();
    void OP_fx07();
    void OP_fx0a();
    void OP_fx15();
    void OP_fx18();
    void OP_fx1e();
    void OP_fx29();
    void OP_fx33();
    void OP_fx55();
    void OP_fx65();
};