import serial #Serial imported for Serial communication
import time #Required to use delay functions
import pyautogui

ArduinoSerial = serial.Serial('com4',9600) #Create Serial port object called arduinoSerialData
time.sleep(2) #wait for 2 seconds for the communication to get established

pyautogui.moveTo(184, 337, 2)
pyautogui.click(button='right')
pyautogui.moveTo(490, 360, 2)
pyautogui.moveTo(495, 360, 1)
pyautogui.click()
time.sleep(6)
pyautogui.moveTo(617, 406,2)
pyautogui.doubleClick()

while 1:
    incoming = str (ArduinoSerial.readline()) #read the serial data and print it as line
    print incoming
    
    if 'Play/Pause' in incoming:
        pyautogui.typewrite(['space'], 0.2)

    if 'Rewind' in incoming:
        pyautogui.typewrite(['left'] ,0.7 ) 

    if 'Forward' in incoming:
        pyautogui.typewrite(['right'], 0.7) 

    if 'Vup' in incoming:
        pyautogui.typewrite(['up'], 0.2)
        

    if 'Vdown' in incoming:
        pyautogui.typewrite(['down'], 0.2)

    incoming = "";
