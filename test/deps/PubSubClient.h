#ifndef PubSubClient_h
#define PubSubClient_h

struct PubSubClient {

  MOCK_METHOD0( connected, bool () );
  MOCK_METHOD2( publish, unsigned long ( const char *, const char * ) );
};

#endif // PubSubClient_h
