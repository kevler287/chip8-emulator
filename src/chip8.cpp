#include <fstream>
#include "chip8.h"
#include <iostream>

const unsigned int START_ADDRESS = 0x200;

Chip8::Chip8()
{
    programCounter = START_ADDRESS;
    opTable["00e0"] = &Chip8::OP_clearDisplay;
    opTable["00ee"] = &Chip8::OP_return;
    opTable["0xxx"] = &Chip8::OP_0xxx;
    opTable["1xxx"] = &Chip8::OP_JumpAddr;
    opTable["2xxx"] = &Chip8::OP_callAddr;
    opTable["3xxx"] = &Chip8::OP_3xxx;
    opTable["4xxx"] = &Chip8::OP_4xxx;
    opTable["5xx0"] = &Chip8::OP_5xx0;
    opTable["6xxx"] = &Chip8::OP_6xxx;
    opTable["7xxx"] = &Chip8::OP_7xxx;
    opTable["8xx0"] = &Chip8::OP_8xx0;
    opTable["8xx1"] = &Chip8::OP_8xx1;
    opTable["8xx2"] = &Chip8::OP_8xx2;
    opTable["8xx3"] = &Chip8::OP_8xx3;
    opTable["8xx4"] = &Chip8::OP_8xx4;
    opTable["8xx5"] = &Chip8::OP_8xx5;
    opTable["8xx6"] = &Chip8::OP_8xx6;
    opTable["8xx7"] = &Chip8::OP_8xx7;
    opTable["8xxe"] = &Chip8::OP_8xxe;
    opTable["9xx0"] = &Chip8::OP_9xx0;
    opTable["axxx"] = &Chip8::OP_axxx;
    opTable["bxxx"] = &Chip8::OP_bxxx;
    opTable["cxxx"] = &Chip8::OP_cxxx;
    opTable["dxxx"] = &Chip8::OP_dxxx;
    opTable["ex9e"] = &Chip8::OP_ex9e;
    opTable["exa1"] = &Chip8::OP_exa1;
    opTable["fx07"] = &Chip8::OP_fx07;
    opTable["fx0a"] = &Chip8::OP_fx0a;
    opTable["fx15"] = &Chip8::OP_fx15;
    opTable["fx18"] = &Chip8::OP_fx18;
    opTable["fx1e"] = &Chip8::OP_fx1e;
    opTable["fx29"] = &Chip8::OP_fx29;
    opTable["fx33"] = &Chip8::OP_fx33;
    opTable["fx55"] = &Chip8::OP_fx55;
    opTable["fx65"] = &Chip8::OP_fx65;
}

bool Chip8::Tick()
{
    opcode = (memory[programCounter] << 8u) | memory[programCounter + 1];
    programCounter += 2;

    std::cout << std::hex << opcode << ": ";
    unsigned int opDigit;
    unsigned int inDigit;
    unsigned int filter;
    for (const auto &oc : opTable)
    {
        bool match = true;
        for (int j = 0; j < 4; j++)
        {
            char c = oc.first[j];
            if (c == 'x')
            {
                continue;
            }
            filter = 0xF << (12u - j * 4u);
            opDigit = (opcode & filter) >> (12u - j * 4u);

            if (c >= '0' && c <= '9')
                inDigit = c - '0';
            if (c >= 'a' && c <= 'f')
                inDigit = c - 'a' + 10;

            if (inDigit != opDigit)
            {
                match = false;
                break;
            }
        }
        if (match)
        {
            (this->*oc.second)();
            std::cout << "\n";
            return true;
        }
    }
    return false;
}

void Chip8::LoadROM(char const *filename)
{
    // Open the file as a stream of binary and move the file pointer to the end
    std::ifstream file(filename, std::ios::binary | std::ios::ate);

    if (file.is_open())
    {
        // Get size of file and allocate a buffer to hold the contents
        std::streampos size = file.tellg();
        char *buffer = new char[size];

        // Go back to the beginning of the file and fill the buffer
        file.seekg(0, std::ios::beg);
        file.read(buffer, size);
        file.close();

        // Load the ROM contents into the Chip8's memory, starting at 0x200
        for (long i = 0; i < size; ++i)
        {
            memory[START_ADDRESS + i] = buffer[i];
        }

        // Free the buffer
        delete[] buffer;
    }
}