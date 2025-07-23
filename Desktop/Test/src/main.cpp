#include <SDL2/SDL.h>
#include <iostream>
#include "display.hpp"

int main() {
    try {
        PixelDisplay display(256, 256, 60);
        display.run();
    } catch (const std::exception& e) {
        std::cerr << "Fatal error: " << e.what() << std::endl;
        return 1;
    }

    // Investigate this: https://github.com/gbmhunter/CppLinuxSerial/tree/master
    // for serial communication in C++ with custom baud-rate

    // Read UART Data
    return 0;
}
