#include "communication.hpp"
#include "display.hpp"
#include <iostream>

int main() {
    Communication::Parser serial("/dev/ttyACM0", 7400000);

    uint16_t x[2] = {0};
    uint16_t y[2] = {0};
    uint16_t px{0};
    uint8_t byte = 0;

    while(true){
        byte = serial.readByte();
        
        if (byte == 0x2a) { // Set column address
            x[0] = (serial.readByte() << 8) | serial.readByte();
            x[1] = (serial.readByte() << 8) | serial.readByte();
        }
        else if (byte == 0x2b) { // Set row address
            y[0] = (serial.readByte() << 8) | serial.readByte();
            y[1] = (serial.readByte() << 8) | serial.readByte();
        }
        else if(byte == 0x2c) { // Collect pixels value (RGB565)
            size_t size = (y[1] - y[0] + 1) * (x[1] - x[0] + 1);
            for(size_t i=0; i<size; i++) {
                px = (serial.readByte() << 8) | serial.readByte();
                std::cout << "px(" << i << ") = " << serial.byteToHex(px) << std::endl;
            }
        }
    }
}