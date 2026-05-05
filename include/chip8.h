#include <cstdint>
#include <map>
#include <string>
#include <random>
#include <display.h>

const unsigned int FONT_ADDRESS = 0x050;
const unsigned int START_ADDRESS = 0x200;

const uint8_t FONTSET[80] =
    {
        0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
        0x20, 0x60, 0x20, 0x20, 0x70, // 1
        0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
        0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
        0x90, 0x90, 0xF0, 0x10, 0x10, // 4
        0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
        0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
        0xF0, 0x10, 0x20, 0x40, 0x40, // 7
        0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
        0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
        0xF0, 0x90, 0xF0, 0x90, 0x90, // A
        0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
        0xF0, 0x80, 0x80, 0x80, 0xF0, // C
        0xE0, 0x90, 0x90, 0x90, 0xE0, // D
        0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
        0xF0, 0x80, 0xF0, 0x80, 0x80  // F
};

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
    std::map<const SDL_Keycode, uint8_t> keyBinds;
    bool keyStates[16]{};

    uint16_t opcode{};
    std::map<char const *, void (Chip8::*)()> opTable;

    std::default_random_engine randGen;
    std::uniform_int_distribution<uint8_t> randomSeed;

    uint8_t delayTimer{};
    uint8_t soundTimer{};

    Chip8();
    void Tick();
    bool ProcessKeyboardEvent();
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
    void OP_skipIfKeyPressed();
    void OP_skipIfKeyIsNotPressed();
    void OP_setRegisterToDelayTimer();
    void OP_waitForKeyPress();
    void OP_setDelayTimer();
    void OP_setSoundTimer();
    void OP_addToIndexRegister();
    void OP_setIndexRegisterToFontAddress();
    void OP_writeDigitsToMemory();
    void OP_writeRegistersToMemory();
    void OP_writeMemoryToRegisters();
};