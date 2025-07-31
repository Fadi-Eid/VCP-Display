#pragma once

#include <SDL2/SDL.h>
#include <vector>
#include <cstdint>

class PixelDisplay {
public:
    PixelDisplay(int width, int height);
    ~PixelDisplay();
    void refresh();
    static void delay(uint32_t ms);
    void updatePixels(const std::vector<uint16_t>& pixels);
protected:
    void render();
    void handleEvents();
private:
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    SDL_Texture* texture = nullptr;

    std::vector<uint16_t> pixels;
    int width, height;

public:
    bool running;
};