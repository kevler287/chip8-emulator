#include "chip8.h"
#include <iostream>

void Chip8::OP_clearDisplay()
{
    for (int i = 0; i < std::size(display); i++)
    {
        display[i] = 0;
    }
}

void Chip8::OP_return()
{
    programCounter = stack[stackPointer];
    stackPointer--;
}

void Chip8::OP_0xxx()
{
    std::cout << "0xxx";
}

void Chip8::OP_JumpAddr()
{
    programCounter = opcode & 0x0FFF;
}

void Chip8::OP_callAddr()
{
    stackPointer++;
    stack[stackPointer] = programCounter;
    programCounter = opcode & 0x0FFF;
}

void Chip8::OP_skipIf()
{
    if (registers[(opcode & 0x0F00) >> 8] == (opcode & 0x00FF))
    {
        programCounter += 2;
    }
}
void Chip8::OP_skipIfNot()
{
    if (registers[(opcode & 0x0F00) >> 8] != (opcode & 0x00FF))
    {
        programCounter += 2;
    }
}
void Chip8::OP_skipIfEqual()
{
    if (registers[(opcode & 0x0F00) >> 8] == registers[(opcode & 0x00F0) >> 4])
    {
        programCounter += 2;
    }
}
void Chip8::OP_setRegister()
{
    registers[(opcode & 0x0F00) >> 8] = opcode & 0x00FF;
}
void Chip8::OP_addToRegister()
{
    registers[(opcode & 0x0F00) >> 8] += opcode & 0x00FF;
}
void Chip8::OP_copyRegister()
{
    registers[(opcode & 0x0F00) >> 8] = registers[(opcode & 0x00F0) >> 4];
}
void Chip8::OP_bitwiseOR()
{
    registers[(opcode & 0x0F00) >> 8] |= registers[(opcode & 0x00F0) >> 4];
}
void Chip8::OP_bitwiseAND()
{
    registers[(opcode & 0x0F00) >> 8] &= registers[(opcode & 0x00F0) >> 4];
}
void Chip8::OP_bitwiseXOR()
{
    registers[(opcode & 0x0F00) >> 8] ^= registers[(opcode & 0x00F0) >> 4];
}
void Chip8::OP_sumRegister()
{
    uint16_t sum = registers[(opcode & 0x0F00) >> 8] + registers[(opcode & 0x00F0) >> 4];

    if (sum > 0xFF)
        registers[15] = 1;
    else
        registers[15] = 0;

    registers[(opcode & 0x0F00) >> 8] = sum & 0xFF;
}
void Chip8::OP_subtractRegister()
{
    if (registers[(opcode & 0x0F00) >> 8] > registers[(opcode & 0x00F0) >> 4])
        registers[15] = 1;
    else
        registers[15] = 0;
    registers[(opcode & 0x0F00) >> 8] -= registers[(opcode & 0x00F0) >> 4];
}
void Chip8::OP_halveRegister()
{
    registers[15] = registers[(opcode & 0x0F00) >> 8] & 0x01;
    registers[(opcode & 0x0F00) >> 8] /= 2;
}
void Chip8::OP_subtractRegisterInverted()
{
    if (registers[(opcode & 0x0F00) >> 8] < registers[(opcode & 0x00F0) >> 4])
        registers[15] = 1;
    else
        registers[15] = 0;
    registers[(opcode & 0x0F00) >> 8] = registers[(opcode & 0x00F0) >> 4] - registers[(opcode & 0x0F00) >> 8];
}
void Chip8::OP_doubleRegister()
{
    registers[15] = registers[(opcode & 0x0F00) >> 8] & 0x80;
    registers[(opcode & 0x0F00) >> 8] *= 2;
}
void Chip8::OP_skipIfRegistersNotEqual()
{
    if (registers[(opcode & 0x0F00) >> 8] != registers[(opcode & 0x00F0) >> 4])
    {
        programCounter += 2;
    }
}
void Chip8::OP_setIndexRegister()
{
    indexRegister = opcode & 0x0FFF;
}
void Chip8::OP_jumpPC()
{
    programCounter = (opcode & 0x0FFF) + registers[0];
}
void Chip8::OP_randomBitwiseAND()
{
    registers[(opcode & 0x0F00) >> 8] = randomSeed(randGen) & (opcode & 0x00FF);
}
void Chip8::OP_displaySprite()
{
    registers[15] = 0;
    uint16_t n = opcode & 0x000F;
    uint16_t x0 = registers[(opcode & 0x0F00) >> 8] % SCREEN_WIDTH;
    uint16_t y0 = registers[(opcode & 0x00F0) >> 4] % SCREEN_HEIGHT;
    for (int i = 0; i < n; i++)
    {
        uint16_t start = (y0 + i) * SCREEN_WIDTH + x0;
        uint8_t b = memory[indexRegister + i];
        for (int j = 0; j < 8; j++)
        {
            if (b & (0b10000000 >> j))
            {
                if (display[start + j] == 0xFFFFFFFF)
                    registers[15] = 1;
                display[start + j] ^= 0xFFFFFFFF;
            }
            else
            {
                display[start + j] ^= 0x0;
            }
        }
    }
}
void Chip8::OP_skipIfKeyPressed()
{
    uint8_t keyIdx = registers[(opcode & 0x0F00) >> 8];
    if (keyStates[keyIdx])
    {
        programCounter += 2;
    }
}
void Chip8::OP_skipIfKeyIsNotPressed()
{
    uint8_t keyIdx = registers[(opcode & 0x0F00) >> 8];
    if (!keyStates[keyIdx])
    {
        programCounter += 2;
    }
}
void Chip8::OP_setRegisterToDelayTimer()
{
    registers[(opcode & 0x0F00) >> 8] = delayTimer;
}
void Chip8::OP_waitForKeyPress()
{
    std::cout << "Press any key\n";
    while (true)
    {
        for (int i = 0; i < std::size(keyStates); i++)
        {
            if (keyStates[i])
            {
                registers[(opcode & 0x0F00) >> 8] = i;
                return;
            }
        }
    }
}
void Chip8::OP_setDelayTimer()
{
    delayTimer = registers[(opcode & 0x0F00) >> 8];
}
void Chip8::OP_setSoundTimer()
{
    soundTimer = registers[(opcode & 0x0F00) >> 8];
}
void Chip8::OP_addToIndexRegister()
{
    indexRegister += registers[(opcode & 0x0F00) >> 8];
}
void Chip8::OP_setIndexRegisterToFontAddress()
{
    indexRegister = FONT_ADDRESS + (5 * registers[(opcode & 0x0F00) >> 8]);
}
void Chip8::OP_writeDigitsToMemory()
{
    uint8_t ones = registers[(opcode & 0x0F00) >> 8] % 10;
    uint8_t tens = (registers[(opcode & 0x0F00) >> 8] % 100) / 10;
    uint8_t hundreds = registers[(opcode & 0x0F00) >> 8] / 100;
    uint8_t digits[3] = {hundreds, tens, ones};
    for (int i = 0; i < std::size(digits); i++)
    {
        memory[indexRegister + i] = digits[i];
    }
}
void Chip8::OP_writeRegistersToMemory()
{
    for (int i = 0; i < std::size(registers); i++)
    {
        memory[indexRegister + i] = registers[i];
    }
}
void Chip8::OP_fx65()
{
    for (int i = 0; i < std::size(registers); i++)
    {
        registers[i] = memory[indexRegister + i];
    }
}