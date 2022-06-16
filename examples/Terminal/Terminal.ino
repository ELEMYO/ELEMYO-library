//  Reads an analog input on pin A0, prints the result to the Serial Monitor.
//  The sensor gain is controlled by the program.
//  Graphical representation is available using Elemyo_GUI, Python_GUI and Matlab_GUI.
//  2018-04-18 by ELEMYO (https://github.com/ELEMYO/Elemyo-library)
//
// Changelog:
//    2018-04-18 - initial release
//    2020-06-15 - loop time sending added

/* ============================================
ELEMYO library code is placed under the MIT license
Copyright (c) 2018 ELEMYO

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
===============================================


Wiring the ELEMYO sensor to an Arduino

ELEMYO -->  Arduino
  +        5V
  -        GND
  S        analog pin A0 (or other analog input)
  СS       pin 10 (SS pin)
  MOSI     pin 11 (UNO, Nano, Mini), pin 51 (Mega), pin SI (Leonardo), pin 16 (Pro micro)
  SCK      pin 13 (UNO, Nano, Mini), pin 52 (Mega), pin SCK (Leonardo), pin 15 (Pro micro)

*/

#include <ELEMYO.h>

#define   CSpin         10
#define   sensorInPin   A0      // analog input pin that the sensor is attached to
#define   timePeriod    0.7     // frequency of signal update (time in ms).

int sensorValue = 0;            // value read from the sensor
long loopTime=0, sendTime=0;    // values for calculating and sending a time period of one loop

ELEMYO MyoSensor(CSpin);

void setup() {
  // initialize serial communications at 115200 bps:
  Serial.begin(115200);
  // Initial value of gain
  MyoSensor.gain(x1);
  // initialize sensorInPin
  pinMode(sensorInPin, INPUT);
}

void loop() {
  // read the analog in value:
  sensorValue = analogRead(sensorInPin);

  // print the results to the Serial Monitor:
  Serial.println(sensorValue);

  // check for byte in buffer
  if (Serial.available() > 0) {
    // Read gain value from serial buffer
    int gainValue = Serial.read(); 
    
    // Set the gain in the sensor
    switch(gainValue) { 
      case 1:
        MyoSensor.gain(x1);
        break;
      case 2:
        MyoSensor.gain(x2);
        break;
      case 4:
        MyoSensor.gain(x4);
        break;
      case 5:
        MyoSensor.gain(x5);
        break;
      case 8:
        MyoSensor.gain(x8);
        break;
      case 10:
        MyoSensor.gain(x10);
        break;
      case 16:
        MyoSensor.gain(x16);
        break;
      case 32:
        MyoSensor.gain(x32);
        break;
    }
  }

  if ((micros() - sendTime > 10000) && (micros() < 100000))
  {
    sendTime = micros();
    Serial.print("T");
    Serial.println(sendTime - loopTime);
  }
  loopTime = micros();
  
  // wait before the next loop
  delayMicroseconds(timePeriod*1000);
}
