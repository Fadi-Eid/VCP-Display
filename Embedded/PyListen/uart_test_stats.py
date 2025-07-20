import serial
import time

# --- CONFIG ---
SERIAL_PORT = '/dev/ttyACM0'
BAUDRATE = 7400000
CHUNK_SIZE = 6000
EXPECTED_BYTE = 0xAA
THROUGHPUT_INTERVAL = 1.0
PRINT_FIRST_N_BYTES = 16

# --- Feature Toggles ---
PRINT_ERRORS = True
SHOW_THROUGHPUT = True
SHOW_RX_DATA = False

# --- INIT ---
ser = serial.Serial(SERIAL_PORT, baudrate=BAUDRATE, timeout=1)
start_time = time.time()
last_report = start_time
total_bytes = 0
error_bytes = 0

print("Started reading UART stream...")

try:
    while True:
        data = ser.read(CHUNK_SIZE)
        now = time.time()

        if data:
            chunk_len = len(data)
            total_bytes += chunk_len

            # Error checking
            errors_in_chunk = sum(b != EXPECTED_BYTE for b in data)
            error_bytes += errors_in_chunk

            # Print received data if enabled
            if SHOW_RX_DATA:
                first_bytes = " ".join(f"{b:02X}" for b in data[:PRINT_FIRST_N_BYTES])
                print(f"Received {chunk_len} bytes: {first_bytes} ...")

            # Print errors if enabled
            if PRINT_ERRORS and errors_in_chunk > 0:
                print(f"⚠️  Errors this chunk: {errors_in_chunk} / {chunk_len}")

            # Throughput report if enabled
            if SHOW_THROUGHPUT and (now - last_report >= THROUGHPUT_INTERVAL):
                elapsed = now - start_time
                kbps = total_bytes / elapsed / 1024
                mbps = total_bytes * 8 / elapsed / 1_000_000
                error_rate = (error_bytes / total_bytes * 100) if total_bytes else 0
                print(f"[{elapsed:.2f}s] {total_bytes} bytes | {kbps:.2f} KB/s | {mbps:.2f} Mbps | Errors: {error_rate:.4f}%")
                last_report = now

except KeyboardInterrupt:
    print("\nMeasurement stopped.")
    final_error_rate = (error_bytes / total_bytes * 100) if total_bytes else 0
    print(f"Final error rate: {final_error_rate:.6f}% ({error_bytes} wrong bytes out of {total_bytes})")
