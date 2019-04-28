#include "Arduino.h"

class NPN {
    public:
        NPN(int pin);
        void turnOnNPN();
        void turnOffNPN();

    private:
        int _pin;
};