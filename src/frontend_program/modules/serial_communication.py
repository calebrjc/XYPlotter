import time

import serial


class SerialCommunicator:
    def __init__(self):
        self.ser = None
        self.serial_init()

    def serial_init(self):
        # Initializing the plotter
        print("Initializing plotter", end="")

        # Initialize serial connection
        self.ser = serial.Serial("COM8", 9600, timeout=.1)

        print(".", end="")

        # Clearing I/O buffers
        self.ser.reset_input_buffer()

        print(".", end="")

        self.ser.reset_output_buffer()

        print(".", end="")

        # Waiting for ready message
        acknowledgement = self.get_serial_message()
        print(".", end="")
        if acknowledgement != "READY":
            print(". failed.")
            return False
        print(". done.")

        # Ensuring send_command() works as expected
        print("Testing communication between program and plotter", end="")

        # Send test command
        result = self.send_command("TEST")
        print(".", end="")
        if not result:
            print(". failed.")
            return False
        print(". done.")

        print("Plotter is initialized.")

        return True

    def send_serial_message(self, message):
        message.replace(" ", "")
        message.replace(",", "")

        while len(message) < 20:
            message += "0"

        command = "<" + message + ">"
        self.ser.write(command.encode())

    def send_command(self, message):
        self.send_serial_message(message)
        res = self.get_serial_message()
        return res

    def get_serial_message(self):
        reading = True
        recording = False
        message = ""
        c = ""

        while reading:
            if self.ser.in_waiting <= 0:
                continue

            c = self.ser.read().decode()

            if recording:
                if c == ">":
                    reading = False
                if reading:
                    message += c

            if c == "<":
                recording = True

        return message
