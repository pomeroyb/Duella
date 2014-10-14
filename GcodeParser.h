#ifndef GCODEPARSER_H
  #define GCODEPARSER_H
  

  //#include "Arduino.h"
    #include <stdlib.h>
  class GcodeParser
  {
    public:
      GcodeParser();
      String* parseLine( String sBuffer );
      String** parseCommands( String* commands);
      float stringToFloat( String value );
     private:

    
  };

#endif
