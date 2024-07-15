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

This library is officially apart of the Arduino library manager. Just download it directly from the IDE! But you also have these two options if you prefer to do manual installation:

### Git install

1. Download any libraries using the arduino IDE, like the `Servo` library. This should create a `/home/Arduino/Libraries` folder.
2. cd into the libraries folder and clone this repository. You may have to rename the folder to `EzArduino`. The library is now installed locally.
3. Import the library with `#include <EzArduino.h>`

### Manual install

1. Download any libraries using the arduino IDE, like the `Servo` library. This should create a `/home/Arduino/Libraries` folder.
2. Download the ZIP release, unzip it, place it in the libraries folder, and rename the folder to `EzArduino`. The library is now installed locally.
3. Import the library with `#include <EzArduino.h>`

## Documentation

## Output components

This includes stuff like LEDs, piezos, etc.

### OutputComponent

Base class for all output components.

#### Public Members

- `int pin`: The pin number assigned to the component.
- `int mode`: The mode of the pin (default is `OUTPUT`).

#### Constructor

- `OutputComponent(int _pin)`: Initializes the component with the specified pin.

#### Public Methods

- `void setup()`: Configures the pin as an output. Validates if the pin is between 2 and 13.
- `void on()`: Sets the pin to HIGH.
- `void off()`: Sets the pin to LOW.
- `bool componentIsReady()`: Checks if the component is ready for operation.

### PWMPinComponent

Derived from `OutputComponent`. Represents a PWM-capable pin.

#### Constructor

- `PWMPinComponent(int _pin)`: Initializes the component with the specified pin.

#### Public Methods

- `void setup()`: Configures the pin as a PWM output if it is a valid PWM pin.

### Piezo

Derived from `PWMPinComponent`. Represents a piezo buzzer.

#### Constructor

- `Piezo(int _pin)`: Initializes the piezo with the specified pin.

#### Public Methods

- `void playTone(int frequency, int duration)`: Plays a tone at the specified frequency and duration.

### LED

Basic class representing an LED with blink functionality.

#### Constructor

- `LED(int _pin)`: Initializes the LED with the specified pin.

#### Public Methods

- `void blink(int millis)`: Blinks the LED with the specified delay.

### DigitalLED

Derived from `OutputComponent` and `LED`. Represents a digital LED.

#### Constructor

- `DigitalLED(int _pin)`: Initializes the digital LED with the specified pin.

### AnalogLED

Derived from `PWMPinComponent` and `LED`. Represents an analog (PWM-controlled) LED.

#### Constructor

- `AnalogLED(int _pin)`: Initializes the analog LED with the specified pin.

#### Public Methods

- `void setBrightness(int brightness)`: Sets the brightness of the LED using PWM.

### RGBLED

Represents an RGB LED controlled by three PWM pins.

#### Public Members

- `AnalogLED *redPin`: Pointer to the red LED pin.
- `AnalogLED *greenPin`: Pointer to the green LED pin.
- `AnalogLED *bluePin`: Pointer to the blue LED pin.

#### Constructor

- `RGBLED(int r, int g, int b)`: Initializes the RGB LED with the specified pins for red, green, and blue.

#### Public Methods

- `void setup()`: Configures the RGB LED pins as outputs.
- `void rgb(int r, int g, int b)`: Sets the RGB LED to the specified color. Validates the RGB values (0-255).
- `void off()`: Turns off all the RGB LED pins.

### Usage Example

```cpp
#include "OutputComponents.h"

void setup() {
  Serial.begin(9600);

  // Initialize a digital LED on pin 8
  DigitalLED myLED(8);
  myLED.setup();
  myLED.on();
  delay(1000);
  myLED.off();

  // Initialize an RGB LED on pins 9, 10, and 11
  RGBLED myRGBLED(9, 10, 11);
  myRGBLED.setup();
  myRGBLED.rgb(255, 0, 0); // Set to red
  delay(1000);
  myRGBLED.off();
}

void loop() {
  // Main loop
}
```

## Input Components

Stuff like buttons

### InputComponent

Base class for all input components.

