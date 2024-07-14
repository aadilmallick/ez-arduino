# EZ Arduino

A library that makes interacting with basic Arduino Components as simple as possible.

Here is how to use it:

```cpp
#include <EzArduino.h>

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
  // 3. makes the led blink at 500ms interval
  led.blink(500);
}
```

## Installation

### Git install

1. Download any libraries using the arduino IDE, like the `Servo` library. This should create a `/home/Arduino/Libraries` folder.
2. cd into the libraries folder and clone this repository. You may have to rename the folder to `EzArduino`. The library is now installed locally.
3. Import the library with `#include <EzArduino.h>`

### Manual install

1. Download any libraries using the arduino IDE, like the `Servo` library. This should create a `/home/Arduino/Libraries` folder.
2. Download the ZIP release, unzip it, place it in the libraries folder, and rename the folder to `EzArduino`. The library is now installed locally.
3. Import the library with `#include <EzArduino.h>`

## Documentation
