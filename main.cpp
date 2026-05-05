#include <iostream>
#include <chip8.h>
#include <thread>

int main(int argc, const char * argv[])
{
    int const freq = std::stoi(argv[1]);
    char const* romFilename = argv[2];

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

        while (chip8.delayTimer > 0)
        {
            chip8.delayTimer--;
            std::this_thread::sleep_for(std::chrono::milliseconds(1000/freq));
        }

        while (chip8.soundTimer > 0)
        {
            chip8.soundTimer--;
            std::this_thread::sleep_for(std::chrono::milliseconds(1000/freq));
        }

    }
    return 0;
}
