#include <iostream>
#include <chip8.h>

int main()
{
    char const *romFilename = "roms/flightrunner.ch8";
    Chip8 chip8;
    chip8.LoadROM(romFilename);
    Display display;
    bool success = display.Init();
    if (!success){
        return 1;
    }
    bool quit = false;

    while(!quit)
    {
        quit = chip8.ProcessKeyboardEvent();
        chip8.Tick();
        display.Render(chip8.display);

        if (chip8.delayTimer > 0)
        {
            chip8.delayTimer--;
        }

        if (chip8.soundTimer > 0)
        {
            chip8.soundTimer--;
        }

    }
    return 0;
}
