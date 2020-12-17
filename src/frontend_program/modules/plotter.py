from . import serial_communication as SC


def nths(num):
    result = hex(int(num)).lstrip("0x").rstrip("L")
    while len(result) < 4:
        result = "0" + result
    return result


class Plotter:
    def __init__(self):
        self.comm = SC.SerialCommunicator()
        self.x = 0
        self.y = 0
        self.maxX = 100
        self.maxY = 100

    def turn_off(self):
        return self.comm.send_command("TOFF")

    def test_x(self):
        return self.comm.send_command("TSTX")

    def test_y(self):
        return self.comm.send_command("TSTY")

    def test_z(self):
        return self.comm.send_command("TSTZ")

    def pen_up(self):
        return self.comm.send_command("PENU")

    def pen_down(self):
        return self.comm.send_command("PEND")

    def home(self):
        return self.comm.send_command("HOME")

    def move(self, x1, y1, x2, y2):
        command = "MOVE" + nths(x1) + nths(y1) + nths(x2) + nths(y2)
        return self.comm.send_command(command)

    def draw_line(self, x1, y1, x2, y2):
        command = "DRLN" + nths(x1) + nths(y1) + nths(x2) + nths(y2)
        return self.comm.send_command(command)

    def draw_segment(self, x, y):
        command = "DRSG" + nths(x) + nths(y)
        return self.comm.send_command(command)
