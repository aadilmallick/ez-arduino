#ifndef CONSTANTS_H
#define CONSTANTS_H

struct Constants
{
  int digitalPins[12] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
  int non_pwm_pins[5] = {2, 4, 7, 12, 13};
  int pwm_pins[6] = {3, 5, 6, 9, 10, 11};
  int analog_pins[6] = {A0, A1, A2, A3, A4, A5};
  struct arrayLengths
  {
    int pwm_pin_length = 6;
    int digital_pin_length = 12;
    int non_pwm_pin_length = 5;
    int analog_pin_length = 6;
  };

  Constants::arrayLengths arrayLengths;

public:
  static bool containsInt(int arr[], int size, int value)
  {
    for (int i = 0; i < size; i++)
    {
      if (arr[i] == value)
      {
        return true;
      }
    }
    return false;
  }

  bool isPWMPin(int pin)
  {
    return containsInt(pwm_pins, arrayLengths.pwm_pin_length, pin);
  }

  bool isDigitalPin(int pin)
  {
    return containsInt(digitalPins, arrayLengths.digital_pin_length, pin);
  }

  bool isNonPWMPin(int pin)
  {
    return containsInt(non_pwm_pins, arrayLengths.non_pwm_pin_length, pin);
  }

  bool isAnalogPin(int pin)
  {
    return containsInt(analog_pins, arrayLengths.analog_pin_length, pin);
  }
};

Constants constants;

#endif