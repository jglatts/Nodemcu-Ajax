#include "Arduino.h"
#include "NPNControls.h"

NPN::NPN(int pin) {
    pinMode(pin, OUTPUT);
    _pin = pin;
}

void NPN::turnOnNPN() {
    digitalWrite(_pin, HIGH);
}

void NPN::turnOffNPN() {
    digitalWrite(_pin, LOW);
}
