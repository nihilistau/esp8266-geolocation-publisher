# Geolocator

Tiny library for publishing geolocation related data over mqtt via PubSubClient.

## Usage

```c++
Geolocator geolocator( pubSubClient );

void setup() {
  ...
  geolocator.setup("some/mqtt/topic");
  ...
}

void loop() {
  ...
  geolocator.loop();
  ...
}
```

## Running Tests

```bash
cd test
cmake . && make && make test
```
