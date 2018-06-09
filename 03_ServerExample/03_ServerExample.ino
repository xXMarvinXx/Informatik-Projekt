#include <SoftwareSerial.h>
#include "DumbServer.h"
#include <Servo.h>
/* The WiFi shield is connected to
   the Arduino pins 3 and 2, as the
   Arduino has only one hardware serial
   port (pins 0 and 1) we are using a
   serial port emulated in software. */
SoftwareSerial esp_serial(3, 2);
EspServer esp_server;

Servo servo ;
int inPin = 7; // Pushbutton Pin.
int val = 0; // Variable zum Lesen des Pin-Status 
int servoAngle = 0;   // servo position in degrees
int Zaehler = 0;
int servoPin = 8;

void setup()
{
  Serial.println("Starting server...");
  esp_server.begin(&esp_serial, "AndroidAP", "fdqz0801", 30303);
  Serial.println("...server is running");

   char ip[16];
  esp_server.my_ip(ip, 16);

  Serial.print("My ip: ");
  Serial.println("ip");
  
  Serial.begin(9600);
  esp_serial.begin(9600);
  servo.attach(servoPin);
  pinMode(inPin, INPUT);    // declare pushbutton as input

  /* Connect to the wireless network with the name "GDI"
     and password "password", change these to match
     your wifi settings.

     If anything fails begin() will not return.

     To debug possible problems you can flash a second
     Arduino with the "Bare Minimum" example,
     connect the GNDs of the two Arduinos,
     connect pin 3 or 2 of the Arduino with the Wifi-shield
     to pin 1(TX) of the other Arduino and use the Serial monitor
     to see the Wifi commands and error-messages. */
  

  /* Get and print the IP-Address the python program
     should connect to */

}

void loop()
{

 val = digitalRead(inPin); //Auslesen ob Button gedrückt wurde.
  if (val == LOW) //Wenn Button gedrückt wurde. 
  {   
   servo.write(45);      /* öffnet den Briefkasten für 10 Sekunden */
   delay(10000);          
   servo.write(90);      /* Schließt den Briefkasten */
             
   Zaehler ++;            /* Zählt wie viele Briefe eingeworfen wurden.*/
   esp_server.write("Zaehler\n");
   
  }
 


    
  
}
