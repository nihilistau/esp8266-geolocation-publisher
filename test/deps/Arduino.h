#ifndef Arduino_h
#define Arduino_h

#include <stdint.h>
#include <stdlib.h>
#include <string>
#include <gmock/gmock.h>
#include <stdexcept>

#include "ArduinoString.h"

struct MockSerial {

  MOCK_METHOD1( print, void( const char * ) );
  MOCK_METHOD1( print, void( const String& ) );

  MOCK_METHOD1( println, void( const char * ) );
  MOCK_METHOD1( println, void( const String& ) );
};
extern MockSerial Serial;


#endif // Arduino_h
