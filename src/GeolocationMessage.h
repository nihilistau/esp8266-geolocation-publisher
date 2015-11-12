#ifndef GeolocationMessage_h
#define GeolocationMessage_h

#include "Arduino.h"

class GeolocationMessage {
public:
  static String format( const String& ip, int8_t wifiNetworks );
private:
  static void appendMacAddress( uint8_t* macAddress, String& output );
};

#endif