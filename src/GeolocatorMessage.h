#ifndef GeolocatorMessage_h
#define GeolocatorMessage_h

#include "Arduino.h"

class GeolocatorMessage {
public:
  static String format( const String& ip, int8_t wifiNetworks );
private:
  static void appendMacAddress( uint8_t* macAddress, String& output );
};

#endif