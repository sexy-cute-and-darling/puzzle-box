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

rgb_lcd lcd;
hp_game game;

const int pinTouch = 3;               // pin of Touch Sensor
const int potentiometer = A1;

void setup() 
{
    Serial.begin(9600);                         // set the serial communication frequency at 9600 bits per sec
    pinMode(potentiometer, INPUT);
    pinMode(pinTouch, INPUT);
    
    // set up the LCD's number of columns and rows:
    lcd.begin(16, 2);
    game.begin();
    // lcd.setRGB(colorR, colorG, colorB);

    delay(1000);
}

void loop()
{
    lcd.clear();
    if(digitalRead(pinTouch)) {
      game.clickButton();
      delay(1000);
    }
    int value = analogRead(potentiometer);
    game.updatePotentiometer(value);
    lcd.print(game.getState());
    struct Color gcolor = game.getColor();
    lcd.setRGB(gcolor.r, gcolor.g, gcolor.b);
    delay(500);
}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
