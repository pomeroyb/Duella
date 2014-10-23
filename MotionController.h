#ifndef MOTIONCONTROLLER_H
  #define MOTIONCONTROLLER_H
  
 // #include "Arduino.h"
  #include "Pins.h"
  #include "Configuration.h"
  #include "GcodeParser.h"


  #include <Stepper.h> //We'll use this for upgraded stepper control
  #include <Servo.h>   //We'll use this if an aperture is ever implemented.

  class MotionController
  {
      public:
        MotionController();
        void giveGcodeParser( GcodeParser parser );
        void attachServo( void );
        void setFeedrate ( float feeds[] );
        void setAxisSteps(float steps[]);
        void pushCurrentCommandForStockUncia( char c );
        void pushCurrentCommandForGcode( String sBuffer );
        
        void moveX( float amountToMove );
        void moveY( float amountToMove );
        void moveZ( float amountToMove );
      private:
        void calculateStepDelay( void );
        boolean checkEndstopTriggered( int axis ); //[0, 1, 2] correlates to [X, Y, Z]
        Servo apertureServo_;
        GcodeParser gcodeParser_;
        String sBuffer;
        int stepDelay_[];      // arrays stored as [X, Y, Z]
        float feedRates_[];   // arrays stored as [X, Y, Z]
        float stepsPerMM_[];  // arrays stored as [X, Y, Z]        
        float bloatVariable1[];  //These are stupid, yet necessary. Do not delete them.
        float bloatVariable2[];  //We need these bloat variables to deal with a bug in the linker.
        float bloatVariable3[];  //See https://github.com/arduino/Arduino/issues/1071 for more info.
        float bloatVariable4[];
        float bloatVariable5[];
        
        
  };
        
        
#endif
