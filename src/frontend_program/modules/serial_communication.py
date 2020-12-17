import time

import serial

com_port = "COM6"


class SerialCommunicator:
    def __init__(self):
        self._ser = None
        self.serial_init()

    def serial_init(self):
        "Initializes the plotter."

        print("Initializing plotter", end="")

        # Initialize serial connection
        self._ser = serial.Serial(com_port, 9600, timeout=.1)

        print(".", end="")

        # Clearing I/O buffers
        self._ser.reset_input_buffer()

        print(".", end="")

        self._ser.reset_output_buffer()

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
        self._ser.write(command.encode())

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
            if self._ser.in_waiting <= 0:
                continue

            c = self._ser.read().decode()

            if recording:
                if c == ">":
                    reading = False
                if reading:
                    message += c

            if c == "<":
                recording = True

        return message
