from . import plotter as Plotter

import sys

p = Plotter.Plotter()


def prompt():
    print("XYPLOTTER$", end=" ")
    return str(input())


def interpret_command(command):
    if command.find("test") == 0:
        if command.find("-x") != -1:
            print("TSTX()")
            p.test_x()
            p.test_y()
        if command.find("-y") != -1:
            print("TSTY()")
        if command.find("-z") != -1:
            print("TSTZ()")
        if command.find("-pu") != -1:
            print("TPNU()")
            p.pen_up()
        if command.find("-pd") != -1:
            print("TPDN()")
            p.pen_down()
    if command.find("draw") != -1:
        p.draw_line(0, 0, 1000, 1000)
    if command.find("exit") == 0:
        print("goodbye")
        sys.exit(0)
    pass



def begin():
    while True:
        command = prompt()
        interpret_command(command)
