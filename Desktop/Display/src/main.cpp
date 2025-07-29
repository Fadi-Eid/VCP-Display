#include "display.hpp"
#include <cstdint>

int main() {
    const int width{200}, height{200};
    std::vector<uint32_t> pixels(width * height, 0xFFFF0000);

    PixelDisplay display(width, height);

    while(display.running) {
        display.updatePixels(pixels);
        display.refresh();
        display.delay(20);
    }
    
    return 0;
}
