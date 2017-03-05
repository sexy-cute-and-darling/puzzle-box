/*
  Hello World.ino
  2013 Copyright (c) Seeed Technology Inc.  All right reserved.

  Author:Loovee
  2013-9-18

  Grove - Serial LCD RGB Backlight demo.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include <Wire.h>
#include "rgb_lcd.h"
#include "hp_game.h"
#include <Servo.h>
Servo servoMain; // Define our Servo

rgb_lcd lcd;
hp_game game;

const int pinTouch = 3;               // pin of Touch Sensor
const int pinButton = 2;
const int potentiometer = A0;
const int pinLed = 13;

//Sound Sensor
const int pinSound = A1;               // pin of Sound Sensor
int soundThreshold = 800;              // the threshold to turn on or off the LED

//Light Sensor
const int pinLight = A2;              // pin of Light Sensor
int lightThreshold = 750;              // the threshold to turn on or off the LED

// Temperature Sensor
const int pinTemp = A3;
int tempThreshold = 25;
float temperature;
int B = 3975;                         //  B Value of the Thermistor
float resistance;

int servoAngle = 0;

void setup() 
{
    Serial.begin(9600);                         // set the serial communication frequency at 9600 bits per sec
    pinMode(potentiometer, INPUT);
    pinMode(pinSound, INPUT);
    pinMode(pinLight, INPUT);
    pinMode(pinButton, INPUT);
    pinMode(pinTouch, INPUT);
    pinMode(pinTemp, INPUT);
    
    // set up the LCD's number of columns and rows:
    lcd.begin(16, 2);
    game.begin();

    servoMain.attach(7);
    servoMain.write(0);

    delay(1000);
}

/*
if(lightSensor>lightThreshold)
if(digitalRead(pinTouch))
if(soundSensor>soundThreshold)
*/

void loop()
{
    lcd.clear();
    
    // Button
    if (digitalRead(pinButton)) {
      game.clickButton();
    }

    // Temperature
    int tempSensor = analogRead(pinTemp);
    resistance=(float)(1023-tempSensor)*10000/tempSensor;    // get resistance
    temperature=1/(log(resistance/10000)/B+1/298.15)-273.15; 
    if (temperature>tempThreshold) {
      game.hitTemperature();
    }

    //Sound
    if (analogRead(pinSound) > soundThreshold) {
      game.hitSound();
    }

    // Light
    if (analogRead(pinLight) > lightThreshold) {
      game.hitLight();
    }

    // Touch & Button
    if (digitalRead(pinTouch) && digitalRead(pinButton)) {
      game.hitDoublePress();
    }

    // Potentiometer
    game.updatePotentiometer(analogRead(potentiometer));
    struct Color gcolor = game.getColor();
    lcd.setRGB(gcolor.r, gcolor.g, gcolor.b);

    // Victory?
    if (game.isWinner()) {
      lcd.print("Victory!");
      lcd.setCursor(0, 1);
      lcd.print(game.getState());
      delay(9000);
      servoMain.write(180);
      delay(1000);
    } else {
      lcd.print("Try Harder!");
      lcd.setCursor(0, 1);
      lcd.print(game.getState());
      delay(500);
    }
}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
