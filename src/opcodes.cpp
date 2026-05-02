#include "chip8.h"
#include <iostream>

void Chip8::OP_clearDisplay()
{
    for (int i = 0 ; i < std::size(display) ; i++){
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
    if (registers[(opcode & 0x0F00) >> 8] == (opcode & 0x00FF)){
        programCounter += 2;
    }
}
void Chip8::OP_skipIfNot()
{
    if (registers[(opcode & 0x0F00) >> 8] != (opcode & 0x00FF)){
        programCounter += 2;
    }
}
void Chip8::OP_skipIfEqual()
{
    if (registers[(opcode & 0x0F00) >> 8] == registers[(opcode & 0x00F0) >> 4]){
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

    if (sum > 0xFF) registers[15] = 1;
    else registers[15] = 0;

    registers[(opcode & 0x0F00) >> 8] = sum & 0xFF;
}
void Chip8::OP_subtractRegister()
{
    if (registers[(opcode & 0x0F00) >> 8] > registers[(opcode & 0x00F0) >> 4]) registers[15] = 1;
    else registers[15] = 0;
    registers[(opcode & 0x0F00) >> 8] -= registers[(opcode & 0x00F0) >> 4];
}
void Chip8::OP_halveRegister()
{
    registers[15] = registers[(opcode & 0x0F00) >> 8] & 0x01;
    registers[(opcode & 0x0F00) >> 8] /= 2;
}
void Chip8::OP_subtractRegisterInverted()
{
    if (registers[(opcode & 0x0F00) >> 8] < registers[(opcode & 0x00F0) >> 4]) registers[15] = 1;
    else registers[15] = 0;
    registers[(opcode & 0x0F00) >> 8] = registers[(opcode & 0x00F0) >> 4] - registers[(opcode & 0x0F00) >> 8];
}
void Chip8::OP_doubleRegister()
{
    registers[15] = registers[(opcode & 0x0F00) >> 8] & 0x80;
    registers[(opcode & 0x0F00) >> 8] *= 2;
}
void Chip8::OP_skipIfRegistersNotEqual()
{
    if (registers[(opcode & 0x0F00) >> 8] != registers[(opcode & 0x00F0) >> 4]){
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
    uint16_t n = opcode & 0x000F;
    uint16_t x0 = registers[(opcode & 0x0F00) >> 8] % SCREEN_WIDTH;
    uint16_t y0 = registers[(opcode & 0x00F0) >> 4] % SCREEN_HEIGHT;
    for (int i = 0 ; i < n ; i++){
        uint16_t start = (y0+i) * SCREEN_WIDTH + x0;
        uint8_t b = memory[indexRegister + i];
        for (int j = 0 ; j < 8 ; j++){
            display[start+j] ^= (b & (0b10000000 >> j)) >> (7 - j);
        }
    }
    Render();
}
void Chip8::OP_ex9e()
{
    std::cout << "ex9e";
}
void Chip8::OP_exa1()
{
    std::cout << "exa1";
}
void Chip8::OP_fx07()
{
    std::cout << "fx07";
}
void Chip8::OP_fx0a()
{
    std::cout << "fx0a";
}
void Chip8::OP_fx15()
{
    std::cout << "fx15";
}
void Chip8::OP_fx18()
{
    std::cout << "fx18";
}
void Chip8::OP_addToIndexRegister()
{
    indexRegister += registers[(opcode & 0x0F00) >> 8];
}
void Chip8::OP_fx29()
{
    std::cout << "fx29";
}
void Chip8::OP_fx33()
{
    std::cout << "fx33";
}
void Chip8::OP_fx55()
{
    std::cout << "fx55";
}
void Chip8::OP_fx65()
{
    std::cout << "fx65";
}