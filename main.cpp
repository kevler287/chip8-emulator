#include <iostream>
#include <chip8.h>

int main()
{
    char const *romFilename = "roms/octojam1title.ch8";
    Chip8 chip8;
    chip8.LoadROM(romFilename);
    Display display;
    bool success = display.Init();
    if (!success){
        return 1;
    }
    SDL_Event e;
    bool quit = false;

    while(!quit)
    {
        while( SDL_PollEvent( &e ) != 0 )
        {
            if( e.type == SDL_QUIT )
            {
                quit = true;
            }
        }
        bool success = chip8.Tick();
        if (!success)
        {
            std::cout << "error: " << std::hex << chip8.opcode << "\n";
        }
        display.Render(chip8.display);
    }
    return 0;
}
