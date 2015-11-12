#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "Arduino.h"
#include "GeolocationMessage.h"
#include "ESP8266WiFi.h"

using ::testing::StrEq;
using ::testing::Return;
using ::testing::Mock;
using ::testing::StrictMock;

struct GeolocationMessageFixture : ::testing::Test {

    StrictMock<MockESP8266WiFi> mockWifi;

    GeolocationMessageFixture() {
        mockESP8266WifiPtr = &mockWifi;
    }
    ~GeolocationMessageFixture() {
        mockESP8266WifiPtr = 0;
    }

    virtual void TearDown() {
        Mock::VerifyAndClearExpectations( &mockWifi );
    }
};

TEST_F( GeolocationMessageFixture, no_ip_and_no_networks ) {

    String ip;

    String ret = GeolocationMessage::format( ip, 0 );
    ASSERT_STREQ( "", ret.c_str() );
}

TEST_F( GeolocationMessageFixture, only_ip ) {

    String ip( "255.255.255.255" );

    String ret = GeolocationMessage::format( ip, 0 );
    ASSERT_STREQ( "ip: 255.255.255.255", ret.c_str() );
}

TEST_F( GeolocationMessageFixture, single_ip_and_single_network ) {

    String ip( "54.33.11.66" );

    uint8_t mac0[] = { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06 };
    EXPECT_CALL( mockWifi, BSSID( 0 ) ).WillOnce( Return( mac0 ) );
    EXPECT_CALL( mockWifi, channel( 0 ) ).WillOnce( Return( 1 ) );
    EXPECT_CALL( mockWifi, RSSI( 0 ) ).WillOnce( Return( -30 ) );

    String ret = GeolocationMessage::format( ip, 1 );
    ASSERT_STREQ( "ip: 54.33.11.66\nnetworks: 1 010203040506,1,-1e", ret.c_str() );
}

TEST_F( GeolocationMessageFixture, only_single_network ) {

    String ip;

    uint8_t mac0[] = { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06 };
    EXPECT_CALL( mockWifi, BSSID( 0 ) ).WillOnce( Return( mac0 ) );
    EXPECT_CALL( mockWifi, channel( 0 ) ).WillOnce( Return( 1 ) );
    EXPECT_CALL( mockWifi, RSSI( 0 ) ).WillOnce( Return( -30 ) );

    String ret = GeolocationMessage::format( ip, 1 );
    ASSERT_STREQ( "networks: 1 010203040506,1,-1e", ret.c_str() );
}

TEST_F( GeolocationMessageFixture, two_networks ) {

    String ip;

    uint8_t mac0[] = { 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF };
    EXPECT_CALL( mockWifi, BSSID( 0 ) ).WillOnce( Return( mac0 ) );
    EXPECT_CALL( mockWifi, channel( 0 ) ).WillOnce( Return( 1 ) );
    EXPECT_CALL( mockWifi, RSSI( 0 ) ).WillOnce( Return( -30 ) );

    uint8_t mac1[] = { 0xFB, 0x0A, 0xA1, 0xB4, 0x50, 0x75 };
    EXPECT_CALL( mockWifi, BSSID( 1 ) ).WillOnce( Return( mac1 ) );
    EXPECT_CALL( mockWifi, channel( 1 ) ).WillOnce( Return( 11 ) );
    EXPECT_CALL( mockWifi, RSSI( 1 ) ).WillOnce( Return( -60 ) );

    String ret = GeolocationMessage::format( ip, 2 );
    ASSERT_STREQ( "networks: 1 aabbccddeeff,1,-1e;fb0aa1b45075,b,-3c", ret.c_str() );
}
