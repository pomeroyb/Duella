#ifndef DUELLASERIAL_H
  #define DUELLASERIAL_H

 // #include "Arduino.h"
  #include "Configuration.h"
  #include "MotionController.h"  
  
  class DuellaSerial
    {
    public:
      DuellaSerial();
      void begin( void );
      void read( void );
      void readSerialForGcode( void );
      void readSerialForUncia( void );
      void CreationWorkshopSerialPing( void );
      void resetBuffer( void );
      void sendReadyCommand( void );
      void giveMotionControl( MotionController motionControl );      
    private:
      bool firstSerialPing_;
      bool firstSerialChar_;
      String sBuffer_;
      MotionController motionControl_;
    };
	
#endif
