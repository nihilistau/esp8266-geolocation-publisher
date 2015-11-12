#ifndef Geolocator_h
#define Geolocator_h

#include <PubSubClient.h>

class Geolocator {
public:

  Geolocator( PubSubClient& client, int maxNetworks = 3 );
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

  String publicIpAddress;
  String getPublicIpAddress();
  static String lookupPublicIpAddress();
};

#endif