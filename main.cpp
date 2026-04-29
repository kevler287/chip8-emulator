#include <iostream>
#include "chip8.h"

int main() {
    char const* romFilename = "roms/pong_single_player.ch8";
    uint16_t opcode;
    uint16_t table;

    Chip8 chip8;
	chip8.LoadROM(romFilename);

    for(int i = 0; i<10 ; i++){
        chip8.Increment();
    }
}
