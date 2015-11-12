#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "Arduino.h"
#include "PubSubClient.h"
#include "ESP8266WiFi.h"
#include "PublicIpLookup.h"
#include "GeolocationPublisher.h"

using ::testing::_;
using ::testing::AnyNumber;
using ::testing::Mock;
using ::testing::Return;
using ::testing::StrictMock;

struct GeolocatorPublisherFixture : ::testing::Test {

    StrictMock<MockESP8266WiFi> mockWifi;
    StrictMock<MockPublicIpLookup> mockPublicIpLookup;

    GeolocatorPublisherFixture() {
        mockESP8266WifiPtr = &mockWifi;
        mockPublicIpLookupPtr = &mockPublicIpLookup;
    }

    ~GeolocatorPublisherFixture() {
        mockESP8266WifiPtr = 0;
        mockPublicIpLookupPtr = 0;
    }

    virtual void TearDown() {
        Mock::VerifyAndClearExpectations( &mockWifi );
        Mock::VerifyAndClearExpectations( &mockPublicIpLookup );
    }
};

TEST_F( GeolocatorPublisherFixture, loop_when_not_setup ) {

    StrictMock<PubSubClient> client;

    GeolocationPublisher publisher( client );
    ASSERT_THROW( publisher.loop(), const char * );
}

TEST_F( GeolocatorPublisherFixture, loop_when_mqtt_not_connected ) {

    StrictMock<PubSubClient> client;
    EXPECT_CALL( client, connected() ).WillOnce( Return( false ) );

    GeolocationPublisher publisher( client );
    publisher.setup( "topic" );
    publisher.loop();
}

TEST_F( GeolocatorPublisherFixture, loop_when_not_scanning ) {

    StrictMock<PubSubClient> client;
    EXPECT_CALL( client, connected() ).WillOnce( Return( true ) );

    EXPECT_CALL( mockWifi, scanComplete() ).WillOnce( Return( -2 ) );
    EXPECT_CALL( mockWifi, scanNetworks( true ) ).WillOnce( Return( 0 ) );

    GeolocationPublisher publisher( client );
    publisher.setup( "topic" );
    publisher.loop();
}

TEST_F( GeolocatorPublisherFixture, loop_when_scan_incomplete ) {

    StrictMock<PubSubClient> client;
    EXPECT_CALL( client, connected() ).WillOnce( Return( true ) );

    EXPECT_CALL( mockWifi, scanComplete() ).WillOnce( Return( -1 ) );

    GeolocationPublisher publisher( client );
    publisher.setup( "topic" );
    publisher.loop();
}

TEST_F( GeolocatorPublisherFixture, loop_when_scan_complete ) {

    StrictMock<PubSubClient> client;
    EXPECT_CALL( client, connected() ).WillOnce( Return( true ) );
    EXPECT_CALL( client, publish( _, _ ) ).WillOnce( Return( true ) );

    EXPECT_CALL( mockWifi, scanComplete() ).WillOnce( Return( 0 ) );
    EXPECT_CALL( mockWifi, scanDelete() );

    EXPECT_CALL( mockPublicIpLookup, lookupIpAddress( _ ) ).WillOnce( Return( true ) );

    GeolocationPublisher publisher( client );
    publisher.setup( "topic" );
    publisher.loop();

    // force verification
    Mock::VerifyAndClearExpectations( &mockWifi );
    Mock::VerifyAndClearExpectations( &mockPublicIpLookup );

    // second call should do nothing
    publisher.loop();
}
