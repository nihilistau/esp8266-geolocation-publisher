#ifndef ArduinoString_h
#define ArduinoString_h

#include <string>       // std::string
#include <iostream>     // std::cout
#include <sstream>      // std::stringstream

#define HEX 16

class String : public std::string {
public:

    String() {
    }

    String( const char* str )
        : std::string( str ) {
    }

    String( long int value, int base ) {

        if( base == 16 ) {
            std::stringstream ss;

            if( value < 0 ) {
                ss << "-";
                value = value * -1;
            }

            ss << std::hex << value;
            this->append( ss.str() );

        } else {
            throw "Unsupported base";
        }
    }
};

#endif