#include "communication.hpp"


Parser::Parser(std::string device, int baud) {
    // Open
    m_serialPort = open(device.c_str(), O_RDWR);
    if (m_serialPort < 0) {
        throw std::runtime_error("Failed to open device: " + device);
    }

    struct termios2 tty;

    if (ioctl(m_serialPort, TCGETS2, &tty) != 0) {
            throw std::runtime_error("Error from TCGETS2");
    }

    // Configure custom baud rate
    tty.c_cflag &= ~CBAUD;          // clear baud bits
    tty.c_cflag |= CBAUDEX;
    tty.c_ispeed = baud;
    tty.c_ospeed = baud;

    // Configure ontrol flags
    tty.c_cflag &= ~PARENB;			// Clear parity bit
    tty.c_cflag &= ~CSTOPB;			// Clear stop field, only one stop bit used
    tty.c_cflag |= CS8;				// 8 bits per byte
    tty.c_cflag &= ~CRTSCTS;		// Disable RTS/CTS hardware flow control
    tty.c_cflag |= CREAD | CLOCAL;	// Turn on READ & ignore ctrl lines (CLOCAL = 1)

    tty.c_lflag &= ~(ICANON | ECHO | ECHOE | ECHONL);
    tty.c_iflag &= ~(IXON | IXOFF | IXANY);
    tty.c_iflag &= ~(IGNBRK|BRKINT|PARMRK|ISTRIP|INLCR|IGNCR|ICRNL);
    tty.c_oflag &= ~OPOST;
    tty.c_oflag &= ~ONLCR;

    tty.c_cc[VTIME] = 0;	// Wait indefinetly or
    tty.c_cc[VMIN] = 1;		// when 1 bytes get received

    if (ioctl(m_serialPort, TCSETS2, &tty) != 0) {
        throw std::runtime_error("Error from TCSETS2");
    }
}

Parser::~Parser() {
    if(!m_serialPort)
        close(m_serialPort);
}

uint8_t Parser::readByte() {
    uint8_t byte[1];
    read(m_serialPort, byte, 1);
    return byte[0];
}

std::string Parser::fullWordToHex(uint32_t fullword) {
    std::ostringstream oss;
    oss << "0x" << std::hex << std::uppercase
        << std::setw(8) << std::setfill('0')
        << fullword;
    return oss.str();
}

std::string Parser::halfWordToHex(uint16_t halfWord) {
    std::ostringstream oss;
    oss << "0x" << std::hex << std::uppercase
        << std::setw(4) << std::setfill('0')
        << halfWord;
    return oss.str();
}


std::string Parser::byteToHex(uint8_t byte) {
    std::ostringstream oss;
    oss << "0x" << std::hex << std::uppercase
        << std::setw(2) << std::setfill('0')
        << static_cast<int>(byte);
    return oss.str();
}