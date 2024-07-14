#ifndef UTILS_H
#define UTILS_H

#include <Arduino.h>

class Console {
  public:
    static void begin(unsigned long rate = 115200) {
        Serial.begin(rate);
    }

    template<typename T, typename... Args>
    static void print(T first, Args... args) {
        Serial.print(asString(first));
        Serial.print(" ");
        print(args...);
    }


  private:
    // Base case for the variadic template recursion
    static void print() {
        Serial.println();
    }
    template<typename T>
    static String asString(T value) {
        return String(value);
    }

    static String asString(const char* value) {
        return String(value);
    }

    static String asString(const String& value) {
        return value;
    }
};

#endif