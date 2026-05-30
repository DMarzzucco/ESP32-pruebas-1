#include <Arduino.h>

#define LED 2

void setup() {
  Serial.begin(115200);
  pinMode(LED, OUTPUT);
}

void loop() {
  digitalWrite(LED, HIGH);
  Serial.println("Hola");
  delay(2000);
  digitalWrite(LED, LOW);
  Serial.println("Adios");
  delay(2000);
}