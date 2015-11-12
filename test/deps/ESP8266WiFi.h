#ifndef WiFi_h
#define WiFi_h

#include <stdint.h>
#include <gmock/gmock.h>

struct MockESP8266WiFi {

  MOCK_METHOD1( scanNetworks, int8_t ( bool ) );
  MOCK_METHOD0( scanComplete, int8_t () );
  MOCK_METHOD0( scanDelete, void () );

  MOCK_METHOD1( BSSID, uint8_t* ( uint8_t ) );
  MOCK_METHOD1( RSSI, int32_t ( uint8_t ) );
  MOCK_METHOD1( channel, int32_t ( uint8_t ) );
};

extern MockESP8266WiFi * mockESP8266WifiPtr;

class ESP8266WiFiClass {
public:

  int8_t scanComplete() {

    if( !mockESP8266WifiPtr ) {
      throw std::logic_error("mockESP8266WifiPtr not set");
    }

    return mockESP8266WifiPtr->scanComplete();
  }

  void scanDelete() {

    if( !mockESP8266WifiPtr ) {
      throw std::logic_error("mockESP8266WifiPtr not set");
    }

    mockESP8266WifiPtr->scanDelete();
  }

  int8_t scanNetworks( bool async = false ) {

    if( !mockESP8266WifiPtr ) {
      throw std::logic_error("mockESP8266WifiPtr not set");
    }

    return mockESP8266WifiPtr->scanNetworks( async );
  }

  uint8_t* BSSID( uint8_t networkItem ) {

    if( !mockESP8266WifiPtr ) {
      throw std::logic_error("mockESP8266WifiPtr not set");
    }

    return mockESP8266WifiPtr->BSSID( networkItem );
  }

  int32_t channel( uint8_t networkItem ) {

    if( !mockESP8266WifiPtr ) {
      throw std::logic_error("mockESP8266WifiPtr not set");
    }

    return mockESP8266WifiPtr->channel( networkItem );
  }

  int32_t RSSI( uint8_t networkItem ) {

    if( !mockESP8266WifiPtr ) {
      throw std::logic_error("mockESP8266WifiPtr not set");
    }

    return mockESP8266WifiPtr->RSSI( networkItem );
  }
};

extern ESP8266WiFiClass WiFi;

#endif // ESP_h
