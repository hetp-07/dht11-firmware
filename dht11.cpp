// AUTHOR: Het Patel (HETP-07)
// FILE: dht11.cpp
// VERSION: 1.0.0
// PURPOSE: DHT11 Temperature & Humidity Sensor library for Arduino

#include "dht11.h"

// Return values:
// DHTLIB_OK
// DHTLIB_ERROR_CHECKSUM
// DHTLIB_ERROR_TIMEOUT
int dht11::read(int pin)
{
    // BUFFER TO RECEIVE
    uint8_t data[5] = {0};
    uint8_t bitCount = 7;
    uint8_t byteIndex = 0;

    // REQUEST SAMPLE
    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW);
    delay(18);
    digitalWrite(pin, HIGH);
    delayMicroseconds(40);
    pinMode(pin, INPUT);

    // ACKNOWLEDGE or TIMEOUT
    unsigned int loopCount = 10000;
    while(digitalRead(pin) == LOW)
        if (loopCount-- == 0) return DHTLIB_ERROR_TIMEOUT;

    loopCount = 10000;
    while(digitalRead(pin) == HIGH)
        if (loopCount-- == 0) return DHTLIB_ERROR_TIMEOUT;

    // READ OUTPUT - 40 BITS => 5 BYTES or TIMEOUT
    for (int i = 0; i < 40; i++)
    {
        loopCount = 10000;
        while(digitalRead(pin) == LOW)
            if (loopCount-- == 0) return DHTLIB_ERROR_TIMEOUT;

        unsigned long startTime = micros();    // store a starting time of microcontroller 

        loopCount = 10000;
        while(digitalRead(pin) == HIGH)
            if (loopCount-- == 0) return DHTLIB_ERROR_TIMEOUT;

        if ((micros() - startTime) > 40) data[byteIndex] |= (1 << bitCount);
        if (bitCount == 0)   // next byte?
        {
            bitCount = 7;    // restart at MSB
            byteIndex++;      // next byte!
        }
        else bitCount--;
    }

    // WRITE TO RIGHT VARS
    humidity = data[0];
    temperature = data[2];

    // CALCULATE CHECKSUM
    uint8_t checksum = data[0] + data[1] + data[2] + data[3];
    
    // VERIFY CHECKSUM
    if (data[4] != checksum) return DHTLIB_ERROR_CHECKSUM;
    
    return DHTLIB_OK;
}
//
// END OF FILE
//
