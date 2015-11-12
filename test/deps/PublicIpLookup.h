#ifndef PublicIpLookup_h
#define PublicIpLookup_h

#include "Arduino.h"
#include <stdint.h>
#include <gmock/gmock.h>

struct MockPublicIpLookup {
  MOCK_METHOD1( lookupIpAddress, bool ( String& ) );
};

extern MockPublicIpLookup * mockPublicIpLookupPtr;

class PublicIpLookup {
public:

   static bool lookupIpAddress( String& ipAddress ) {

    if( !mockPublicIpLookupPtr ) {
      throw std::logic_error( "mockPublicIpLookupPtr not set" );
    }

    return mockPublicIpLookupPtr->lookupIpAddress( ipAddress );
  }
};

#endif // ESP_h
