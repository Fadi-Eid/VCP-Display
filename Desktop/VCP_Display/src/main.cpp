#include "communication.hpp"
#include "display.hpp"
#include <iostream>

int main() {
    const int width{50}, height{50};
    std::vector<uint32_t> pixels(width * height, 0xFF000000); // ARGB8888 default: black

    PixelDisplay display(width, height);
    Parser serial("/dev/ttyACM0", 7400000);

    uint16_t x[2] = {0};
    uint16_t y[2] = {0};
    uint16_t rgb565 = 0;
    uint8_t byte = 0;

    while (display.running) {
        byte = serial.readByte();

        if (byte == 0x2a) { // Set column address
            x[0] = (serial.readByte() << 8) | serial.readByte();
            x[1] = (serial.readByte() << 8) | serial.readByte();
        } 
        else if (byte == 0x2b) { // Set row address
            y[0] = (serial.readByte() << 8) | serial.readByte();
            y[1] = (serial.readByte() << 8) | serial.readByte();
        } 
        else if (byte == 0x2c) { // Write RGB565 pixels
            size_t count = (y[1] - y[0] + 1) * (x[1] - x[0] + 1);
            for (uint16_t row = y[0]; row <= y[1]; ++row) {
                for (uint16_t col = x[0]; col <= x[1]; ++col) {
                    uint8_t hi = serial.readByte();
                    uint8_t lo = serial.readByte();
                    rgb565 = (hi << 8) | lo;

                    // Extract RGB565
                    uint8_t r5 = (rgb565 >> 11) & 0x1F;
                    uint8_t g6 = (rgb565 >> 5) & 0x3F;
                    uint8_t b5 = rgb565 & 0x1F;

                    // Expand to 8-bit (with left shift and replicate upper bits)
                    uint8_t r8 = (r5 << 3) | (r5 >> 2);
                    uint8_t g8 = (g6 << 2) | (g6 >> 4);
                    uint8_t b8 = (b5 << 3) | (b5 >> 2);

                    // ARGB8888 (Alpha = 255)
                    uint32_t argb = (0xFF << 24) | (r8 << 16) | (g8 << 8) | b8;

                    if (row < height && col < width) {
                        pixels[row * width + col] = argb;
                    }
                }
            }
        }

        display.updatePixels(pixels);
        display.refresh();
    }

    return 0;
}
