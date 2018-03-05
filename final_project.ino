//Arduino code:

const int trigger1 = 4; //Trigger pin of 1st Sensor
const int echo1 = 5; //Echo pin of 1st Sensor
const int trigger2 = 2; //Trigger pin of 2nd Sensor
const int echo2 = 3;//Echo pin of 2nd Sensor

long time_taken;
int dist, distL, distR;     // dist= distanta calculata de la o mana la senzor. distL= distanta pt mana stanga. distL= distanta pt mana dreapta.

void setup() {
//The Serial communication between Arduino and python takes places at a baud rate of 9600.
  Serial.begin(9600); 
  pinMode(trigger1, OUTPUT); 
  pinMode(echo1, INPUT); 
  pinMode(trigger2, OUTPUT); 
  pinMode(echo2, INPUT); 
}

/*###Function to calculate distance###*/
void calculate_distance(int trigger, int echo) {
  digitalWrite(trigger, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);
  time_taken = pulseIn(echo, HIGH);
  dist = time_taken * 0.034 / 2;
  if(dist > 50)
    dist = 50;
}

void loop() {
  calculate_distance(trigger1, echo1);
  distL = dist; //get distance of left sensor

  calculate_distance(trigger2, echo2);
  distR = dist; //get distance of right sensor

  //Uncomment for debudding
  /*Serial.print("L=");
  Serial.println(distL);
  Serial.print("R=");
  Serial.println(distR);*/
 
  //Pause Modes -Hold
  if((distL > 40 && distR > 40) && (distL < 50 && distR < 50)) {
   //Detect both hands
    Serial.println("Play/Pause"); 
    delay (500);
  }

  calculate_distance(trigger1, echo1);
  distL = dist;

  calculate_distance(trigger2, echo2);
  distR = dist;

  //Control Modes 
  //Lock Left - Control Mode
  if(distL < 40 && distR > 40) {
     delay(100); //Hand Hold Time
     calculate_distance(trigger1, echo1);
     distL = dist;
  
     if(distL >= 10 && distL <= 40) {
        Serial.println("Left Locked");
        while(distL <= 40) {
             calculate_distance(trigger1, echo1);
             distL = dist;
         
             if(distL < 20) { //Hand pushed in 
               Serial.println("Vup"); 
               delay(700);
             }
         
             if(distL > 22) { //Hand pulled out
               Serial.println("Vdown"); 
               delay(700);
             } 
        }
     }
  }
    
  

  //Lock Right - Control Mode
  if(distL > 40 && distR < 40) {
     delay(100); //Hand Hold Time
     calculate_distance(trigger2, echo2);
     distR = dist;
     if(distR >= 10 && distR <= 40) {
       Serial.println("Right Locked");
       while(distR < 30) {
            calculate_distance(trigger2, echo2);
            distR = dist;
        
            if(distR < 20) {  //Right hand pushed in
               Serial.println ("Rewind"); 
               delay(500);
            }
            if(distR > 22) { //Right hand pulled out
              Serial.println ("Forward"); 
              delay(500);
             } 
       }
     }
  }

  delay(200);
}
