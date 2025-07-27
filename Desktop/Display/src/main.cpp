#include "communication.hpp"
#include <iostream>
#include <iomanip>   // for std::hex and std::setw

int main() {
    Communication::Parser serial("/dev/ttyACM0", 7400000);
        while(true) {
            std::cout << Communication::Parser::byteToHex(serial.readByte()) << std::endl;
        }
}