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





Arduino code:


const int trigger1 = 4; //Trigger pin of 1st Sensor
const int echo1 = 5; //Echo pin of 1st Sensor
const int trigger2 = 2; //Trigger pin of 2nd Sensor
const int echo2 = 3;//Echo pin of 2nd Sensor

long time_taken;
int dist,distL,distR;     // dist= distanta calculata de la o mana la senzor. distL= distanta pt mana stanga. distL= distanta pt mana dreapta.

 

void setup() {

//The Serial communication between Arduino and python takes places at a baud rate of 9600.
Serial.begin(9600); 
  
pinMode(trigger1, OUTPUT); 
pinMode(echo1, INPUT); 
pinMode(trigger2, OUTPUT); 
pinMode(echo2, INPUT); 

}

/*###Function to calculate distance###*/
void calculate_distance(int trigger, int echo)
{

digitalWrite(trigger, LOW);
delayMicroseconds(2);
digitalWrite(trigger, HIGH);
delayMicroseconds(10);
digitalWrite(trigger, LOW);

time_taken = pulseIn(echo, HIGH);
dist= time_taken*0.034/2;
if (dist>50)
dist = 50;

}

void loop() 
{

calculate_distance(trigger1,echo1);
distL =dist; //get distance of left sensor

calculate_distance(trigger2,echo2);
distR =dist; //get distance of right sensor

//Uncomment for debudding
/*Serial.print("L=");
Serial.println(distL);
Serial.print("R=");
Serial.println(distR);*/


//Pause Modes -Hold
if ((distL >40 && distR>40) && (distL <50 && distR<50)) //Detect both hands
{
Serial.println("Play/Pause"); 
delay (500);
}

calculate_distance(trigger1,echo1);
distL =dist;

calculate_distance(trigger2,echo2);
distR =dist;

 

//Control Modes
//Lock Left - Control Mode
if (distL<40 && distR>40)
{
  delay(100); //Hand Hold Time
  calculate_distance(trigger1,echo1);
  distL =dist;
  
  if (distL>=10 && distL<=40)
  {
    Serial.println("Left Locked");
    while(distL<=40)
    {
      calculate_distance(trigger1,echo1);
      distL =dist;
      if (distL<20) //Hand pushed in 
      {Serial.println ("Vup"); delay (700);}
      if (distL>22) //Hand pulled out
      {Serial.println ("Vdown"); delay (700);}
    }
  }
}

//Lock Right - Control Mode
if (distL>40 && distR<40)
{
  delay(100); //Hand Hold Time
  calculate_distance(trigger2,echo2);
  distR =dist;
  if (distR>=10 && distR<=40)
  {
    Serial.println("Right Locked");
    while(distR<30 )
    {
      calculate_distance(trigger2,echo2);
      distR =dist;
      if (distR<20) //Right hand pushed in
      {Serial.println ("Rewind"); delay (500);}
      if (distR>22) //Right hand pulled out
      {Serial.println ("Forward"); delay (500);}
  }
}
}

delay(200);
}


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

