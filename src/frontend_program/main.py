from modules import serial_communication as SC, console as Console

comm = SC.SerialCommunicator()

def interpret_command(command):
    if command == "test":
        print("X, Y, or Z?", end=" ")
        axis = str(input())
        if axis.lower() == "x":
            print(comm.send_command("TSTX"))
        if axis.lower() == "y":
            print(comm.send_command("TSTY"))
        if axis.lower() == "z":
            print(comm.send_command("TSTZ"))
    elif command == "shutdown":
        print("Shutting down... done.", end="")
        quit()
    else:
        print("ERROR: Unrecognized command.")



def main():
    while True:
        command = Console.prompt()
        interpret_command(command)


if (__name__ == "__main__"):
    main()
