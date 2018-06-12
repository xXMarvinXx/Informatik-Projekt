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
int inPin = 10; // Pushbutton Pin.
int inPin2 = 5; //Pushbutton zum Briefkastenöffnen
int val = 0; // Variable zum Lesen des 1. Buttons 
int val2 = 0; // Variable zum auslesen des 2. Buttons
int servoAngle = 0;   // servo position in degrees
int Zaehler = 0;  //Zählt wie viele Briefe gekommen sind
int servoPin = 8; // Pin für den Servo der den Briefkasten öffnet
int LED1 = 11;   // LED die am Briefkasten anzeigt , dass Post gekommen ist.
int a ;

void setup()
{
  Serial.begin(9600);
  esp_serial.begin(9600);
  servo.attach(servoPin);
  pinMode(inPin, INPUT_PULLUP);    // declare pushbutton as input
   pinMode(inPin2, INPUT);
   pinMode (LED1 , OUTPUT);
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
  Serial.println("Starting server...");
  esp_server.begin(&esp_serial, "AndroidAP", "fdqz0801", 30303);
  Serial.println("...server is running");


  /* Get and print the IP-Address the python program
     should connect to */
  char ip[16];
  esp_server.my_ip(ip, 16);

  Serial.print("My ip: ");
  Serial.println(ip);
}

void loop()
{  
  if (Zaehler == 0)
  {
  digitalWrite (11 , HIGH);
  delay(1000);
  Zaehler++ ;
  return(Zaehler);
  }
  delay(2000);
   Zaehler ++;
 val2 = digitalRead(inPin2);
 val = digitalRead(inPin); //Auslesen ob Button gedrückt wurde.
  if (val == HIGH) //Wenn Button gedrückt wurde. 
  {   
   Zaehler ++;
   esp_server.write(Zaehler);
   servo.write(45);      // öffnet den Briefkasten für 10 Sekunden
   delay(10000);          // Wait 10 seconds
   servo.write(90);      // Schließt den Briefkasten
   
   
  }
  if (val2 == LOW) 
  {
   int Zaehler = 0;
   esp_server.write(Zaehler); 
  }
  
 
  
  
  
}
