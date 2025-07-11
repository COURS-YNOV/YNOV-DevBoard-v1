#ifndef LED_HPP
#define LED_HPP

#include <Arduino.h>

class LED {
public:
    LED(uint8_t pin);
    void LED_on();
    void LED_off();
    void LED_toggle();
    void LED_blink(unsigned int delay_ms = 500);
    void LED_launchTest();
    bool LED_getState();

private:
    uint8_t _pin;
    bool _state;
};

#endif