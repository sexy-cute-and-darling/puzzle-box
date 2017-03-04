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

rgb_lcd lcd;

const int colorR = 125;
const int colorG = 0;
const int colorB = 130;

const int potentiometer = A0;                    // rotary angle sensor connect to A0

void setup() 
{
    // Serial.begin(9600);                         // set the serial communication frequency at 9600 bits per sec
    pinMode(potentiometer, INPUT);
    
    // set up the LCD's number of columns and rows:
    lcd.begin(16, 2);
    
    lcd.setRGB(colorR, colorG, colorB);

    delay(1000);
}

void loop() 
{
    int color = 0;
    for (int i=0; i<10; i++){
      lcd.clear();
      // Print a message to the LCD.
      lcd.print("hello, world!");
      // set the cursor to column 0, line 1
      // (note: line 1 is the second row, since counting begins with 0):
      lcd.setCursor(0, 1);
      int value = analogRead(potentiometer);
      // Serial.println(value);                      // pirnt the value on the serial monitor screen
      lcd.print(value);
      color=1.0*value/1024.0*256;
      lcd.setRGB(color, color, color);
      delay(100);
    }
}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
