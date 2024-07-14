#ifndef OUTPUTCOMPONENTS_H
#define OUTPUTCOMPONENTS_H

#include <Arduino.h>
#include "constants.h"


/* BASE CLASS */
class OutputComponent
{
public:
  int pin;
  int mode;
  OutputComponent(int _pin)
  {
    pin = _pin;
    mode = OUTPUT;
  }
  void setup()
  {
    if (pin < 2 || pin > 13)
    {
      Serial.println("pin " + String(pin) + " is not a valid pin");
      return;
    }
    pinMode(pin, mode);
    isReady = true;
  }
  void on()
  {
    if (!componentIsReady())
      return;
    digitalWrite(pin, HIGH);
  }
  void off()
  {
    if (!componentIsReady())
      return;
    digitalWrite(pin, LOW);
  }
  bool componentIsReady()
  {
    if (!isReady)
    {
      Serial.println("component on pin " + String(pin) + " is not ready");
      return false;
    }
    return true;
  }

private:
  bool isReady;
};


class PWMPinComponent : public OutputComponent
{
public:
  PWMPinComponent(int _pin) : OutputComponent(_pin) {}
  void setup()
  {
    if (!constants.isPWMPin(pin))
    {
      Serial.println("pin " + String(pin) + " is not a pwm pin");
      return;
    }
    OutputComponent::setup();
  }
};



/* CONCRETE CLASSES */


class Piezo : public PWMPinComponent
{
public:
  Piezo(int _pin) : PWMPinComponent(_pin) {}
  void playTone(int frequency, int duration)
  {
    tone(pin, frequency, duration);
  }
};

class LED {
  public:
    LED(int _pin) {
      this->__pin__ = _pin;
    }
    void blink(int millis) {
        digitalWrite(this->__pin__, HIGH);
        delay(millis);
        digitalWrite(this->__pin__, LOW);
        delay(millis);
    }
  private:
    int __pin__;
};

class DigitalLED : public OutputComponent, public LED
{
public:
  DigitalLED(int _pin) : OutputComponent(_pin), LED(_pin) {}
};


class AnalogLED : public PWMPinComponent, public LED
{
public:
  AnalogLED(int _pin) : PWMPinComponent(_pin), LED(_pin) {}

  void setBrightness(int brightness)
  {
    if (!PWMPinComponent::componentIsReady())
      return;
    analogWrite(PWMPinComponent::pin, brightness);
  }
};

class RGBLED
{
public:
  AnalogLED *redPin;
  AnalogLED *greenPin;
  AnalogLED *bluePin;
  RGBLED(int r, int g, int b)
  {
    redPin = new AnalogLED(r);
    greenPin = new AnalogLED(g);
    bluePin = new AnalogLED(b);
  }

  ~RGBLED()
  {
    delete redPin;
    delete greenPin;
    delete bluePin;
  }

  void setup()
  {
    redPin->setup();
    greenPin->setup();
    bluePin->setup();
  }

  void rgb(int r, int g, int b)
  {
    if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
    {
      Serial.println("rgb values must be between 0 and 255");
      return;
    }
    redPin->setBrightness(r);
    greenPin->setBrightness(g);
    bluePin->setBrightness(b);
  }

  void off()
  {
    redPin->off();
    greenPin->off();
    bluePin->off();
  }
};


#endif