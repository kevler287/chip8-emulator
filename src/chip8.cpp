#include <fstream>
#include "chip8.h"
#include <iostream>

Chip8::Chip8()
{
    programCounter = START_ADDRESS;
    randomSeed = std::uniform_int_distribution<uint8_t>(0, 255U);

    opTable["00e0"] = &Chip8::OP_clearDisplay;
    opTable["00ee"] = &Chip8::OP_return;
    opTable["0xxx"] = &Chip8::OP_0xxx;
    opTable["1xxx"] = &Chip8::OP_JumpAddr;
    opTable["2xxx"] = &Chip8::OP_callAddr;
    opTable["3xxx"] = &Chip8::OP_skipIf;
    opTable["4xxx"] = &Chip8::OP_skipIfNot;
    opTable["5xx0"] = &Chip8::OP_skipIfEqual;
    opTable["6xxx"] = &Chip8::OP_setRegister;
    opTable["7xxx"] = &Chip8::OP_addToRegister;
    opTable["8xx0"] = &Chip8::OP_copyRegister;
    opTable["8xx1"] = &Chip8::OP_bitwiseOR;
    opTable["8xx2"] = &Chip8::OP_bitwiseAND;
    opTable["8xx3"] = &Chip8::OP_bitwiseXOR;
    opTable["8xx4"] = &Chip8::OP_sumRegister;
    opTable["8xx5"] = &Chip8::OP_subtractRegister;
    opTable["8xx6"] = &Chip8::OP_halveRegister;
    opTable["8xx7"] = &Chip8::OP_subtractRegisterInverted;
    opTable["8xxe"] = &Chip8::OP_doubleRegister;
    opTable["9xx0"] = &Chip8::OP_skipIfRegistersNotEqual;
    opTable["axxx"] = &Chip8::OP_setIndexRegister;
    opTable["bxxx"] = &Chip8::OP_jumpPC;
    opTable["cxxx"] = &Chip8::OP_randomBitwiseAND;
    opTable["dxxx"] = &Chip8::OP_displaySprite;
    opTable["ex9e"] = &Chip8::OP_skipIfKeyPressed;
    opTable["exa1"] = &Chip8::OP_skipIfKeyIsNotPressed;
    opTable["fx07"] = &Chip8::OP_setRegisterToDelayTimer;
    opTable["fx0a"] = &Chip8::OP_waitForKeyPress;
    opTable["fx15"] = &Chip8::OP_setDelayTimer;
    opTable["fx18"] = &Chip8::OP_setSoundTimer;
    opTable["fx1e"] = &Chip8::OP_addToIndexRegister;
    opTable["fx29"] = &Chip8::OP_setIndexRegisterToFontAddress;
    opTable["fx33"] = &Chip8::OP_writeDigitsToMemory;
    opTable["fx55"] = &Chip8::OP_writeRegistersToMemory;
    opTable["fx65"] = &Chip8::OP_fx65;

    keyBinds[SDLK_x] = 0x0;
    keyBinds[SDLK_1] = 0x1;
    keyBinds[SDLK_2] = 0x2;
    keyBinds[SDLK_3] = 0x3;
    keyBinds[SDLK_q] = 0x4;
    keyBinds[SDLK_w] = 0x5;
    keyBinds[SDLK_e] = 0x6;
    keyBinds[SDLK_a] = 0x7;
    keyBinds[SDLK_s] = 0x8;
    keyBinds[SDLK_d] = 0x9;
    keyBinds[SDLK_z] = 0xa;
    keyBinds[SDLK_c] = 0xb;
    keyBinds[SDLK_4] = 0xc;
    keyBinds[SDLK_r] = 0xd;
    keyBinds[SDLK_f] = 0xe;
    keyBinds[SDLK_v] = 0xf;

    for (int i = 0; i < std::size(FONTSET); i++)
    {
        memory[FONT_ADDRESS + i] = FONTSET[i];
    }
}

void Chip8::Tick()
{
    opcode = (memory[programCounter] << 8u) | memory[programCounter + 1];
    programCounter += 2;

    // if ((opcode & 0x0F00) >> 8 == 0xa){
    //     std::cout << std::hex << opcode;
    // }
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
            return;
        }
    }
    std::cout << "error: " << std::hex << opcode << " doesn't exist\n";
}

bool Chip8::ProcessKeyboardEvent()
{
    bool quit = false;
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if( event.type == SDL_QUIT ) quit = true;

        if (keyBinds.count(event.key.keysym.sym) == 0)continue;
        uint8_t keyIdx = keyBinds[event.key.keysym.sym];
        if (event.type == SDL_KEYDOWN)
            keyStates[keyIdx] = true;
        if (event.type == SDL_KEYUP)
            keyStates[keyIdx] = false;
    }
    return quit;
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