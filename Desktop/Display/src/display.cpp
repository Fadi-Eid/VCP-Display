#include "display.hpp"
#include <iostream>
#include <string>
#include <cstdint>
#include <stdexcept>

PixelDisplay::PixelDisplay(int width, int height) : width(width), height(height),
                                                    pixels(width * height, 0xFF000000),
                                                    running(true) 
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0) 
    throw std::runtime_error(std::string("SDL_Init failed: ") + SDL_GetError());

    window = SDL_CreateWindow("VCP Display", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
    if (!window) throw std::runtime_error(std::string("SDL_CreateWindow failed") + SDL_GetError());

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) throw std::runtime_error(std::string("SDL_CreateRenderer failed") + SDL_GetError());

    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, width, height);
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
void PixelDisplay::updatePixels(const std::vector<uint32_t>& newPixels) {
    if (pixels.size() != newPixels.size()) {
        throw std::invalid_argument(
            "[PixelDisplay] updatePixels(): Buffer size mismatch. Expected " +
            std::to_string(pixels.size()) + ", got " +
            std::to_string(newPixels.size())
        );
    }

    std::copy(newPixels.begin(), newPixels.end(), pixels.begin());
}

void PixelDisplay::render() {
    SDL_Rect *rect = nullptr; // Use this later to update specific part of the screen
    SDL_UpdateTexture(texture, rect, pixels.data(), width * sizeof(uint32_t));
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