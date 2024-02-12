# dht11-firmware
# DHT11 Arduino Library

This is a library for interfacing with the DHT11 Temperature & Humidity Sensor on Arduino platforms.

## Features

- Read temperature and humidity data from the DHT11 sensor.
- Compatible with Arduino and other microcontroller platforms.

## Installation

1. Clone or download this repository.
2. Copy the `dht11` folder to the `libraries` directory in your Arduino sketchbook.
3. Restart the Arduino IDE if it's open.

## Usage

1. Include the `dht11.h` header file in your Arduino sketch.
2. Create a `dht11` object and call the `read()` method with the sensor pin as an argument.
3. Check the return value to determine if the reading was successful.
4. Access the `humidity` and `temperature` variables to get the sensor data.
