#ifndef PINS_H
#define PINS_H

//*****************************//
//Pin Definitions
//*****************************//
    /*
      Depending on how you set up your electronics, you'll have to edit
      these to match your configuration.
     
      Refer to the photos inside ".../Duella/Reference" to make sure your
      settings match real life. Note that the outputs written on the PCB
      do not match the pin numbers of the Teensy 2.0
      
      Do NOT use pins 7 and 8 -- they are reserved for Rx and Tx. Attaching anything to them will prevent
      your Teensy from communicating with CWS.
    */


  
  
  #define IO_LED                       11
  #define Z_STEPPER_DIRECTION          0
  #define Z_STEPPER_STEP               1
  #define Z_STEPPER_SLEEP              2    //SLEEP is logic-inverted
  #define Z_STEPPER_RESET              3    //RESET is logic-inverted
  #define Z_STEPPER_DISABLE            4    //ENABLE is logic inverted, so we call it DISABLE for readability.
  
  #ifdef Z_PRINT_LEVEL_ENDSTOP 
    #define Z_PRINT_ENDSTOP_PIN        9
  #endif
  
  #ifdef SERVO_APERTURE
    #define IO_APERTURE_SERVO          10
  #endif
  
  #ifdef WIPER_AXIS_ENDSTOP 
    #define WIPER_AXIS_ENDSTOP_PIN          8
  #endif
  
  #ifdef Y_AXIS_ENDSTOP
    #define Y_AXIS_ENDSTOP_PIN         11   //We're running out of pins! This overlaps on the IO_LED
  #endif
  
  #ifdef WIPER_AXIS_STEPPER  //This is the X-Axis by definition.
    #define X_STEPPER_DIRECTION        21
    #define X_STEPPER_STEP             20
    #define X_STEPPER_SLEEP            19   //SLEEP is logic-inverted
    #define X_STEPPER_RESET            18   //RESET is logic-inverted
    #define X_STEPPER_DISABLE          17   //ENABLE is logic inverted, so we call it DISABLE for readability.
  #endif
  
  #ifdef Y_AXIS_STEPPER  //This is the yet unused Y axis by definition.
    #define Y_STEPPER_DIRECTION        16
    #define Y_STEPPER_STEP             15
    #define Y_STEPPER_SLEEP            14   //SLEEP is logic-inverted
    #define Y_STEPPER_RESET            13   //RESET is logic-inverted
    #define Y_STEPPER_DISABLE          12   //ENABLE is logic inverted, so we call it DISABLE for readability.
  #endif

#endif  //PINS_H
