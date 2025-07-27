#include <stdio.h>
#include <string.h>
#include <fcntl.h>			// Contains file controls like O_RDWR
#include <errno.h>			// Error integer and strerror() function
#include <unistd.h>			// write(), read(), close()
#include <sys/ioctl.h>
#include <asm/termbits.h>
#include <cstdint>

int main() {
	/* https://blog.mbedded.ninja/programming/operating-systems/linux/linux-serial-ports-using-c-cpp/ */
	// open serial port
    int serial_port = open("/dev/ttyACM0", O_RDWR);

	// check for errors
    if (serial_port < 0) {
        fprintf(stderr, "Error %i from open: %s\n", errno, strerror(errno));
        return 1;
    }

    struct termios2 tty;

    if (ioctl(serial_port, TCGETS2, &tty) != 0) {
        fprintf(stderr, "Error %i from TCGETS2: %s\n", errno, strerror(errno));
        return 1;
    }

	// Configure custom baud rate
    tty.c_cflag &= ~CBAUD;          // clear baud bits
    tty.c_cflag |= CBAUDEX;
    tty.c_ispeed = 7400000;
    tty.c_ospeed = 7400000;

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

    tty.c_cc[VTIME] = 0;	// Wait 0.1s max (1 decisecond)
    tty.c_cc[VMIN] = 1;		// returning when 2 bytes get received

    if (ioctl(serial_port, TCSETS2, &tty) != 0) {
        fprintf(stderr, "Error %i from TCSETS2: %s\n", errno, strerror(errno));
        return 1;
    }

	// Start reading loop
    int count = 0;
    uint8_t byte[1];

    while (1) {
        read(serial_port, byte, 1);
        printf("(%d) Resceived %02x\n", count++, byte[0]);
    }
   
    close(serial_port);
    return 0;
}
