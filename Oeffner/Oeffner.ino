

/*
Into Robotics
*/
 
#include <Servo.h> 
 
int servoPin = 9;
 
Servo servo;  
int Zaehler = 0; //Variable zum zählen der Anzahl der durchgeführten Öffnungen
int inPin = 7; // Pushbutton Pin.
int val = 0; // Variable zum Lesen des Pin-Status 
int servoAngle = 0;   // servo position in degrees
 
void setup()
{
  Serial.begin(9600);  
  servo.attach(servoPin);
  pinMode(inPin, INPUT);    // declare pushbutton as input
}
 
 
void loop()
{

 val = digitalRead(inPin); //Auslesen ob Button gedrückt wurde.
  if (val == LOW) //Wenn Button gedrückt wurde. 
  {   
   servo.write(45);      // öffnet den Briefkasten für 10 Sekunden
   delay(10000);          // Wait 10 seconds
   servo.write(90);      // Schließt den Briefkasten
   delay(10000);          // Wait 1 second
   Zaehler = Zaehler + 1 ; // Zaehler der Anzahl der Öffnungen erhöht sich um eins.
  }
}
