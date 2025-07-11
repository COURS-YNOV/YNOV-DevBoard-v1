#include "led.hpp"

LED::LED(uint8_t pin) : _pin(pin), _state(false) {
    pinMode(_pin, OUTPUT);
    digitalWrite(_pin, LOW);
}

void LED::LED_on() {
    _state = true;
    digitalWrite(_pin, HIGH);
}

void LED::LED_off() {
    _state = false;
    digitalWrite(_pin, LOW);
}

void LED::LED_toggle() {
    _state = !_state;
    digitalWrite(_pin, _state ? HIGH : LOW);
}

void LED::LED_blink(unsigned int delay_ms) {
    LED_toggle();
    delay(delay_ms);
}

void LED::LED_launchTest() {
    Serial.println("------------ LED ------------");
    Serial.println("Blink 10 times ...");

    for(int i = 0; i < 10; i++) {
        LED_blink(100);
    }
    LED_off();

    Serial.println("------------------------------");
}

bool LED::LED_getState() {
    return _state;
}