#pragma once

#include <fcntl.h>			// Contains file controls like O_RDWR
#include <unistd.h>			// write(), read(), close()
#include <sys/ioctl.h>
#include <asm/termbits.h>

#include <string>
#include <stdexcept>
#include <cstdint>
#include <cstring>
#include <iomanip> 

namespace Communication {
class Parser {
public:
    Parser(std::string device, int baud);

    ~Parser();

    uint8_t readByte();

    static std::string byteToHex(uint8_t byte);

private:
    int m_serialPort{0};
};
}