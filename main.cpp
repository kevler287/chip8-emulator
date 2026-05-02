#include <iostream>
#include "chip8.h"

int main()
{
    char const *romFilename = "roms/zero_demo.ch8";
    Chip8 chip8;
    chip8.LoadROM(romFilename);

    for (int k = 0; k < 1000; k++)
    {
        bool success = chip8.Tick();
        if (!success)
        {
            std::cout << "error: " << std::hex << chip8.opcode << "\n";
        }
    }
}
