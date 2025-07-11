#ifndef BUZZER_HPP
#define BUZZER_HPP

#include <Arduino.h>
#include "config.h"

class BUZZER {
public:
    BUZZER(uint8_t pin);
    void BUZZER_beep(unsigned int frequency = 2000, unsigned int duration = 200);
    void BUZZER_stop();
    void BUZZER_launchTest();
    uint8_t BUZZER_getPin();

private:
    uint8_t _pin;
    uint8_t _channel;
    uint8_t _resolution;
    uint16_t _frequency;
};

#endif