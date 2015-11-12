#include "Geolocator.h"

#include <ESP8266WiFi.h>
#include <PublicIpLookup.h>
#include "GeolocatorMessage.h"

Geolocator::Geolocator(
    PubSubClient& client,
    int maxNetworks
  )
  : client( client ),
    maxNetworks( maxNetworks ),
    hasPublished( false ) {
}

void Geolocator::setup( const String& topic ) {
  this->topic = topic;
}

void Geolocator::loop() {

  if( hasPublished ) {
    return;
  }

  if( !isSetup() ) {
    Serial.println( "ERROR: Geolocator not setup" );
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

bool Geolocator::publish( String ip, int8_t networks ) {

  if( networks > maxNetworks ) {
    networks = maxNetworks;
  }

  String body = GeolocatorMessage::format( ip, networks );

  Serial.print( "Publishing geolocation info to " );
  Serial.println( topic );
  Serial.println( body );

  bool published = client.publish( topic.c_str(), body.c_str() );
  if( !published  ) {
    Serial.println( "Failed to publish" );
  }
  return published;
}

String Geolocator::getPublicIpAddress() {

  if( publicIpAddress.length() == 0 ) {
    PublicIpLookup::lookupIpAddress( publicIpAddress );
  }

  return publicIpAddress;
}
