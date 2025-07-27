#include <CppLinuxSerial/SerialPort.hpp>
#include <vector>
#include <iomanip>  // for std::hex, std::setw, std::setfill

using namespace mn::CppLinuxSerial;

int main()
{
	// Create serial port object and open serial port at 7400000 baud
	SerialPort serialPort("/dev/ttyACM0", 7400000);
	serialPort.SetNumDataBits(NumDataBits::EIGHT);
	serialPort.SetNumStopBits(NumStopBits::ONE);
	serialPort.SetParity(Parity::NONE);
	serialPort.SetTimeout(1000); // Block for up to 1000ms to receive data
	serialPort.Open();

	// Buffer array to store received data
	std::vector<uint8_t> buffer;

	while(true)
	{
		// read a byte
		for(int i = 0; i<200; i++) {
			serialPort.ReadBinary(buffer);
		}

		for(auto byte : buffer) {
			std::cout << std::hex << std::uppercase            // Hex format, uppercase letters
								<< std::setw(2) << std::setfill('0')      // Width 2, pad with '0'
								<< static_cast<int>(byte) << " ";         // Print byte value
		}
		std::cout << std::endl;
		buffer.clear();

		
	}

	// Close the serial port
	serialPort.Close();
}