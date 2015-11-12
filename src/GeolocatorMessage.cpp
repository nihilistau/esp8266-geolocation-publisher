#include "GeolocatorMessage.h"
#include <ESP8266WiFi.h>

#define GEOLOCATION_NETWORKS_FORMAT_VERSION 1

String GeolocatorMessage::format( const String& ip, int8_t networks ) {

  int bodyLength = 0;

  if( ip.length() > 0 ) {
    bodyLength += 5 + ip.length();
  }

  if( networks > 0 ) {

    bodyLength += (
      10    // networks:
      + 1   // version
    );

    bodyLength += networks * (
      1     // separator
      + 12  // mac
      + 1   // ,
      + 1   // channel
      + 1   // ,
      + 3   // rssi
    );
  }

  // ------------------------------------------------

  String body;
  body.reserve( bodyLength );

  if( ip.length() > 0 ) {
    body += "ip: ";
    body += ip;
  }

  if( networks > 0 ) {

    if( body.length() > 0 ) {
      body += "\n";
    }

    body += "networks: ";
    body += String( GEOLOCATION_NETWORKS_FORMAT_VERSION, HEX );

    char separator = ' ';
    for( int8_t i = 0; i < networks; i++ ) {

      body += separator;
      uint8_t* mac = WiFi.BSSID( i );
      GeolocatorMessage::appendMacAddress( mac, body );

      body += ",";
      body += String( WiFi.channel( i ), HEX );

      body += ",";
      body += String( WiFi.RSSI( i ), HEX );

      separator = ';';
    }
  }

#if GEOLOCATION_PUBLISHER_TEST
  if( body.length() > bodyLength ) {
    throw "Geolocation body under provisioned";
  }
#endif

  return body;
}

void GeolocatorMessage::appendMacAddress( uint8_t* macAddress, String& output ) {

  for( int i = 0; i < 6; i++ ) {

    String part( macAddress[ i ], HEX );

    if( part.length() == 1 ) {
      output += "0";
    }
    output += part;
  }
}
