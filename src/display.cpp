#include <display.h>
#include <iostream>

bool Display::Init(){
    window = SDL_CreateWindow("Chip-8", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH*10, SCREEN_HEIGHT*10, SDL_WINDOW_SHOWN);
    if (window == NULL){
        std::cout << "Error creating window\n";
        return false;
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL){
        std::cout << "Error creating renderer\n";
        return false;
    }
    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, SCREEN_WIDTH, SCREEN_HEIGHT);
    if (texture == NULL){
        std::cout << "Error creating texture\n";
        return false;
    }
    return true;
}

void Display::Render(const uint32_t pixels[SCREEN_WIDTH * SCREEN_HEIGHT]){
    SDL_UpdateTexture(texture, NULL, pixels, sizeof(pixels[0]) * SCREEN_WIDTH);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);
}