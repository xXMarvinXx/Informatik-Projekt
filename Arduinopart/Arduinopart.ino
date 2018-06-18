#include <Servo.h>
#include "DumbServer.h"
#include <SoftwareSerial.h>

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
  esp_server.begin(&esp_serial, "AndroidAP", "fdqz0801", 30303);
  Serial.println("...server is running");
  /* Am Anfang liegt keine Post drinne */
}
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
  }
}




