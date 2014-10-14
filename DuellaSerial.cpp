#include "DuellaSerial.h"

  DuellaSerial::DuellaSerial()
  {
	
  }
  
  void DuellaSerial::begin( void )
  {
    Serial.begin(BAUDRATE);
      firstSerialPing_ = true;
  }
  
  void DuellaSerial::giveMotionControl( MotionController motionControl )
  {
    motionControl_ = motionControl; 
  }  

  
  void DuellaSerial::read( void )
  {
    //If the Uncia is completely unmodified, CWS will send commands as
    //single chars to give instructions.
    #ifdef STOCK_UNCIA
      readSerialForUncia();
    #endif
    
    //If the Uncia is modified in any way, we might as well just use normal
    //GCode.
    #ifndef STOCK_UNCIA
      readSerialForGcode();
    #endif
  }
  
    
  void DuellaSerial::readSerialForGcode( void )
  {
    while(Serial.available() > 0)
    {
      char c = Serial.read();
      sBuffer_ += c;
      
      if(c == '\n' || c == '\r')
      {
        motionControl_.pushCurrentCommandForGcode( sBuffer_ );
        resetBuffer();
        sendReadyCommand();
        
      }
    }
  }
  
  void DuellaSerial::readSerialForUncia( void )
  {
    if (Serial.available() > 0)
    {
      int Byte = Serial.read();
      motionControl_.pushCurrentCommandForStockUncia(Byte);
    } 
  }
  
  
  void DuellaSerial::CreationWorkshopSerialPing( void )
  {
    if (firstSerialPing_)
    {
      while(Serial.available() > 0) {
        //The very first thing that Pomeroy's fork of CWS does on connect
        //is ping the Uncia with 'P'. Knowing this, we don't have to check
        //what the char that we first received is, but we do have to purge
        //it from the serial buffer
        char ping = Serial.read();
        #ifdef STOCK_UNCIA
        Serial.write('Sedgwick3D');
        #endif
        
        #ifndef STOCK_UNCIA
        Serial.write('N'); //'N' for Not-Stock
        #endif 
        firstSerialPing_ = false;
      }
    }
  }  
  
  
  void DuellaSerial::resetBuffer( void )
  {
    sBuffer_ = "";
  }

  
  void DuellaSerial::sendReadyCommand( void )
  {
    Serial.print(F("\n\rok\n\r>")); 
  }
