# Control-my-Computer-with-Hands-using-Arduino
~In acest proiect voi folosi Arduino si python pentru a controla BS Player-ul.
Mai exact, cu ajutorul celor 2 senzori ultrasonici voi masura distanta de la maini pana la monitor si in functie de aceasta distanta se va executa o anumita comanda. Comenzile din Arduino sunt trimise pc-ul prin serial port. De acolo sunt citite de Python, iar cu ajutorul librariei pyautogui, vom controla tastatura si mouse-ul.


Comenzi:
1. Pause/Play - cand ambele maini sunt in fata senzorilor 
2. Forward/Rewind - cand mana dreapta este in fata senzorului
3.Increasing/decreasing volume- cand mana stanga este in fata senzorului.


~ Componente necesare: 
     -2x ultrasonic sensor
     -arduino Uno
     -connecting wires
     -breadboard
     
Cei doi senzori sunt conectati la pinii digitali ai placii arduino, si la GND si 5V.     







Python code:


import serial #Serial imported for Serial communication
import time #Required to use delay functions
import pyautogui used for controlling keyboard and mouse

ArduinoSerial = serial.Serial('com4',9600) #Create Serial port object called arduinoSerial
time.sleep(2) #wait for 2 seconds for the communication to get established

//Here is my code for opening my movie

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

