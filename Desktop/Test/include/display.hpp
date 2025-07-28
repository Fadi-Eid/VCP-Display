#pragma once

#include <vector>
#include <SDL2/SDL.h>

class PixelDisplay {
public:
    PixelDisplay(int width, int height);
    ~PixelDisplay();
    void refresh();
protected:
    virtual void updatePixels();
    void render();
    void handleEvents();
private:
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    SDL_Texture* texture = nullptr;

    std::vector<uint8_t> pixels;

    int width, height, delayTime;

public:
    bool running;
};