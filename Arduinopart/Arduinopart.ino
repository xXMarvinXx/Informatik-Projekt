/* Grundlagen der Informatik I, SoSe 18
 Projekt: Briefkasten  
 Autoren: Marvin Heise , Joel Kiener , Reza Toosi
 Matrikelnummer: 4381335 , 4444028 , :::::
 Datum: 14.06.18
 */
/**@file */
#include <Servo.h> /*Libraries*/
#include "DumbServer.h" 
#include <SoftwareSerial.h>

/**The Wifi shield is connected to 
 * the Arduino-Pins 2 and 3
 */
SoftwareSerial esp_serial(3, 2);
EspServer esp_server;

Servo servo1; /*!<define servo1 as a Servo for the servo library */

int servoPin1 = 9; /*!<define Pin 9 as the Servo Pin */
int Zaehler = 0;   /*!<define a Counter for how often the Mailbox has been opened*/
int inPin1 = 11;   /*!<define the Pin 11 for the 1. Pushbutton */
int val1 = 0;      /*!<define the val1 for the Pushbutton 1 */
int val2 = 0;      /*!<define the val2 for the Pushbutton 2 */
int servoAngle1 = 0;    /*!<define the servoAngle as 0 as starting Angle */
int inPin2 = 13;        /*!<define the Pin 13 for the Pushbutton 2*/
int led = 12;           /*!<define the Pin 12 for the LED > */

void setup() //!<setup the wifi-shied + server. additionally declare Pin as Output or Input
{
  esp_serial.begin(9600); /*!<send to the Client on 9600 Baud> */
  Serial.begin(9600);     /*!<send to the SerialPort on 9600 Baud> */

  servo1.attach(servoPin1);   /*!< declare ServoPin1 as a Servopin for the Library */
  servo1.write(0);            /*!< set the poristion of the ServoPin to 0 */

  pinMode(inPin1, INPUT_PULLUP); /** declare pushbutton as input */
  pinMode(inPin2, INPUT_PULLUP); /** declare pushbutton 2 as input */
  pinMode(led, OUTPUT);          /** declare LED as Output */

  Serial.println("Starting server..."); 
  esp_server.begin(&esp_serial, "AndroidAP", "fdqz0801", 30303);
  Serial.println("...server is running");
  /**Get and print the IP-Address to which the Python should connect to */ 
  char ip[16];
  esp_server.my_ip(ip, 16);

  Serial.print("My ip: ");
  Serial.println(ip);
}
void loop() //<! Start Loop
{

  val1 = digitalRead(inPin1); /*Auslesen ob Button gedrückt wurde. */
  val2 = digitalRead(inPin2); /* Auslesen ob Button zum rausnehmen der Briefe geöffnet wurde. */

  if (val1 == LOW)
  {
    servo1.write(0); 
    delay(10000);
    Zaehler ++;
    servo1.write(+90); 
    digitalWrite(led , HIGH); 
    }
    
  
  if (val2 == LOW) 
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




