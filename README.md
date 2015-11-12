# Geolocator

Tiny library for publishing geolocation related data over mqtt via PubSubClient.

## Usage

```c++
Geolocator geolocator( pubSubClient );

void setup() {
  ...
  heartbeat.setup("some/mqtt/topic");
  ...
}

void loop() {
  ...
  heartbeat.loop();
  ...
}
```

## Running Tests

```bash
./run-tests.sh
```
