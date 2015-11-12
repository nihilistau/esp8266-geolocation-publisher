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
  const int maxNetworks;
  String topic;
  
  bool isSetup() const {
      return topic.length() > 0;
  }

  bool hasPublished;
  bool publish( String ip, int8_t networks );

  String publicIpAddress;
  String getPublicIpAddress();
};

#endif