#include "display.hpp"
#include <iostream>
#include <string>
#include <cstdint>
#include <stdexcept>

PixelDisplay::PixelDisplay(int width, int height) : width(width), height(height),
                                                    pixels(width * height, 0xFF00),
                                                    running(true) 
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0) 
    throw std::runtime_error(std::string("SDL_Init failed: ") + SDL_GetError());

    window = SDL_CreateWindow("VCP Display", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
    if (!window) throw std::runtime_error(std::string("SDL_CreateWindow failed") + SDL_GetError());

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) throw std::runtime_error(std::string("SDL_CreateRenderer failed") + SDL_GetError());

    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGB565, SDL_TEXTUREACCESS_STREAMING, width, height);
    if (!texture) throw std::runtime_error(std::string("SDL_CreateTexture failed") + SDL_GetError());
}

PixelDisplay::~PixelDisplay() {
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void PixelDisplay::refresh() {
    handleEvents();
    render();
}

/* This should populate the pixels vector based on the received UART data */
void PixelDisplay::updatePixels(const std::vector<uint16_t>& newPixels, uint16_t x[], uint16_t y[]) {
    this->pixels = newPixels;
    start_horiz = x[0];
    end_horiz = x[1];
    start_vert = y[0];
    end_vert = y[1];
}

void PixelDisplay::render() {
    void* texturePixels;
    int pitch;

    // Specify zone to update
    SDL_Rect updateRect = {start_horiz, start_vert, end_horiz - start_horiz + 1, end_vert - start_vert + 1}; 

    if (SDL_LockTexture(texture, &updateRect, &texturePixels, &pitch) != 0) {
        std::cerr << "Failed to lock texture: " << SDL_GetError() << std::endl;
        return;
    }

    // Copy only the region's pixels from your `pixels` vector to the texture
    for (int row = 0; row < updateRect.h; ++row) {
        memcpy(
            static_cast<uint8_t*>(texturePixels) + row * pitch,
            &pixels[(start_vert + row) * width + start_horiz],
            updateRect.w * sizeof(uint16_t)  // RGB565
        );
    }

    SDL_UnlockTexture(texture);
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

void PixelDisplay::delay(uint32_t ms) {
    SDL_Delay(ms);
}