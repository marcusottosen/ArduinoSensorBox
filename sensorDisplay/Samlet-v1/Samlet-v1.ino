#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>
#include "BaroAndTemp.h"
#include "Photoresister.h"
#include "TempAndHum.h"

//Screen
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 4
#define CLK_PIN   5
#define DATA_PIN  7
#define CS_PIN    6
MD_Parola P = MD_Parola(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);

//MQ2 module (gas/smoke) - Needs to be initiated here
#include <MQ2.h>
#include <Wire.h>
MQ2 mq2(A2);

//Make objects & assign pin ()  "000" bcause arduino is weird
Photoresister light(000); //Pin hardcoded in class
TempAndHum humid(000); //pin hardcoded in class
BaroAndTemp baro(000); //Pin hardcoded in library

const int buttonPin = 3;

int buttonState = 0;
int count = 0;
String toPrint = "Startup";
String sensorValue = "#";

void setup() {
  //Serial.begin(9600);
  baro.initBaro();

  mq2.begin();

  P.begin();
  P.setIntensity(0.3);
  pinMode(buttonPin, INPUT);
}

void loop() { //Evt. få hver part til at køre individuelt, så knappen kan tjekkes mellem hver af dem (flere mindre delays)
  buttonState = digitalRead(buttonPin);

  if (buttonState == HIGH) {
    if (count < 7) {
      count++;
    } else {
      count = 0;
    }
  }


  if (count == 0) {                       //TEMPERATURE
    float x = (humid.temp() + (baro.tempValue())) / 2;
    String temp = String(x, 1);
    toPrint = "   " + temp + "@";

  } else if (count == 1) {                //HUMIDITY
    sensorValue = humid.humidity();
    toPrint = "RH: " + sensorValue + "%";

  } else if (count == 2) {                //PRESSURE
    int x = baro.baroValue();
    sensorValue = x;
    toPrint = "hPa: " + sensorValue;

  } else if (count == 3) {                //LIGHT
    sensorValue = light.lightValue();
    toPrint = "LYS: " + sensorValue;

  } else if (count == 4) {                //CO - in PPM
    int x = mq2.readCO();
    sensorValue = x;
    toPrint = "CO: " + sensorValue;

  } else if (count == 5) {                //LPG
    int x = mq2.readLPG();
    sensorValue = x;
    toPrint = "LPG: " + sensorValue;

  } else if (count == 6) {                //SMOKE
    int x = mq2.readSmoke();
    sensorValue = x;
    toPrint = "RoG: " + sensorValue;
  } else if (count == 7) {
    toPrint = "  SIMON";
  }
  P.print(toPrint);

  delay(600); //ms
}
