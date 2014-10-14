#ifndef CONFIGURATION_H
#define CONFIGURATION_H


/***********************************/
//FIRMWARE DEFINES AND CONFIGURATION
/***********************************/
/////The following defines select the configuration of your Uncia.
#define STOCK_UNCIA //Keep this uncommented if you have no hardware/electronics mods to Uncia.

//This determines the speed at which the printer communicates with the computer.
//Standard speeds: 300, 1200, 2400, 4800, 9600, 14400, 19200, 28800, 38400, 57600, 115200, 250000
//Creation Workshop operates at 115200.
const int BAUDRATE = 115200;


//==================================HARDWARE CONFIGURATIONS==================================
#ifndef STOCK_UNCIA
  /*
    Comment and uncomment the following according to your setup.
    If something here is uncommented, this firmware assumes that you
    have that feature on your bot. This could affect you in various
    ways, from being unable to connect to Creation Workshop, to
    breaking your bot. WHEN IN DOUBT, LEAVE IT COMMENTED.
  */
  
  //#define Z_PRINT_LEVEL_ENDSTOP   //A limit switch on your Z axis to set your initial print height
    
  //#define WIPER_AXIS_STEPPER      //Stepper motor to drive a wiper across the print surface. This is defined as the X Axis.
  //#define WIPER_AXIS_ENDSTOP      //A limit switch on your wiper axis to let your wiper find its home
  
  //#define SERVO_APERTURE          //A servo powered aperture for covering the lens during layer changes
  
#endif


//==================================Z-MOTOR CONFIGURATIONS==================================
////Defining the how many steps the motor needs to take to move a mm
////The benefits of a standardized hardware system:
////The Uncia has an MXL belt on 18 tooth pulleys, with a 1.8 degree per step motor.
////The calulated steps per mm:
//
//--------------------------------------------------------
//Stock Uncia Motor:                     87.5752599890531
//Upgraded 5.2:1 Geared Stepper Motor:   455.3913519430761
//Upgraded 5.0:1 Geared Stepper Motor:   437.8762999452655
//--------------------------------------------------------
//
////Choose your motor, and put the calculated value here:.

#define STEPS_PER_MM      {50.0, 0.0, 87.5752599890531}

#define DEFAULT_FEEDRATE {200, 300, 100}      // Axis order is X, Y, Z
                                              // X is the Wiper Axis, Y is as yet undefined, Z is the Z-Axis.
#define HOMING_FEEDRATE {300, 300, 300}       // Y could be a resin pump, or something.


//==================================ENDSTOP CONFIGURATIONS==================================
//
// An endstop that is wired NC -> GND will need these set to false.
// An endstop that is wired NO -> GND will need these set to true.
//const bool X_MIN_ENDSTOP_INVERTING = false; 
//const bool Y_MIN_ENDSTOP_INVERTING = false; 
//const bool Z_MIN_ENDSTOP_INVERTING = false; 


//==================================SERVO CONFIGURATIONS==================================
//
//You need to adjust this for your specific servo
//These are the degrees that the will be sent to the servo when it opens and closes
const int ApertureOpen = 90;
const int ApertureClose = 180;



#endif //__CONFIGURATION_H
