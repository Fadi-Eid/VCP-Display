#pragma once

#include <vector>
#include <SDL2/SDL.h>

class PixelDisplay {
public:
    PixelDisplay(int width, int height, int fps);
    ~PixelDisplay();
    void run();
protected:
    virtual void updatePixels();
    void render();
    void handleEvents();
private:
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    SDL_Texture* texture = nullptr;

    std::vector<uint8_t> pixels;

    bool running;
    int width, height, fps, delayTime;
    const int pixelSize = 3;
};