#include "Geolocator.h"

#include <ESP8266WiFi.h>
#include <WiFiRestClient.h>

Geolocator::Geolocator(
    PubSubClient& client,
    int maxNetworks
  )
  : client( client ),
    maxNetworks( maxNetworks ),
    hasScanned( false ) {
}

void Geolocator::setup( const String& topic ) {
  this->topic = topic;
}

void Geolocator::loop() {

  if( !isSetup() ) {
    Serial.println( "ERROR: Geolocator not setup" );
    return;
  }

  if( hasScanned ) {
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
      hasScanned = true;
      break;
  }
}

bool Geolocator::publish( String ip, int8_t networks ) {

  if( networks > maxNetworks ) {
    networks = maxNetworks;
  }

  String body;
  body.reserve( 38 + networks * 51 );

  body += "{";

  if( ip.length() > 0 ) {
    body += "\"ip\":\"";
    body += ip;
    body += "\",";
  }

  body += "\"networks\":[";

  for( int8_t i = 0; i < networks; i++ ) {

    if( i > 0 ) {
      body += ",";
    }

    body += "{\"mac\":\"";
    body += WiFi.BSSIDstr( i );
    body += "\",\"channel\":";
    body += WiFi.channel( i );
    body += ",\"rssi\":";
    body += WiFi.RSSI( i );
    body += "}";
  }

  body += "]}";

  Serial.printf( "Publishing geolocation info to %s\n", topic.c_str() );
  Serial.println( body );

  bool published = client.publish( topic.c_str(), body.c_str() );
  if( !published  ) {
    Serial.println( "Failed to publish" );
  }
  return published;
}

String Geolocator::getPublicIpAddress() {

  if( publicIpAddress.length() == 0 ) {
    publicIpAddress = Geolocator::lookupPublicIpAddress();
  }

  return publicIpAddress;
}

String Geolocator::lookupPublicIpAddress() {

  WiFiRestClient restClient( "api.ipify.org" );

  String ipAddress;

  int statusCode = restClient.get( "/?format=text", &ipAddress );
  if( statusCode == 200 ) {

    ipAddress.trim();
    return ipAddress;

  } else {
    return "";
  }
}