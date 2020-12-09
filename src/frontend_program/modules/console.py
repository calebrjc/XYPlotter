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
        countLetters(command[6:len(command)])
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
    space = 25 - (size/2)
    scalex = int((1000/(size + 1)) - space)
    scaley = scalex * 2
    x = scalex/2
    y = 500 - (scaley/2)
    factorx = scalex/21 #this is the scaling factor to write letters
    factory = scaley/21
    for i in word:
        drawLetter(i, x, y, factorx, factory)
        x += int(scalex + space + (space/size))
    p.home()
def drawLetter(l, x, y, scalex, scaley):
    if (l == ' '):
        return
    if (l == 'A'):
        p.draw_line(x+scalex*10, y+scaley*21, x+scalex*0, y+scaley*0)
        p.draw_line(x+scalex*10, y+scaley*21, x+scalex*21, y+scaley*0)
        p.draw_line(x+scalex*0, y+scaley*12, x+scalex*21, y+scaley*12)
        return
    if (l == 'B'):
        p.draw_line(x+scalex*0, y+scaley*0, x+scalex*0, y+scaley*21)
        p.draw_line(x+scalex*21, y+scaley*18, x+scalex*14, y+scaley*21)
        p.draw_segment(x+scalex*0, y+scaley*21)
        p.draw_line(x+scalex*21, y+scaley*18, x+scalex*21, y+scaley*14)
        p.draw_segment(x+scalex*14, y+scaley*12)
        p.draw_segment(x+scalex*0, y+scaley*12)
        p.draw_line(x+scalex*21, y+scaley*9, x+scalex*14, y+scaley*12)
        p.draw_line(x+scalex*21, y+scaley*9, x+scalex*21, y+scaley*5)
        p.draw_segment(x+scalex*14, y+scaley*0)
        p.draw_segment(x+scalex*0, y+scaley*0)
        return
    if (l == 'C'):
        p.draw_line(x+scalex*0, y+scaley*5, x+scalex*21, y+scaley*0)
        p.draw_line(x+scalex*0, y+scaley*5, x+scalex*0, y+scaley*14)
        p.draw_segment(x+scalex*21, y+scaley*21)
        return
    if (l == 'D'):
        p.draw_line(x+scalex*0, y+scaley*0, x+scalex*0, y+scaley*21)
        p.draw_line(x+scalex*21, y+scaley*14, x+scalex*10, y+scaley*21)
        p.draw_segment(x+scalex*0, y+scaley*21)
        p.draw_line(x+scalex*21, y+scaley*14, x+scalex*21, y+scaley*7)
        p.draw_segment(x+scalex*10, y+scaley*0)
        p.draw_segment(x+scalex*0, y+scaley*0)
        return
    if (l == 'E'):
        p.draw_line(x+scalex*0, y+scaley*0, x+scalex*0, y+scaley*21)
       	p.draw_segment(x+scalex*21, y+scaley*21)
        p.draw_line(x+scalex*0, y+scaley*10, x+scalex*21, y+scaley*10)
        p.draw_line(x+scalex*0, y+scaley*0, x+scalex*21, y+scaley*0)
        return
    if (l == 'F'):
        p.draw_line(x+scalex*0, y+scaley*0, x+scalex*0, y+scaley*21)
        p.draw_segment(x+scalex*21, y+scaley*21)
        p.draw_line(x+scalex*0, y+scaley*14, x+scalex*21, y+scaley*14)
        return
    if (l == 'G'):
        p.draw_line(x+scalex*0, y+scaley*5, x+scalex*21, y+scaley*0)
        p.draw_line(x+scalex*0, y+scaley*5, x+scalex*0, y+scaley*18)
        p.draw_segment(x+scalex*21, y+scaley*21)
        p.draw_line(x+scalex*21, y+scaley*7, x+scalex*10, y+scaley*10)
        p.draw_line(x+scalex*21, y+scaley*7, x+scalex*21, y+scaley*0)
        return
    if (l == 'H'):
        p.draw_line(x+scalex*0, y+scaley*0, x+scalex*0, y+scaley*21)
        p.draw_line(x+scalex*0, y+scaley*12, x+scalex*21, y+scaley*12)
        p.draw_line(x+scalex*21, y+scaley*21, x+scalex*21, y+scaley*0)
        return
    if (l == 'I'):
        p.draw_line(x+scalex*0, y+scaley*21, x+scalex*21, y+scaley*21)
        p.draw_line(x+scalex*10, y+scaley*21, x+scalex*10, y+scaley*0)
        p.draw_line(x+scalex*0, y+scaley*0, x+scalex*21, y+scaley*0)
        return
    if (l == 'J'):
        p.draw_line(x+scalex*0, y+scaley*21, x+scalex*21, y+scaley*21)
        p.draw_line(x+scalex*10, y+scaley*21, x+scalex*10, y+scaley*8)
        p.draw_line(x+scalex*8, y+scaley*0, x+scalex*10, y+scaley*8)
        p.draw_line(x+scalex*8, y+scaley*0, x+scalex*3, y+scaley*0)
        p.draw_segment(x+scalex*0, y+scaley*5)
        p.draw_segment(x+scalex*0, y+scaley*7)
        return
    if (l == 'K'):
        p.draw_line(x+scalex*0, y+scaley*0, x+scalex*0, y+scaley*21)
        p.draw_line(x+scalex*21, y+scaley*21, x+scalex*0, y+scaley*13)
        p.draw_segment(x+scalex*11, y+scaley*13)
        p.draw_segment(x+scalex*21, y+scaley*0)
        #p.draw_line(x+scalex*21, y+scaley*0, x+scalex*0, y+scaley*13)
        return
    if (l == 'L'):
        p.draw_line(x+scalex*0, y+scaley*0, x+scalex*0, y+scaley*21)
        p.draw_line(x+scalex*0, y+scaley*0, x+scalex*21, y+scaley*0)
        return
    if (l == 'M'):
        p.draw_line(x+scalex*0, y+scaley*0, x+scalex*0, y+scaley*21)
        p.draw_segment(x+scalex*10, y+scaley*14)
        p.draw_segment(x+scalex*21, y+scaley*21)
        p.draw_segment(x+scalex*21, y+scaley*0)
        return
    if (l == 'N'):
        p.draw_line(x+scalex*0, y+scaley*0, x+scalex*0, y+scaley*21)
        p.draw_line(x+scalex*0, y+scaley*21, x+scalex*10, y+scaley*10)
        p.draw_line(x+scalex*21, y+scaley*0, x+scalex*10, y+scaley*10)
        p.draw_line(x+scalex*21, y+scaley*0, x+scalex*21, y+scaley*21)
        return
    if (l == 'O'):
        p.draw_line(x+scalex*14, y+scaley*0, x+scalex*7, y+scaley*0)
        p.draw_segment(x+scalex*0, y+scaley*5)
        p.draw_segment(x+scalex*0, y+scaley*16)
        p.draw_segment(x+scalex*7, y+scaley*21)
        p.draw_segment(x+scalex*14, y+scaley*21)
        p.draw_segment(x+scalex*21, y+scaley*16)
        p.draw_segment(x+scalex*21, y+scaley*5)
        p.draw_segment(x+scalex*14, y+scaley*0)
        return
    if (l == 'P'):
        p.draw_line(x+scalex*0, y+scaley*0, x+scalex*0, y+scaley*21)
        p.draw_line(x+scalex*21, y+scaley*18, x+scalex*14, y+scaley*21)
        p.draw_segment(x+scalex*0, y+scaley*21)
        p.draw_line(x+scalex*21, y+scaley*18, x+scalex*21, y+scaley*14)
        p.draw_segment(x+scalex*14, y+scaley*11)
        p.draw_segment(x+scalex*0, y+scaley*11)
        return
    if (l == 'Q'):
        p.draw_line(x+scalex*14, y+scaley*0, x+scalex*7, y+scaley*0)
        p.draw_segment(x+scalex*0, y+scaley*5)
        p.draw_segment(x+scalex*0, y+scaley*16)
        p.draw_segment(x+scalex*7, y+scaley*21)
        p.draw_segment(x+scalex*14, y+scaley*21)
        p.draw_segment(x+scalex*21, y+scaley*16)
        p.draw_segment(x+scalex*21, y+scaley*5)
        p.draw_segment(x+scalex*14, y+scaley*0)
        p.draw_line(x+scalex*21, y+scaley*0, x+scalex*14, y+scaley*10)
        return
    if (l == 'R'): 
        p.draw_line(x+scalex*0, y+scaley*0, x+scalex*0, y+scaley*21)
        p.draw_segment(x+scalex*17, y+scaley*21)
        p.draw_segment(x+scalex*19, y+scaley*19)
        p.draw_segment(x+scalex*19, y+scaley*14)
        p.draw_segment(x+scalex*0, y+scaley*14)
        p.draw_line(x+scalex*14, y+scaley*14, x+scalex*21, y+scaley*0)
        return
    if (l == 'S'): 
        p.draw_line(x+scalex*21, y+scaley*21, x+scalex*7, y+scaley*21)
        p.draw_line(x+scalex*0, y+scaley*18, x+scalex*7, y+scaley*21)
        p.draw_line(x+scalex*0, y+scaley*18, x+scalex*0, y+scaley*14)
        p.draw_segment(x+scalex*7, y+scaley*11)
        p.draw_segment(x+scalex*14, y+scaley*11)
        p.draw_line(x+scalex*21, y+scaley*9, x+scalex*14, y+scaley*11)
        p.draw_line(x+scalex*21, y+scaley*9, x+scalex*21, y+scaley*3)
        p.draw_segment(x+scalex*14, y+scaley*0)
        p.draw_segment(x+scalex*0, y+scaley*0)
        return
    if (l == 'T'):
        p.draw_line(x+scalex*10, y+scaley*0, x+scalex*10, y+scaley*21)
        p.draw_line(x+scalex*0, y+scaley*21, x+scalex*21, y+scaley*21)
        return
    if (l == 'U'):
        p.draw_line(x+scalex*5, y+scaley*0, x+scalex*0, y+scaley*5)
        p.draw_line(x+scalex*0, y+scaley*5, x+scalex*0, y+scaley*21)
        p.draw_line(x+scalex*5, y+scaley*0, x+scalex*16, y+scaley*0)
        p.draw_segment(x+scalex*21, y+scaley*5)
        p.draw_segment(x+scalex*21, y+scaley*21)
        return
    if (l == 'V'):
        p.draw_line(x+scalex*10, y+scaley*0, x+scalex*0, y+scaley*21)
        p.draw_line(x+scalex*10, y+scaley*0, x+scalex*21, y+scaley*21)
        return
    if (l == 'W'):
        p.draw_line(x+scalex*7, y+scaley*0, x+scalex*0, y+scaley*21)
        p.draw_line(x+scalex*7, y+scaley*0, x+scalex*10, y+scaley*10)
        p.draw_line(x+scalex*14, y+scaley*0, x+scalex*10, y+scaley*10)
        p.draw_line(x+scalex*14, y+scaley*0, x+scalex*21, y+scaley*21)
        return
    if (l == 'X'):
        p.draw_line(x+scalex*10, y+scaley*10, x+scalex*21, y+scaley*21)
        p.draw_line(x+scalex*10, y+scaley*10, x+scalex*21, y+scaley*0)
        p.draw_line(x+scalex*10, y+scaley*10, x+scalex*0, y+scaley*21)
        p.draw_line(x+scalex*10, y+scaley*10, x+scalex*0, y+scaley*0)
        return
    if (l == 'Y'):
        p.draw_line(x+scalex*10, y+scaley*0, x+scalex*10, y+scaley*12)
        p.draw_segment(x+scalex*21, y+scaley*21)
        p.draw_line(x+scalex*10, y+scaley*12, x+scalex*0, y+scaley*21)
        return
    if (l == 'Z'):
        p.draw_line(x+scalex*0, y+scaley*21, x+scalex*21, y+scaley*21)
        p.draw_segment(x+scalex*0, y+scaley*0)
        p.draw_segment(x+scalex*21, y+scaley*0)
        return
