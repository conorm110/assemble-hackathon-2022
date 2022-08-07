import serial
import pyautogui
ser = serial.Serial('COM3', 9600, timeout=None, xonxoff=False, rtscts=False, dsrdtr=False) #Tried with and without the last 3 parameters, and also at 1Mbps, same happens.
ser.flushInput()
ser.flushOutput()
while True:
    bytesToRead = ser.inWaiting()
    temp = ser.read(bytesToRead)
    if str(temp) != "b\'\'":
        pyautogui.press(str(temp)[2])