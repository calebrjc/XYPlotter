from . import plotter as Plotter

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
    if command.find("draw") == 0:
        p.draw_line(0, 0, 1000, 1000)
    pass


def begin():
    while True:
        command = prompt()
        interpret_command(command)
