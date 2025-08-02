#include "communication.hpp"
#include "display.hpp"
#include <iostream>

int main() {
    /* Display Properties */
    const int width{150}, height{150};

    /* Pixels buffer (RGB565) TODO: Make configurable */
    std::vector<uint16_t> pixels(width * height, 0x00); // RGB565 default: black

    /* Construct Display */
    PixelDisplay display(width, height);

    /* Construct Communication*/
    Parser serial("/dev/ttyACM0", 7400000);

    /* Page and Column Addresses */
    uint16_t x[2] = {0};
    uint16_t y[2] = {0};

    while (display.running) {

        if (serial.readByte() == 0x2A) { // Set column address command
            /* Get start and end horizontal pixels */
            x[0] = serial.readHalfWord();
            x[1] = serial.readHalfWord();

            if (serial.readByte() == 0x2b) { // Set row address command
                /* Get start and end vertical pixels*/
                y[0] = serial.readHalfWord();
                y[1] = serial.readHalfWord();
                
                if (serial.readByte() == 0x2c) { // Receive pixels stream command
                    /* Compute the number of pixels needed for the dirty rectangle */
                    size_t count = (y[1] - y[0] + 1) * (x[1] - x[0] + 1);
                    
                    /* Fill the pixels vector */
                    for (uint16_t row = y[0]; row <= y[1]; ++row) {
                        for (uint16_t col = x[0]; col <= x[1]; ++col) {
                            pixels[row * width + col] = serial.readHalfWord();
                        }
                    }
                    display.updatePixels(pixels, x, y);
                    display.refresh();
                }
            }
        }
    }

    return 0;
}
