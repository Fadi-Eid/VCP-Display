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

class Parser {
public:
    Parser(std::string device, int baud);

    ~Parser();

    uint8_t readByte();
    uint16_t readHalfWord();
    ssize_t readBytes(uint8_t* buffer, size_t length);

    static std::string byteToHex(uint8_t byte);
    static std::string halfWordToHex(uint16_t halfWord);
    static std::string fullWordToHex(uint32_t fullWord);

private:
    int m_serialPort{0};
};
