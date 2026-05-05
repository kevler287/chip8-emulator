# chip8-emulator
First steps in c++

## Rules
- no GenAI
- exception was made for installing SDL2 on windows

## Usage
- install g++ compiler and SDL2
- get a rom from: https://github.com/kripod/chip8-roms
- 'g++ -o main.exe -I include/ src/*.cpp main.cpp -lSDL2main -lSDL2'
- './main.exe 60 ${path/to/rom}'

## Sources
- Basic Understanding: https://austinmorlan.com/posts/chip8_emulator/
- Environment Setup: https://code.visualstudio.com/docs/languages/cpp#_set-up-your-c-environment
- Header Files: https://learn.microsoft.com/en-us/cpp/cpp/header-files-cpp?view=msvc-170
- Console logs: https://www.w3schools.com/cpp/cpp_output.asp
- OpCodes: http://devernay.free.fr/hacks/chip8/C8TECH10.HTM#3.0
- opTable: https://stackoverflow.com/questions/73806338/how-to-create-a-map-with-key-of-string-and-value-a-pointer-to-a-member-function
- SDL Basics: https://lazyfoo.net/tutorials/SDL/
- SDL Texture Update: https://discourse.libsdl.org/t/question-creating-an-sdl-texture-from-an-array/38530
- Keybinds: https://www.google.com/url?sa=t&source=web&rct=j&url=https%3A%2F%2Flepuri.net%2Fmaking-a-chip-8-emulator-in-c%2F&ved=0CBYQjRxqFwoTCJiVrMmln5QDFQAAAAAdAAAAABAG&opi=89978449
- timer frequency: https://www.geeksforgeeks.org/cpp/how-to-add-timed-delay-in-cpp/

