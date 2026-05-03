#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

const unsigned int SCREEN_WIDTH = 64;
const unsigned int SCREEN_HEIGHT = 32;

class Display{
    public:
        SDL_Window *window;
        SDL_Renderer *renderer;
        SDL_Texture *texture;
        bool Init();
        void Render(const uint32_t pixels[SCREEN_WIDTH * SCREEN_HEIGHT]);
};