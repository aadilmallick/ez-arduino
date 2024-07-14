#ifndef SENSORS_H
#define SENSORS_H

#include <Arduino.h>
#include "constants.h"

class AnalogInputComponent
{
public:
  int pin;
  AnalogInputComponent(int _pin)
  {
    pin = _pin;
    if (!constants.isAnalogPin(pin))
    {
      Serial.println("pin " + String(pin) + " is not an analog pin");
      pin = -1;
    }
  }

  int getRawValue()
  {
    return analogRead(pin);
  }

  float getVoltage()
  {
    return analogRead(pin) * 5.0 / 1023;
  }

  int getMappedValue(int min, int max)
  {
    return map(getRawValue(), sensorMin, sensorMax, min, max);
  }

protected:
  int sensorMin = 0;
  int sensorMax = 1023;
};

class Photoresistor : public AnalogInputComponent
{
public:
  Photoresistor(int _pin) : AnalogInputComponent(_pin)
  {
    AnalogInputComponent::sensorMin = 13;
    AnalogInputComponent::sensorMax = 974;
  }
};

class TemperatureSensor : public AnalogInputComponent
{
public:
  TemperatureSensor(int _pin) : AnalogInputComponent(_pin)
  {
    AnalogInputComponent::sensorMin = 20;
    AnalogInputComponent::sensorMax = 358;
  }

  float getTemperature(bool isCelsius = true)
  {
    float voltage = getVoltage();
    float temp_c = (100 * voltage) - 50;
    return isCelsius ? temp_c : (temp_c * (9 / 5) + 32);
  }
};

class DistanceSensor
{
public:
  int pin;
  int trigger_pin_delay = 25; // delay in microseconds
  DistanceSensor(int _pin)
  {
    pin = _pin;
    if (pin < 2 || pin > 13)
    {
      Serial.println("pin " + String(pin) + " is not a valid pin");
      pin = -1;
    }
  }

  float getDistanceInCm()
  {
    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW); // ensure the trigger pin is low before
    delayMicroseconds(10);
    digitalWrite(pin, HIGH); // send a pulse
    delayMicroseconds(trigger_pin_delay);
    digitalWrite(pin, LOW); // ensure the trigger pin is low after

    pinMode(pin, INPUT); // now measure distance
    float duration = pulseIn(pin, HIGH);
    float cm = duration / 58.8;

    if (cm < 2 || cm > 320)
    { // invalid range, sensor only detects between 3 - 300cm
      return -1;
    }

    return cm;
  }
};

#endif