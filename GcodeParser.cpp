#include "GcodeParser.h"

#include <stdlib.h>
  GcodeParser::GcodeParser()
  {
    
  }
  
  //This method expects pure Gcode -- no comments or anything like that. CWS strips those out... so we're good.
  String* GcodeParser::parseLine( String sBuffer )
  {
     String ret[256];  //Maximum line length is 256 chars
     int commandCount = 0;
     String temporaryCommand;
     String subString;
     String gcodeLine = sBuffer;
     gcodeLine.trim();  //Trim any leading and trailing whitespaces
     
     temporaryCommand += gcodeLine[0]; //We know that the beginning of the line will be a letter
     subString = gcodeLine.substring(1);
     for (int i = 0; i < subString.length(); i++)
     {
       String c = subString[i];
       if ( c == "0" || c == "1" || c == "2" || c == "3" || c == "4" || c == "5" || 
             c == "6" || c == "7" || c == "8" || c == "9" || c == "." || c == "-")
       { //We are still hearing parts of the command... add them to the temporaryCommand
         temporaryCommand += c;
       }  else if (c == " ")
          {
            //We hit a space, just ignore it.
          } else {
             //We hit a letter, which means we should save this command.
             ret[commandCount + 1] = temporaryCommand; //We reserve the 0 position of the returned array for the command
                   //count.
             //increase the command count
             commandCount++;
             //Now we clear the temporaryCommand, and add our new letter to it.
             temporaryCommand = "";
             temporaryCommand += c;
           }
     }           
     ret[0] = commandCount; //adding the total number of commands to the array, at the 0 position.
     return ret;
  }
  
  
  
  String** GcodeParser::parseCommands( String* commands )
  { //This method takes an array of strings that represents commands, and returns an array of commands
      //the commands are formatted as [LETTER, VALUE], such as ["G", "1"], or ["Z", "10"] or ["X", "10.5"]
    
    int commandCount = commands[0].toInt(); //As set in our parseLine method
    String* ret[commandCount];
    int finalCommandCount = 0;
    
    for ( int i = 0; i < commandCount; i++)
    {
      String tempCommand[2];
      String gcode = commands[i];
      String letter = gcode[0];
      String numbers = gcode.substring(1);
      tempCommand[0] = letter; //The letter command
      tempCommand[1] = numbers; //The numeric value
      
      ret[finalCommandCount] = tempCommand;
      finalCommandCount++;
     }
    return ret;
  }
  
  float GcodeParser::stringToFloat( String value)
  {
     char floatBuf[32]; //32 significant figures should be enough for anyone.
     value.toCharArray(floatBuf, sizeof(floatBuf));
     float f = strtod(floatBuf, NULL); //using strtod because strtof doesn't work, but Arduino views doubles and floats as the same.
     return f;
  }
