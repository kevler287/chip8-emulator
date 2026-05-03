#include <cstdint>
#include <map>
#include <string>
#include <random>
#include <display.h>

class Chip8
{
public:
    uint8_t registers[16]{};
    uint16_t indexRegister{};
    uint16_t programCounter{};
    uint16_t stack[16]{};
    uint8_t stackPointer{};

    uint8_t memory[4096]{};
    uint32_t display[SCREEN_WIDTH * SCREEN_HEIGHT]{};

    uint16_t opcode{};
    std::map<char const *, void (Chip8::*)()> opTable;

    std::default_random_engine randGen;
    std::uniform_int_distribution<uint8_t> randomSeed;

    Chip8();
    bool Tick();
    void LoadROM(char const *filename);

private:
    void OP_clearDisplay();
    void OP_return();
    void OP_0xxx();
    void OP_JumpAddr();
    void OP_callAddr();
    void OP_skipIf();
    void OP_skipIfNot();
    void OP_skipIfEqual();
    void OP_setRegister();
    void OP_addToRegister();
    void OP_copyRegister();
    void OP_bitwiseOR();
    void OP_bitwiseAND();
    void OP_bitwiseXOR();
    void OP_sumRegister();
    void OP_subtractRegister();
    void OP_halveRegister();
    void OP_subtractRegisterInverted();
    void OP_doubleRegister();
    void OP_skipIfRegistersNotEqual();
    void OP_setIndexRegister();
    void OP_jumpPC();
    void OP_randomBitwiseAND();
    void OP_displaySprite();
    void OP_ex9e();
    void OP_exa1();
    void OP_fx07();
    void OP_fx0a();
    void OP_fx15();
    void OP_fx18();
    void OP_addToIndexRegister();
    void OP_fx29();
    void OP_fx33();
    void OP_fx55();
    void OP_fx65();
};