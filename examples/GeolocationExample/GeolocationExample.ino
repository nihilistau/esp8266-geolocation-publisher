/*
 * Publishes the information necessary to get geolocation using google services on startup.
 *
 * Make sure to update wifi ssid & password
 *
 * Depends on libraries:
 *
 *   https://github.com/CanTireInnovations/esp8266-arduino-rest-client
 *   https://github.com/CanTireInnovations/esp8266-geolocation-publisher
 *   https://github.com/CanTireInnovations/esp8266-publicip-lookup
*/

#include <GeolocationPublisher.h>
#include <PublicIpLookup.h>
#include <PubSubClient.h>
#include <ESP8266WiFi.h>
#include <WiFiRestClient.h>

WiFiClient wifiClient;

PubSubClient mqttClient(
  "test.mosquitto.org",
  1883,
  wifiClient
);

GeolocationPublisher geolocator( mqttClient );

void setup() {

  WiFi.mode( WIFI_STA );
  WiFi.begin( "ssid", "password" );
  
  Serial.begin( 115200 );
  geolocator.setup( "geolocationInfo" );
}

void loop() {

  if( !mqttClient.connected() ) {
    mqttReconnect();
  }
  
  geolocator.loop();
}

void mqttReconnect() {
  
  while( !mqttClient.connected() ) {
    
    Serial.print( "Attempting MQTT connection..." );
    
    if( mqttClient.connect( "esp8266-geolocator" ) ) {
      Serial.println("connected");
      
    } else {

      Serial.print( "failed, rc=" );
      Serial.print( mqttClient.state() );
      Serial.println( " try again in 5 seconds" );
      delay( 5000 );
    }
  }
}

