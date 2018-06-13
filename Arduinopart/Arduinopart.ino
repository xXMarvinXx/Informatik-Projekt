#include <Servo.h>
#include "DumbServer.h"
#include <SoftwareSerial.h>

int servoPin1 = 9;

Servo servo1;

SoftwareSerial esp_serial(3, 2);
EspServer esp_server;

unsigned long timer1 = 0 ;
int Zaehler = 0; //Variable zum zählen der Anzahl der durchgeführten Öffnungen
int inPin1 = 11; // Pushbutton Pin.
int val1 = 0; // Variable zum Lesen des Pin-Status
int val2 = 0; // VAriable zum lesen des Buttonstatus
int servoAngle1 = 0; // servo position in degrees
int inPin2 = 13; // Pushbutton Pin2. Öffnet den Briefkasten zum Rausehmen der Post
int led = 12;

void setup()
{
  esp_serial.begin(9600);
  Serial.begin(9600);

  servo1.attach(servoPin1);
  servo1.write(0);

  pinMode(inPin1, INPUT_PULLUP); // declare pushbutton as input
  pinMode(inPin2, INPUT_PULLUP); //declare pushbutton 2 as input
  pinMode(led, OUTPUT);

  esp_server.begin(&esp_serial, "AndroidAP", "fdqz0801", 30303);
  Serial.println("...server is running");
  /* Am Anfang liegt keine Post drinne */
}
void loop() {

  val1 = digitalRead(inPin1); //Auslesen ob Button gedrückt wurde.
  val2 = digitalRead(inPin2); // Auslesen ob Button zum rausnehmen der Briefe geöffnet wurde.

  if (val1 == LOW)/* Wenn Post da ist lass die LED leuchten. */ // Wenn Button gedrückt wurde.
  {
    servo1.write(0);
    Zaehler ++;
    servo1.write(+90);
    Serial.println("Banane");
    digitalWrite(led , HIGH);
    Serial.println(Zaehler);
    }
    // Schließt den Briefkasten
  
  if (val2 == LOW) /*Wenn reset Button gedrückt wurde */
  {
    Zaehler = 0;
    digitalWrite (led , LOW);
  }
  if (Zaehler > 0)
    {
      esp_server.write("y\n");
    }
  else 
  {
    esp_server.write("n\n");
  }
}




