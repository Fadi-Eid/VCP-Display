import serial

# --- CONFIG ---
SERIAL_PORT = '/dev/ttyACM0'
BAUDRATE = 7400000

ser = serial.Serial(SERIAL_PORT, baudrate=BAUDRATE, timeout=1)

ser.reset_input_buffer()

while True:
    data = ser.read(1)

    if data:
        print("Received:", " ".join(f"{b:02X}" for b in data))