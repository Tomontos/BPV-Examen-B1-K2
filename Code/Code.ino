// Include lilbray's
  #include<Servo.h>
// HC04 Sensor - Rechts  
    const int RtrigPin = 9;
    const int RechoPin = 10;
    long Rduration;
    int Rdistance;
// HC04 Sensor - Voor      
    const int VtrigPin = 8;
    const int VechoPin = 7;
    long Vduration;
    int Vdistance;
// HC04 Sensor - Links
    const int LtrigPin = 5;
    const int LechoPin = 6;
    long Lduration;
    int Ldistance;
// Servo defineren
  Servo Rechts;
  Servo Links;

// Opstarten van de robot
void setup(){
  // HC04 Sensor - Rechts  
    pinMode(RtrigPin, OUTPUT);
    pinMode(RechoPin, INPUT);
  // HC04 Sensor - Voor
    pinMode(VtrigPin, OUTPUT);
    pinMode(VechoPin, INPUT);
  // HC04 Sensor - Links
    pinMode(LtrigPin, OUTPUT);
    pinMode(LechoPin, INPUT);
  // Servo attach aan pin
    Links.attach(11);
    Rechts.attach(12);
  // Serial opstarten
    Serial.begin(9600);
  // Distance setup
    Distance();
}

// Nonstop uitvoeren van het script
void loop(){
  // Updaten van de afstandne
    Distance();
  if(Vdistance > 13){
    // Als de afstand tot de rechter muur tussen de 9 en 12 cm is moet de robot rechtdoor blijven rijden.
    if(Rdistance > 7 && Rdistance < 13){
      Links.write(100);
      Rechts.write(82);
    }
    // Als de afstand tot de rechter muur groter of gelijk aan 13 is moet de linker moter sneller draaien om de rechter muur te naderen.
    if(Rdistance >= 18 ){
      Links.write(110);
      Rechts.write(82);
    }
    // Als de afstand tot de rechter muur kleiner of gelijk aan 8 cm is moet de rechter  moter sneller draaien om de afstand van de muur te nemen.
    if(Rdistance <= 7){
      Links.write(100);
      Rechts.write(72);
    }    
  }

  if(Ldistance <= 20 && Rdistance > 20 && Vdistance <= 13) TurnLeft();        //Als linker sensor kleiner of gelijk aan 20 is, rechter sensor groter is dan 20 en voorafstand kleiner of gelijk aan 13 is sla links af.
  if(Ldistance > 20 && Rdistance > 20 && Vdistance <= 13) TurnLeft();         // Als linker sensor groter is dan 20, rechter sensor groter is dan 20 en voor sensor kleiner of gelijk is aan 13 sla links af.
  if(Rdistance <= 20 && Ldistance > 20 && Vdistance <= 13) TurnRight();       // Als rechter sensor klein of gelijk aan 20 is, linker sensor groter dan 20 en voor sensor kleiner of gelijk aan 13 is sla rechts af.
  if(Rdistance <= 20 && Ldistance <= 20 && Vdistance <= 13) TurnArround();    // Als rechter sensor kleiner of gelijk aan 20 is, linker sensor kleiner of gelijk aan 20 is en voor sensor kleiner of gelijk aan 13 is draai om.
}

// Functie om de robot 90 graden naar links te laten draaien wanneer er geen uitgang aan de voor en rechter kant is.
void TurnRight(){
  delay(425);
  Links.write(100);
  Rechts.write(100);
  delay(500);
}

// Functie om de robot 90 graden naar rechts te laten draaien wanneer er geen uitgang aan de voor en linker kant is.
void TurnLeft(){
  delay(425);
  Links.write(82);
  Rechts.write(82);
  delay(500);
}

// Functie om de robot 180 graden te laten draaien als er geen weg voor, rechts of links is.
void TurnArround(){
  delay(425);
  Links.write(82);
  Rechts.write(82);
  delay(700);
}

// HC-04 sensoren uitlezen & opslaan in variable
void Distance(){
  // HC04 Sensor - Rechts  
  digitalWrite(RtrigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(RtrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(RtrigPin, LOW);
  Rduration = pulseIn(RechoPin, HIGH);
  Rdistance= Rduration*0.034/2;
// HC04 Sensor - Voor  
  digitalWrite(VtrigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(VtrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(VtrigPin, LOW);
  Vduration = pulseIn(VechoPin, HIGH);
  Vdistance= Vduration*0.034/2;
// HC04 Sensor - Links
  digitalWrite(LtrigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(LtrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(LtrigPin, LOW);
  Lduration = pulseIn(LechoPin, HIGH);
  Ldistance= Lduration*0.034/2;
}
