#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "Arduino.h"
#include "PubSubClient.h"
#include "ESP8266WiFi.h"
#include "GeolocationPublisher.h"

using ::testing::Return;
using ::testing::AnyNumber;
using ::testing::Mock;
using ::testing::StrictMock;

struct GeolocatorPublisherFixture : ::testing::Test {

    StrictMock<MockESP8266WiFi> mockWifi;

    GeolocatorPublisherFixture() {
        mockESP8266WifiPtr = &mockWifi;
    }

    ~GeolocatorPublisherFixture() {
        mockESP8266WifiPtr = 0;
    }

    virtual void TearDown() {
        Mock::VerifyAndClearExpectations( &mockWifi );
    }
};

TEST_F( GeolocatorPublisherFixture, loop_when_not_setup ) {

    StrictMock<PubSubClient> client;

    GeolocationPublisher publisher( client, 5 );

}