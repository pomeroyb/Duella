/*

Uncia firmware, partially based on Sedgwick firmware.
Allows for stock printers to connect to the eUNCIA driver in Creation Workshop,
and also allows for modified printers to function. This firmware will automatically
tell the eUNCIA driver if it is stock or modified, and the eUNCIA driver will send
commands accordingly.

****All normal user changes should be limited to "Configuration.h" and "Pins.h"****

The MIT License (MIT)

Copyright (c) 2014 Brandon Pomeroy

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
*/



//*****************************//
//Includes
//*****************************//
 // #include "Arduino.h"
  #include <Stepper.h> //We'll use this for upgraded stepper control
  #include <Servo.h>   //We'll use this if an aperture is ever implemented.

  
  //Firmware Configuration
  #include "Configuration.h"
  
  //Pin Definitions
  #include "Pins.h"
  
  //Control classes
  #include "MotionController.h"
  #include "DuellaSerial.h"
  #include "GcodeParser.h"

//*****************************//
//Global Variables
//*****************************//


MotionController motionControl;
DuellaSerial duellaSerial;
GcodeParser gcodeParser;


//*****************************//
//Public Variables
//*****************************//

float stepsPerMM[] = STEPS_PER_MM;
float defaultFeedrate[] = DEFAULT_FEEDRATE;
float homingFeedrate[] = HOMING_FEEDRATE;





void setup()
{
  
//*****************************//
//Setting the pin modes
//*****************************//
  pinMode(IO_LED, OUTPUT);
  
  //Z Motor Pins
  pinMode(Z_STEPPER_DISABLE, OUTPUT);
  pinMode(Z_STEPPER_STEP, OUTPUT);
  pinMode(Z_STEPPER_DIRECTION, OUTPUT);
  pinMode(Z_STEPPER_SLEEP, OUTPUT);
  pinMode(Z_STEPPER_RESET, OUTPUT);
  
  //X Motor Pins
  #ifdef WIPER_AXIS_STEPPER
    pinMode(X_STEPPER_DISABLE, OUTPUT);
    pinMode(X_STEPPER_STEP, OUTPUT);
    pinMode(X_STEPPER_DIRECTION, OUTPUT);
    pinMode(X_STEPPER_SLEEP, OUTPUT);
    pinMode(X_STEPPER_RESET, OUTPUT);
  #endif
  
  //Y motor Pins
  #ifdef Y_AXIS_STEPPER
    pinMode(Y_STEPPER_DISABLE, OUTPUT);
    pinMode(Y_STEPPER_STEP, OUTPUT);
    pinMode(Y_STEPPER_DIRECTION, OUTPUT);
    pinMode(Y_STEPPER_SLEEP, OUTPUT);
    pinMode(Y_STEPPER_RESET, OUTPUT);
  #endif
  
  #ifdef Z_PRINT_LEVEL_ENDSTOP
    pinMode(Z_PRINT_ENDSTOP_PIN, INPUT_PULLUP);
    delayMicroseconds(10);
  #endif
  
  #ifdef Y_AXIS_ENDSTOP
    pinMode(Y_AXIS_ENDSTOP_PIN, INPUT_PULLUP);
    delayMicroseconds(10);
  #endif
  
  #ifdef WIPER_AXIS_ENDSTOP
    pinMode(WIPER_AXIS_ENDSTOP_PIN, INPUT_PULLUP);
    delayMicroseconds(10);
  #endif
  

//*****************************//
//Setting each pin to its respective I/O state
//*****************************//
  digitalWrite(IO_LED, 1);  //Power on the Teensy status LED
  
  digitalWrite(Z_STEPPER_DISABLE, 1); //Keep stepper disabled when we first start up
  digitalWrite(Z_STEPPER_STEP, 0);
  digitalWrite(Z_STEPPER_DIRECTION, 0);
  digitalWrite(Z_STEPPER_SLEEP, 1);  //The SLEEP and RESET pins are logic-inverted. 
  digitalWrite(Z_STEPPER_RESET, 1);  //Keeping these pins HIGH does the opposite of what they say.
  
  #ifdef WIPER_AXIS_STEPPER
    digitalWrite(X_STEPPER_DISABLE, 1); //Keep stepper disabled when we first start up
    digitalWrite(X_STEPPER_STEP, 0);
    digitalWrite(X_STEPPER_DIRECTION, 0);
    digitalWrite(X_STEPPER_SLEEP, 1);  //The SLEEP and RESET pins are logic-inverted. 
    digitalWrite(X_STEPPER_RESET, 1);  //Keeping these pins HIGH does the opposite of what they say.
  #endif
  
  #ifdef Y_AXIS_STEPPER
    digitalWrite(Y_STEPPER_DISABLE, 1); //Keep stepper disabled when we first start up
    digitalWrite(Y_STEPPER_STEP, 0);
    digitalWrite(Y_STEPPER_DIRECTION, 0);
    digitalWrite(Y_STEPPER_SLEEP, 1);  //The SLEEP and RESET pins are logic-inverted. 
    digitalWrite(Y_STEPPER_RESET, 1);  //Keeping these pins HIGH does the opposite of what they say.
  #endif

//*****************************//
//Setting up MotionController
//*****************************//  
  #ifdef IO_APERTURE_SERVO
    motionControl.attachServo();  
  #endif
  motionControl.giveGcodeParser( gcodeParser );
  motionControl.setFeedrate(defaultFeedrate);
  motionControl.setAxisSteps(stepsPerMM);
  
//*****************************//
//Setting up DuellaSerial
//*****************************//
  duellaSerial.begin();
  duellaSerial.giveMotionControl(motionControl);


}

void loop()
{
  duellaSerial.CreationWorkshopSerialPing();
  duellaSerial.read();
}











