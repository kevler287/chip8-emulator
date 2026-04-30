#include "chip8.h"
#include <iostream>

void Chip8::OP_clearDisplay()
{
    for (uint32_t &pixel : display){
        pixel = 0;
    }
    std::cout << display[0];
}

void Chip8::OP_return()
{
    std::cout << "00ee";
}

void Chip8::OP_0xxx()
{
    std::cout << "0xxx";
}

void Chip8::OP_1xxx()
{
    std::cout << "1xxx";
}

void Chip8::OP_2xxx()
{
    std::cout << "2xxx";
}

void Chip8::OP_3xxx()
{
    std::cout << "3xxx";
}
void Chip8::OP_4xxx()
{
    std::cout << "4xxx";
}
void Chip8::OP_5xx0()
{
    std::cout << "5xx0";
}
void Chip8::OP_6xxx()
{
    std::cout << "6xxx";
}
void Chip8::OP_7xxx()
{
    std::cout << "7xxx";
}
void Chip8::OP_8xx0()
{
    std::cout << "8xx0";
}
void Chip8::OP_8xx1()
{
    std::cout << "8xx1";
}
void Chip8::OP_8xx2()
{
    std::cout << "8xx2";
}
void Chip8::OP_8xx3()
{
    std::cout << "8xx3";
}
void Chip8::OP_8xx4()
{
    std::cout << "8xx4";
}
void Chip8::OP_8xx5()
{
    std::cout << "8xx5";
}
void Chip8::OP_8xx6()
{
    std::cout << "8xx6";
}
void Chip8::OP_8xx7()
{
    std::cout << "8xx7";
}
void Chip8::OP_8xxe()
{
    std::cout << "8xxe";
}
void Chip8::OP_9xx0()
{
    std::cout << "9xx0";
}
void Chip8::OP_axxx()
{
    std::cout << "axxx";
}
void Chip8::OP_bxxx()
{
    std::cout << "bxxx";
}
void Chip8::OP_cxxx()
{
    std::cout << "cxxx";
}
void Chip8::OP_dxxx()
{
    std::cout << "dxxx";
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
void Chip8::OP_fx1e()
{
    std::cout << "fx1e";
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