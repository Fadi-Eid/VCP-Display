#include "communication.hpp"
#include "display.hpp"
#include <iostream>

int main() {
    const int width{150}, height{150};
    std::vector<uint16_t> pixels(width * height, 0x00); // RGB565 default: black

    PixelDisplay display(width, height);
    Parser serial("/dev/ttyACM0", 7400000);

    uint16_t x[2] = {0};
    uint16_t y[2] = {0};
    uint16_t rgb565 = 0;

    while (display.running) {

        if (serial.readByte() == 0x2a) { // Set column address
            x[0] = serial.readHalfWord();
            x[1] = serial.readHalfWord();

            if (serial.readByte() == 0x2b) { // Set row address
                y[0] = serial.readHalfWord();
                y[1] = serial.readHalfWord();
                
                if (serial.readByte() == 0x2c) { // Write RGB565 pixels
                    size_t count = (y[1] - y[0] + 1) * (x[1] - x[0] + 1);
                    
                    for (uint16_t row = y[0]; row <= y[1]; ++row) {
                        for (uint16_t col = x[0]; col <= x[1]; ++col) {
                            pixels[row * width + col] = serial.readHalfWord();
                        }
                    }
                    display.updatePixels(pixels);
                    display.refresh();
                }
            }
        }
    }

    return 0;
}
