/* Grundlagen der Informatik I, SoSe 18
 Projekt: Briefkasten  
 Autoren: Marvin Heise , Joel Kiener , Reza Toosi
 Matrikelnummer: 4381335 , 4444028 , 2774454
 Datum: 14.06.18
 */
/**@file */
#include <Servo.h> /*Libraries*/
#include "DumbServer.h" 
#include <SoftwareSerial.h>

<<<<<<< HEAD
int servoPin1 = 9; //Pin für den Servo-Motor

Servo servo1; //Ermöglicht Nutzung der Servo-Motor Bibliothek

SoftwareSerial esp_serial(3, 2);
EspServer esp_server;

int Zaehler = 0; //Variable zum zählen der Anzahl der durchgeführten Öffnungen
int inPin1 = 11; //Button Außerhalb des Briefkasten, öffnet Postschlitz
int val1 = 0; //Variable zum Lesen des Buttonstatus des inneren Button
int val2 = 0; //Variable zum lesen des Buttonstatus des äußeren Button
int servoAngle1 = 0; //Winkel des Servo-Motors
int inPin2 = 13; //Button innerhalb des Briefkasten, resetet gezählte Einwürfe
int led = 12; //Led zum anzeigen ob Post im Briefkasten ist

void setup() {
  esp_serial.begin(9600);
  Serial.begin(9600);
  servo1.attach(servoPin1); //Verknüpft den Pin des Servo-Motors mit der Servo-Motor Bibliothek
  servo1.write(+90); //Setzt den Winkel auf Ausgangsposition
  pinMode(inPin1, INPUT_PULLUP); //Der Äußere Button wird als Input definiert
  pinMode(inPin2, INPUT_PULLUP); //Der innere Button wird als Input definiert
  pinMode(led, OUTPUT); //Die Led wird als Output definiert
=======
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
>>>>>>> 9c8007933246709a87d16cdbf0c47b51f791ca3d
  esp_server.begin(&esp_serial, "AndroidAP", "fdqz0801", 30303);
  Serial.println("...server is running");
  /**Get and print the IP-Address to which the Python should connect to */ 
  char ip[16];
  esp_server.my_ip(ip, 16);

  Serial.print("My ip: ");
  Serial.println(ip);
}
<<<<<<< HEAD
void loop() {
  millis(); //Startet einen Dauerhaft steigenden Zähler
  val1 = digitalRead(inPin1); //Auslesen ob Button zum öffnen des Briefschlitzes gedrückt wurde
  val2 = digitalRead(inPin2); // Auslesen ob Button zum restten des öffnungs-Zählers

  if (val1 == LOW) { //Wenn der äußere Button gedrückt wurde
    delay(1000); //Kurze Pause vor öffnen des Briefschlitzes
    servo1.write(0); //Der Servo-Motor wir auf die Audgangsposition Gesetzt
    delay(10000); //Pause vor schließen des Postschlitzes
    servo1.write(+90); //Der Servo-Motor schließt den Briefschlitz
    Zaehler++ ; //Anzahl der Einwürfe erhöht sich um eins
    esp_server.write("y\n");
  }

  if (val2 == LOW) { //Wenn der innere Button gedrückt wurde.
    Zaehler = 0; //Setzt die Anzahl der Einwürfe auf null zurück
    esp_server.write("n\n");
  }

  if (Zaehler >= 1) {
    digitalWrite(led, HIGH); //Led leuchtet wenn Briefe eingeworfen wurden
  }
  else {
    digitalWrite(led, LOW); //Led hört auf zu leuchten wenn die Anzahl der Einwürfe resetet wurde
=======
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
      esp_server.write("y\n"); /** say y to the client */
    }
  else 
  {
    esp_server.write("n\n");  /** say n to the client */
>>>>>>> 9c8007933246709a87d16cdbf0c47b51f791ca3d
  }
}




