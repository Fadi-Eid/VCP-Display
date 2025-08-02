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
    void updatePixels(const std::vector<uint16_t>& pixels, uint16_t x[], uint16_t y[]);
protected:
    void render();
    void handleEvents();
private:
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    SDL_Texture* texture = nullptr;

    std::vector<uint16_t> pixels;
    int width, height;

    uint16_t start_horiz{0};
    uint16_t end_horiz{0};
    uint16_t start_vert{0};
    uint16_t end_vert{0};

public:
    bool running;
};