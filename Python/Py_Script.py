import serial
import time
import csv
from datetime import datetime

# Serial port settings
COM_PORT = 'COM4'        # Arduino
BAUD_RATE = 115200
TIMEOUT = 1

# Generate timestamped CSV filenames
def generate_csv_filename(prefix="arduino_interactive"):
    timestamp = datetime.now().strftime("%Y%m%d_%H%M%S")
    return f"{prefix}_{timestamp}.csv"

def save_to_csv(log, filename):
    with open(filename, 'w', newline='') as csvfile:
        writer = csv.writer(
            csvfile,
            delimiter=',',
            quotechar='|',
            quoting=csv.QUOTE_MINIMAL)
        writer.writerow(['Command', 'Arduino Response'])
        for cmd, resp in log:
            writer.writerow([cmd, resp])

# Open Serial port
def open_serial(port=COM_PORT, baudrate=BAUD_RATE, timeout=TIMEOUT):
    ser = serial.Serial(port, baudrate, timeout=timeout)
    time.sleep(2)  # Wait for Arduino to initialize
    ser.reset_input_buffer()
    ser.reset_output_buffer()
    print(f"Connected to {ser.name}")
    return ser

# Show the control menu
def print_menu():
    print("\nArduino control command：")
    print("0: All LED OFF")
    print("1: RED LED ON")
    print("2: GREEN LED ON")
    print("3: BLUE LED ON")
    print("4: RGB ledTest()")
    print("5: remote() (listen to IR remote)")
    print("6: 8x8 LED_Matrix_functions")
    print("q: Quit program\n")

# Continuous listening for Remote output
def listen_remote(ser):
    print("\n--- Remote Control Mode ---")
    print("Press Ctrl+C to stop listening.\n")
    log = []
    try:
        while True:
            while ser.in_waiting:
                line = ser.readline().decode('latin-1').strip()
                if line:
                    print("Arduino Remote:", line)
                    log.append(("Remote", line))
            time.sleep(0.01)
    except KeyboardInterrupt:
        print("\nStopping Remote Control mode.")
    return log

# Interactive control
def interactive_control():
    ser = open_serial()
    log = []

    print_menu()

    while True:
        cmd = input("Enter command: ").strip()
        if cmd.lower() == 'q':
            break

        if cmd in ['0','1','2','3','4','5','6']:
            ser.write((cmd + '\n').encode())
            ser.flush()

            # For time-consuming commands, wait a bit
            if cmd in ['4', '6']:
                time.sleep(1.0)

            response = ""
            # Remote mode
            if cmd == '5':
                remote_log = listen_remote(ser)
                log.extend(remote_log)
            else:
                # Block-read Arduino output for up to 1 second
                start_time = time.time()
                timeout = 1.0
                while time.time() - start_time < timeout:
                    while ser.in_waiting:
                        line = ser.readline().decode('latin-1').strip()
                        if line:
                            print("Arduino:", line)
                            response += line + " "
                    time.sleep(0.01)
                log.append((cmd, response.strip()))
        else:
            print("Invalid command，input 0~6 or q Quit")

    ser.close()

    filename = generate_csv_filename()
    save_to_csv(log, filename)
    print(f"\nAll commands and Arduino responses are saved to {filename}")

# Main entry
if __name__ == "__main__":
    interactive_control()
