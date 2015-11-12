#ifndef Geolocator_h
#define Geolocator_h

#include "Arduino.h"
#include <PubSubClient.h>

class Geolocator {
public:

  Geolocator( PubSubClient& client, int maxNetworks = 10 );
  void setup( const String& topic );
  void loop();

private:
  PubSubClient& client;
  String topic;
  const int maxNetworks;
  
  bool isSetup() const {
      return topic.length() > 0;
  }

  bool hasScanned;

  bool publish( String ip, int8_t networks );
  static void appendMacAddress( uint8_t* macAddress, String& output );

  String publicIpAddress;
  String getPublicIpAddress();
};

#endif