#### Public Members

- `int pin`: The pin number assigned to the component.
- `int mode`: The mode of the pin (`INPUT` or `INPUT_PULLUP`).
- `bool isPullup`: Indicates if the pin is configured with a pull-up resistor.

#### Constructor

- `InputComponent(int _pin, bool _isPullup = false)`: Initializes the component with the specified pin and optional pull-up resistor.

#### Public Methods

- `void setup()`: Configures the pin as an input. Validates if the pin is between 2 and 13.
- `bool isTurnedOn()`: Checks if the input component is in the "on" state, taking into account the pin mode.

### Button

Derived from `InputComponent`. Represents a button with debouncing functionality.

#### Public Members

- `int debounceDelay`: The delay in milliseconds to debounce the button (default is 50 ms).

#### Constructor

- `Button(int _pin, bool _isPullup = false)`: Initializes the button with the specified pin and optional pull-up resistor.

#### Public Methods

- `bool buttonStateChanged()`: Checks if the button state has changed, implementing debouncing.

## Usage Example

```cpp
#include "InputComponents.h"

// Initialize a button on pin 7 with pull-up resistor
Button myButton(7, true);

void setup() {
  Serial.begin(9600);

  // setup pinMode with button
  myButton.setup();
}

void loop() {

  // Check if the button state has changed
  if (myButton.buttonStateChanged()) {
    if (myButton.isTurnedOn()) {
      Serial.println("Button pressed");
    } else {
      Serial.println("Button released");
    }
  }
}
```

## Sensors

Potentiometers, temp sensor, motion sensor, photoresistors, etc.

### AnalogInputComponent

Base class for all analog input components.

#### Public Members

- `int pin`: The pin number assigned to the component.

#### Constructor

- `AnalogInputComponent(int _pin)`: Initializes the component with the specified pin and validates if it is an analog pin.

#### Public Methods

- `int getRawValue()`: Reads the raw analog value from the pin.
- `float getVoltage()`: Converts the raw analog value to a voltage.
- `int getMappedValue(int min, int max)`: Maps the raw analog value to a specified range.

#### Protected Members

- `int sensorMin`: Minimum sensor value (default is 0).
- `int sensorMax`: Maximum sensor value (default is 1023).

### Photoresistor

Derived from `AnalogInputComponent`. Represents a photoresistor (light sensor).
gets back the data that lives at the

- `TemperatureSensor(int _pin)`: Initializes the temperature sensor with the specified pin and sets specific sensor range values.

#### Public Methods

- `float getTemperature(bool isCelsius = true)`: Reads the temperature in Celsius (default) or Fahrenheit.

### DistanceSensor

Represents a distance sensor using a trigger pin for ultrasonic measurement.

#### Public Members

- `int pin`: The pin number assigned to the component.
- `int trigger_pin_delay`: The delay in microseconds for the trigger pin (default is 25).

#### Constructor

- `DistanceSensor(int _pin)`: Initializes the distance sensor with the specified pin and validates if it is a valid pin.

#### Public Methods

- `float getDistanceInCm()`: Measures the distance in centimeters. Returns `-1` if the distance is out of range (2 - 320 cm).

## Usage Example

```cpp
#include "Sensors.h"

// Initialize a photoresistor on pin A0
Photoresistor myPhotoresistor(A0);

// Initialize a temperature sensor on pin A1
TemperatureSensor myTemperatureSensor(A1);

// Initialize a distance sensor on pin 7
DistanceSensor myDistanceSensor(7);

void setup() {
  Serial.begin(9600);
}

void loop() {
  // Read and print the photoresistor value
  int lightLevel = myPhotoresistor.getRawValue();
  Serial.print("Light level: ");
  Serial.println(lightLevel);

  // Read and print the temperature value
  float temperature = myTemperatureSensor.getTemperature();
  Serial.print("Temperature: ");
  Serial.println(temperature);

  // Read and print the distance value
  float distance = myDistanceSensor.getDistanceInCm();
  Serial.print("Distance: ");
  Serial.println(distance);

  delay(1000);
}
```
