#include "MotionController.h"
#include "Arduino.h"

  MotionController::MotionController()
  {
    //We need these bloat variables to deal with a bug in the linker.
    //See https://github.com/arduino/Arduino/issues/1071 for more info.
    //
    for (int i = 0; i < 5; i++)
    {
      bloatVariable1[i] = i;
      bloatVariable2[i] = i;
      bloatVariable3[i] = i;
      bloatVariable4[i] = i;
      bloatVariable5[i] = i;  
    }
    
  }
  
  //This attaches our servo to the correct pin
  void MotionController::attachServo( void )
  {
    #ifdef IO_APERTURE_SERVO
       apertureServo_.attach(IO_APERTURE_SERVO); 
       apertureServo_.write(ApertureClose); //Close aperture
    #endif
  }
  
  void MotionController::setFeedrate( float feeds[] )
  {
    //We know that we only have max 3 feedrates.

    feedRates_[0] = feeds[0];
    feedRates_[1] = feeds[1];
    feedRates_[2] = feeds[2];
  }
  
  void MotionController::calculateStepDelay( void )
  {
    long stepsPerSecond[3];
    for (int i = 0; i < 3; i++)
    {
       stepsPerSecond[i]  = (long) (stepsPerMM_[i] * feedRates_[i]);
       stepDelay_[i] = (int) (1000/stepsPerSecond[i]);
    }
  }
  

  //This takes a char that was grabbed from DuellaSerial, and peforms actions
  //depending on the char. This is essentially the Uncia's stock firmware.
  void MotionController::pushCurrentCommandForStockUncia( char c )
    {
      char Byte = c;
         switch(Byte)
           {
            case 'E': //Enable Stepper Motor
              digitalWrite(Z_STEPPER_DISABLE, 0);
              Serial.write('e');
              break;
            case 'D': //Disable Stepper Motor
              digitalWrite(Z_STEPPER_DISABLE, 1);
              Serial.write('d');
              break;
            case 'F': //Change Direction to forward, or away from the projector (1)
              digitalWrite(Z_STEPPER_DIRECTION, 1);
              Serial.write('f');
              break;
            case 'R': //Change Direction to Reverse, or towards the projector (0)
              digitalWrite(Z_STEPPER_DIRECTION, 0);
              Serial.write('r');
              break;
            case 'S': //Step the Stepper Motor
              digitalWrite( Z_STEPPER_STEP, 1);
              delay(1);
              digitalWrite( Z_STEPPER_STEP, 0);
              Serial.write('s');
              break;
            case 'P': //Ping Teensy 2.0
              #ifdef STOCK_UNCIA
              Serial.write('Sedgwick3D');
              #endif
              
              #ifndef STOCK_UNCIA
              Serial.write('N'); //'N' for Not-Stock
              #endif
              break;
            case 'O':
              apertureServo_.write(ApertureOpen); //Open Aperture
              Serial.write('O');
              break;
            case 'C':
              apertureServo_.write(ApertureClose); //Close Aperture
              Serial.write('C');
              break;
            default:
              break;
          }
    }
    
    void MotionController::pushCurrentCommandForGcode( String sBuffer )
    {
      String* parsedLine = gcodeParser_.parseLine(sBuffer);
      int numberOfCommands = parsedLine[0].toInt(); //As set in our parseLine method
      int commandCount = 0;
      //String* parsedLineWithoutCount = parsedLine.substring(1);
      String** commandArray = gcodeParser_.parseCommands(parsedLine);
      for (int i = 1; i < numberOfCommands; i++) //We start at 1 since the 0 pos is the number of commands.
      {
        String* fullCommand = commandArray[i];
        String commandLetterString = fullCommand[0];
        commandCount++; //We're going to increase our counter to make sure we don't read the same command twice.
        char commandLetter = commandLetterString.charAt(0);
        String commandValueString = fullCommand[1];
        float commandValue = float(gcodeParser_.stringToFloat(commandValueString));
        // We now have both the letter and the value of the command! Time to move!
        
        switch(commandLetter)
        {
          case 'G':
            //If it's a G command, commandValue must be an int:
              int commandValueInt = int(commandValue);
              switch(commandValueInt)
              {
                case 1: //G1, simple move
                  //We know that the next three commands could possibly be X, Y, or Z.
                  if (commandCount < numberOfCommands)
                  {// So we don't try to grab a null
                    String* nextCommand = commandArray[i+1];
                    char nextCommandLetter = nextCommand[0].charAt(0);
                    float nextCommandValue = float(gcodeParser_.stringToFloat(nextCommand[1]));
                    
                    if (nextCommandLetter == 'X' || nextCommandLetter == 'Y' || nextCommandLetter == 'Z')
                    {
                      switch(nextCommandLetter)
                      {
                        case 'X':
                          moveX( nextCommandValue );
                          break;
                        case 'Y':
                          moveX( nextCommandValue );
                          break;
                        case 'Z':
                          moveZ( nextCommandValue );
                          break;
                      }
                      commandCount++;
                      i++; //We want to increase our counter to make sure that we don't check this twice.
                      
                      if(commandCount < (numberOfCommands - 1))
                      { //Again, don't want to grab a null!
                        String* nextNextCommand = commandArray[i+2];
                        char nextNextCommandLetter = nextNextCommand[0].charAt(0);
                        float nextNextCommandValue = float(gcodeParser_.stringToFloat(nextNextCommand[1]));
                    
                        if (nextNextCommandLetter == 'X' || nextNextCommandLetter == 'Y' || nextNextCommandLetter == 'Z')
                        {
                          switch(nextNextCommandLetter)
                          {
                            case 'X':
                              moveX( nextNextCommandValue );
                              break;
                            case 'Y':
                              moveX( nextNextCommandValue );
                              break;
                            case 'Z':
                              moveZ( nextNextCommandValue );
                              break;
                          }
                          commandCount++;
                          i++; //We want to increase our counter to make sure that we don't check this twice.
                          
                          if(commandCount < (numberOfCommands - 2))
                          { //Again, don't want to grab a null!
                            String* nextNextNextCommand = commandArray[i+3];  /// This is getting ridiculous...
                            char nextNextNextCommandLetter = nextNextNextCommand[0].charAt(0);
                            float nextNextNextCommandValue = float(gcodeParser_.stringToFloat(nextNextNextCommand[1]));
                        
                            if (nextNextNextCommandLetter == 'X' || nextNextNextCommandLetter == 'Y' || nextNextNextCommandLetter == 'Z')
                            {
                              switch(nextNextNextCommandLetter)
                              {
                                case 'X':
                                  moveX( nextNextNextCommandValue );
                                  break;
                                case 'Y':
                                  moveX( nextNextNextCommandValue );
                                  break;
                                case 'Z':
                                  moveZ( nextNextNextCommandValue );
                                  break;
                              }
                              commandCount++;
                              i++; //We want to increase our counter to make sure that we don't check this twice.
                              //We know that it will be, at most, "G1 X_ Y_ Z_", so we can stop at 3 iterations. Thank god that this silliness is done.
                            }
                          }
                        }
                      }
                    }
                    

                    
                  }
                  
                  break;
                case 4: //G4, dwell. 
                  //TODO
                  break;
                case 28: // home the printer.
                  //TODO
                  break;
                case 5:
                  //TODO
                  break;
                
              }
            break;
        }
        
      }
      
    }
    
    void MotionController::setAxisSteps(float steps[])
    {
      stepsPerMM_[0] = steps[0];
      stepsPerMM_[1] = steps[1];
      stepsPerMM_[2] = steps[2];
    }
    
    void MotionController::giveGcodeParser( GcodeParser parse ) 
    {
      gcodeParser_ = parse;
    }
    
  
    void MotionController::moveX( float amountToMove )
    {
      #ifdef WIPER_AXIS_STEPPER
        //amountToMove is given in mm
        if (amountToMove > 0) //we want to move in the negative direction
        {
          digitalWrite(X_STEPPER_DIRECTION, 0);
        }
        float stepsToTake = amountToMove * stepsPerMM_[0];
        stepsToTake = abs(stepsToTake);
        
        for (int i = 0; i < stepsToTake; i++)
        {
          if(!checkEndstopTriggered(0) )
          {
            digitalWrite( X_STEPPER_STEP, 1);
            delayMicroseconds(500);
            digitalWrite( X_STEPPER_STEP, 0);
            if (stepDelay_[0] <= 500)
            {
              delayMicroseconds(500);
            }else{
               delayMicroseconds( stepDelay_[0] - 500 );
            }
          }
        }
       
      #endif
    }

    
     void MotionController::moveY( float amountToMove )
    {
      #ifdef Y_AXIS_STEPPER
        //amountToMove is given in mm
        if (amountToMove > 0) //we want to move in the negative direction
        {
          digitalWrite(Y_STEPPER_DIRECTION, 0);
        }
        float stepsToTake = amountToMove * stepsPerMM_[1];
        stepsToTake = abs(stepsToTake);
        
        for (int i = 0; i < stepsToTake; i++)
        {
          if(!checkEndstopTriggered(1) )
          {
            digitalWrite( Y_STEPPER_STEP, 1);
            delayMicroseconds(500);
            digitalWrite( Y_STEPPER_STEP, 0);
            if (stepDelay_[1] <= 500)
            {
              delayMicroseconds(500);
            }else{
               delayMicroseconds( stepDelay_[1] - 500 );
            }
          }
          
        }
      #endif
    }
    
     void MotionController::moveZ( float amountToMove )
    {
      //amountToMove is given in mm
      if (amountToMove > 0) //we want to move in the negative direction
      {
        digitalWrite(Z_STEPPER_DIRECTION, 0);
      }
      float stepsToTake = amountToMove * stepsPerMM_[2];
      stepsToTake = abs(stepsToTake);
      
      for (int i = 0; i < stepsToTake; i++)
      {
        if(!checkEndstopTriggered(2) )
        {
          digitalWrite(Z_STEPPER_STEP, 1);
          delayMicroseconds(500);
          digitalWrite(Z_STEPPER_STEP, 0);
          if (stepDelay_[2] <= 500)
          {
            delayMicroseconds(500);
          }else{
             delayMicroseconds( stepDelay_[2] - 500 );
          }
        }
      }
    }
    
    boolean MotionController::checkEndstopTriggered( int axis )
    {
      #ifdef Z_PRINT_LEVEL_ENDSTOP
        if (axis == 2)
        {
          if( Z_MIN_ENDSTOP_INVERTING )
          {
            return !digitalRead(Z_PRINT_ENDSTOP_PIN);
          }else {
            return digitalRead(Z_PRINT_ENDSTOP_PIN);
          }
        }
      #endif
      
      #ifdef Y_AXIS_ENDSTOP
        if (axis == 1)
        {
          if( Y_MIN_ENDSTOP_INVERTING )
          {
            return !digitalRead(Y_AXIS_ENDSTOP_PIN);
          }else {
            return digitalRead(Y_AXIS_ENDSTOP_PIN);
          }
        }
      #endif
      
      #ifdef WIPER_AXIS_ENDSTOP
        if (axis == 0)
        {
          if( Z_MIN_ENDSTOP_INVERTING )
          {
            return !digitalRead(WIPER_AXIS_ENDSTOP_PIN);
          }else {
            return digitalRead(WIPER_AXIS_ENDSTOP_PIN);
          }
        }
      #endif
      
      return false;
    }

