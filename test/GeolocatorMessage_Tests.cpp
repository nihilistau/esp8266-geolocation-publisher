#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "Arduino.h"
#include "GeolocatorMessage.h"
#include "ESP8266WiFi.h"

using ::testing::_;
using ::testing::StrEq;
using ::testing::Return;
using ::testing::AnyNumber;
using ::testing::NiceMock;

struct GeolocatorMessageFixture : ::testing::Test {

    NiceMock<MockESP8266WiFi> mockWifi;

    GeolocatorMessageFixture() {
        mockESP8266WifiPtr = &mockWifi;
    }
    ~GeolocatorMessageFixture() {
        mockESP8266WifiPtr = 0;
    }
};

TEST_F( GeolocatorMessageFixture, no_ip_and_no_networks ) {

}