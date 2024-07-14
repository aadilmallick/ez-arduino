#ifndef INPUTCOMPONENTS_H
#define INPUTCOMPONENTS_H

#include <Arduino.h>
#include "constants.h"


class InputComponent
{
public:
  int pin;
  int mode;
  bool isPullup;
  InputComponent(int _pin, bool _isPullup = false)
  {
    pin = _pin;
    isPullup = _isPullup;
    if (isPullup)
    {
      mode = INPUT_PULLUP;
    }
    else
    {
      mode = INPUT;
    }
  }

  void setup()
  {
    if (pin < 2 || pin > 13)
    {
      Serial.println("pin " + String(pin) + " is not a valid pin");
      return;
    }
    pinMode(pin, mode);
  }

  bool isTurnedOn()
  {
    return getTurnedOnStateForMode(digitalRead(pin));
  }

private:
  bool getTurnedOnStateForMode(int state)
  {
    if (mode == INPUT_PULLUP)
    {
      return state == LOW;
    }
    return state == HIGH;
  }
};

class Button : public InputComponent
{
public:
  Button(int _pin, bool _isPullup = false) : InputComponent(_pin, _isPullup)
  {
    if (InputComponent::isPullup)
    {
      prev_btn_state = HIGH;
      current_btn_state = HIGH;
    }
    else
    {
      prev_btn_state = LOW;
      current_btn_state = LOW;
    }
  }

  bool buttonStateChanged()
  {
    int state = digitalRead(pin);

    // press or release the button -> record timestamp of button state change
    if (state != prev_btn_state)
    {
      lastDebounceTime = millis();
    }

    // if 50ms have passed since last button state change, update the button state
    if (millis() > (lastDebounceTime + debounceDelay))
    {
      if (state != current_btn_state)
      {
        current_btn_state = state;
        return true;
      }
    }

    prev_btn_state = state;
    return false;
  }

private:
  int debounceDelay = 50;
  int current_btn_state;
  int prev_btn_state;
  unsigned long lastDebounceTime = 0;
};


#endif