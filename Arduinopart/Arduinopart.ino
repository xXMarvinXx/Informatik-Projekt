#include <Servo.h>
#include <Time.h>
#include "DumbServer.h"
#include <SoftwareSerial.h>

int servoPin1 = 9;

Servo servo1;

SoftwareSerial esp_serial(3, 2);
EspServer esp_server;

unsigned long timer1;
unsigned long timer10;

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

}
void loop() {
  val1 = digitalRead(inPin1); //Auslesen ob Button gedrückt wurde.
  val2 = digitalRead(inPin2); // Auslesen ob Button zum rausnehmen der Briefe geöffnet wurde.

  if (val1 == LOW) //Wenn Button gedrückt wurde.
  {
    servo1.write(0);
    timer10 = millis(); 
    Zaehler ++;
    servo1.write(+90);
      }
      if (millis() - timer10 >= 100000) { /* nach 10 Sekunden*/
       servo1.write(-90);      // Schließt den Briefkasten 
       esp_server.write("y");
       timer10 = 0;
   
  }
  if (Zaehler > 0){
    digitalWrite(led , HIGH); /* Wenn Post da ist lass die LED leuchten. */
  }
  if (val2 == LOW) /*Wenn reset Button gedrückt wurde */
    {
      Zaehler = 0;
      /* setzte den Post-Zaehler auf 0 zurück */
      if(Zaehler == 0)
      {
        digitalWrite (led , LOW);
              /* Die Led ist aus wenn keine Post da ist .*/
      }
    }
  
  
    
  

  
  
    
    
  
  


}

