#include <Servo.h>
#include <Time.h>

int servoPin1 = 9;
int servoPin2 = 10;

Servo servo1;
Servo servo2;

int Zaehler = 0; //Variable zum zählen der Anzahl der durchgeführten Öffnungen
int inPin1 = 11; // Pushbutton Pin.
int val1 = 0; // Variable zum Lesen des Pin-Status
int val2 = 0; // VAriable zum lesen des Buttonstatus
int servoAngle1 = 0; // servo position in degrees
int servoAngle2 = 0; 
int inPin2 = 12; // Pushbutton Pin2. Öffnet den Briefkasten zum Rausehmen der Post

void setup()
{
  Serial.begin(9600);
  servo1.attach(servoPin1);
  servo1.write(0);
  pinMode(inPin1, INPUT); // declare pushbutton as input
  servo2.write(0);
  servo2.attach(servoPin2);
  pinMode(inPin2, INPUT); //declare pushbutton 2 as input
}


void loop()
{

  val1 = digitalRead(inPin1); //Auslesen ob Button gedrückt wurde.
  val2 = digitalRead(inPin2); // Auslesen ob Button zum rausnehmen der Briefe geöffnet wurde.
  if (val1 == LOW) //Wenn Button gedrückt wurde.
  {
    servo1.write(0);
    delay(1000);
    servo1.write(90);// öffnet den Briefkasten für 10 Sekunden
    delay(10000);          // Wait 10 seconds
    servo1.write(0);      // Schließt den Briefkasten      
    Zaehler = Zaehler + 1 ; // Zaehler der Anzahl der Öffnungen erhöht sich um eins.
  }
  if (val2 == LOW) //Wenn Button gedrückt wurde.
  {
    servo2.write(0);
    delay(1000);
    servo2.write(90); // öffnet den Briefkasten für 10 Sekunden
    delay(10000);          // Wait 10 seconds
    servo2.write(0);      // Schließt den Briefkasten
    int Leerung = 1 ;      // gibt einen Wert aus der angibt das geleert wurde.
  }
}
