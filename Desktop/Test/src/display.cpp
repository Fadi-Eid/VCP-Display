#include "display.hpp"
#include <iostream>

PixelDisplay::PixelDisplay(int width, int height) : width(width), height(height), pixels(width * height * 3, 0), running(true) 
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0) throw std::runtime_error("SDL_Init failed");

    window = SDL_CreateWindow("VCP Display", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
    if (!window) throw std::runtime_error("SDL_CreateWindow failed");

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) throw std::runtime_error("SDL_CreateRenderer failed");

    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGB24, SDL_TEXTUREACCESS_STREAMING, width, height);
    if (!texture) throw std::runtime_error("SDL_CreateTexture failed");
}

PixelDisplay::~PixelDisplay() {
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void PixelDisplay::refresh() {
    handleEvents();
    updatePixels();
    render();
}

/* Testing function (This must be implemented on MCU and the program read via UART/USB)*/
void PixelDisplay::updatePixels() {
    static int count = 0, frames = 0;

    int colorArr[] = {0, 0, 0};
    colorArr[count] = 255;
    
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int i = (y * width + x) * 3;
            pixels[i + 0] = colorArr[0];    // Red
            pixels[i + 1] = colorArr[1];    // Green
            pixels[i + 2] = colorArr[2];    // Blue
        }
    }
    if(++frames == 50) {
        frames = 0;
        if (++count == 3)
            count = 0;
    }
}

void PixelDisplay::render() {
    SDL_UpdateTexture(texture, nullptr, pixels.data(), width * 3);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, nullptr, nullptr);
    SDL_RenderPresent(renderer);
}

void PixelDisplay::handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT)
            running = false;
    }
}