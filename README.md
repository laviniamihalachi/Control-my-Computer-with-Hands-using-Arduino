# Control-my-Computer-with-Hands-using-Arduino
~In acest proiect voi folosi Arduino si python pentru a controla BS Player-ul.
Mai exact, cu ajutorul celor 2 senzori ultrasonici voi masura distanta de la maini pana la monitor si in functie de aceasta distanta se va executa o anumita comanda. Comenzile din Arduino sunt trimise pc-ul prin serial port. De acolo sunt citite de Python, iar cu ajutorul librariei pyautogui, vom controla tastatura si mouse-ul.


Comenzi:
1. Pause/Play - cand ambele maini sunt in fata senzorilor 
2. Forward/Rewind - cand mana dreapta este in fata senzorului
3. Increasing/decreasing volume- cand mana stanga este in fata senzorului.


~ Componente necesare: 
     - 2x ultrasonic sensor
     - arduino Uno
     - connecting wires
     - breadboard
     
Cei doi senzori sunt conectati la pinii digitali ai placii arduino, si la GND si 5V.     







