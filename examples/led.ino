#include "EzArduino.h"

// 1. establish led on pin 8
DigitalLED led(8);

void setup()
{
  // * sidenote: important to have serial on to see any error messages
  Serial.begin(115200);

  // 2. sets up pinMode with led
  led.setup();
}

void loop()
{
  delay(1000);
  Console::print("hello world", 2, 2.4);
}
