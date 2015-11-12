#include "GeolocationPublisher.h"

#include <ESP8266WiFi.h>
#include <PublicIpLookup.h>
#include "GeolocationMessage.h"

GeolocationPublisher::GeolocationPublisher(
    PubSubClient& client,
    int maxNetworks
  )
  : client( client ),
    maxNetworks( maxNetworks ),
    hasPublished( false ) {
}

void GeolocationPublisher::setup( const String& topic ) {
  this->topic = topic;
}

void GeolocationPublisher::loop() {

  if( hasPublished ) {
    return;
  }

  if( !isSetup() ) {
    Serial.println( "ERROR: GeolocationPublisher not setup" );
    return;
  }

  if( !client.connected() ) {
    return;
  }

  int8_t networks = WiFi.scanComplete();
  switch( networks ) {

    case -1: // not finished
      break;
      
    case -2: // not triggered
      Serial.println( "Scanning for wifi networks" );
      WiFi.scanNetworks( true );
      break;

    default:

      String ip = getPublicIpAddress();
      publish( ip, networks );

      // clean up
      WiFi.scanDelete();
      hasPublished = true;
      break;
  }
}

bool GeolocationPublisher::publish( String ip, int8_t networks ) {

  if( networks > maxNetworks ) {
    networks = maxNetworks;
  }

  String body = GeolocationMessage::format( ip, networks );

  Serial.print( "Publishing geolocation info to " );
  Serial.println( topic );
  Serial.println( body );

  bool published = client.publish( topic.c_str(), body.c_str() );
  if( !published  ) {
    Serial.println( "Failed to publish" );
  }
  return published;
}

String GeolocationPublisher::getPublicIpAddress() {

  if( publicIpAddress.length() == 0 ) {
    PublicIpLookup::lookupIpAddress( publicIpAddress );
  }

  return publicIpAddress;
}
