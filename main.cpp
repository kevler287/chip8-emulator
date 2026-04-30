#include <iostream>
#include "chip8.h"

int main()
{
    char const *romFilename = "roms/pong_single_player.ch8";
    uint16_t opcode;
    uint16_t table;

    Chip8 chip8;
    chip8.LoadROM(romFilename);

    for (int k = 0; k < 100; k++)
    {
        bool success = chip8.Tick();
        if (!success)
        {
            std::cout << "error: " << std::hex << chip8.opcode << "\n";
        }
    }
}
