#include <fstream>
#include "chip8.h"
#include <iostream>

const unsigned int START_ADDRESS = 0x200;

Chip8::Chip8() {
    programCounter = START_ADDRESS;
}

void Chip8::Increment(){
    opcode = (memory[programCounter] << 8u) | memory[programCounter + 1];
    programCounter += 2;

    unsigned int digits[] = {
        (opcode & 0xF000u) >> 12u,
        (opcode & 0x0F00u) >> 8u,
        (opcode & 0x00F0u) >> 4u,
        opcode & 0x000Fu,
    };

    

    std::cout << std::hex << opcode << ": ";
    for (int i = 0; i<std::size(digits); i++){
        std::cout << std::hex << digits[i] << ",";
    }
    std::cout << "\n";
}

void Chip8::LoadROM(char const *filename){
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