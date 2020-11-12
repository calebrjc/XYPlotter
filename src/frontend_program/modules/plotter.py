from . import serial_communication as SC

comm = SC.SerialCommunicator()

class Plotter:
  def __init__(self):
    pass

  def turn_off():
    res = comm.send_command("TOFF")
    return "OK" if res else "ERROR"
