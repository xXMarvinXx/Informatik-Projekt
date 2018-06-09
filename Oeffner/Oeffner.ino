

/*
Into Robotics
*/
 
#include <Servo.h> 
#include <Time.h> 
 
int servoPin1 = 9;
int servoPin2 = 10;
 
Servo servo;  
int Zaehler = 0; //Variable zum zählen der Anzahl der durchgeführten Öffnungen
int inPin1 = 6; // Pushbutton Pin.
int val1 = 0; // Variable zum Lesen des Pin-Status 
int val2 = 0; // VAriable zum lesen des Buttonstatus
int servoAngle = 0;   // servo position in degrees
int inPin2 = 12; // Pushbutton Pin2. Öffnet den Briefkasten zum Rausehmen der Post
 
void setup()
{
  Serial.begin(9600);  
  servo.attach(servoPin1);
  pinMode(inPin1, INPUT); // declare pushbutton as input
  Serial.begin(9600);  
  servo.attach(servoPin2);
  pinMode(inPin2, INPUT); //declare pushbutton 2 as input
}
 
 
void loop()
{
  
 val1 = digitalRead(inPin1); //Auslesen ob Button gedrückt wurde.
 val2 = digitalRead(inPin2); // Auslesen ob Button zum rausnehmen der Briefe geöffnet wurde.
  if (val1 == LOW) //Wenn Button gedrückt wurde. 
  {   
   servo.write(-45);      // öffnet den Briefkasten für 10 Sekunden
   delay(10000);          // Wait 10 seconds
   servo.write(90);      // Schließt den Briefkasten
   delay(10000);          // Wait 1 second
   Zaehler = Zaehler + 1 ; // Zaehler der Anzahl der Öffnungen erhöht sich um eins.
  }
  if (val2 == LOW) //Wenn Button gedrückt wurde. 
  {   
   servo.write(-45);      // öffnet den Briefkasten für 10 Sekunden
   delay(10000);          // Wait 10 seconds
   servo.write(90);      // Schließt den Briefkasten
   delay(10000);          // Wait 1 second
   int Leerung = 1 ;      // gibt einen Wert aus der angibt das geleert wurde.
  }
}
