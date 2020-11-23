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
        if command.find("-y") != -1:
            print("TSTY()")
            p.test_y()
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
    if command.find("seg") == 0:
        word = command[4:len(command)].split()
        print(word[0] + " " + word[1])
        p.draw_segment(int(word[0]), int(word[1]))
    if command.find("write") == 0:
        
    if command.find("home") == 0:
        p.home()
    if command.find("exit") == 0:
        print("goodbye")
        p.turn_off()
        sys.exit(0)
    pass



def begin():
    while True:
        command = prompt()
        interpret_command(command)

def countLetters(word):
    size = len(word)
    space = 10
    scale = (1000/(size + 1)) - (size * space)
    x = scale/2
    y = scale/2
    factor = scale/21 #this is the scaling factor to write letters
    for i in word:
        drawLetter(i, x, y, factor)
        x += (scale + space)
        
def drawLetter(l, x, y, scale):
    if (l == ' '):
        return
    if (l == 'A'):
        p.draw_line(x+scale*0, y+scale*0, x+scale*9, y+scale*21)
        p.draw_segment(x+scale*17, y+scale*0)
        p.draw_line(x+scale*4, y+scale*8, x+scale*14, y+scale*8)
        return
