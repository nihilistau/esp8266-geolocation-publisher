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

    String( long int value, int base ) {

        if( base == 16 ) {

            std::stringstream ss;
            ss << std::hex << value;
            this->append( ss.str() );

        } else {
            throw "Unsupported base";
        }
    }
};

#endif