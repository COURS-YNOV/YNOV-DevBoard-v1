#include "buzzer.hpp"

BUZZER::BUZZER(uint8_t pin) : _pin(pin) {
    pinMode(_pin, OUTPUT);
    digitalWrite(_pin, LOW);

    _channel = 0;
    _resolution = 8;
    _frequency = 2000;

    ledcSetup(_channel, _frequency, _resolution);
    ledcAttachPin(_pin, _channel);
}

void BUZZER::BUZZER_beep(unsigned int frequency, unsigned int duration) {
    ledcWriteTone(_channel, frequency);
    ledcWrite(_channel, 128); // 50% duty cycle
    delay(duration);
    BUZZER_stop();
}

void BUZZER::BUZZER_stop() {
    ledcWriteTone(_channel, 0); // stop tone
    ledcWrite(_channel, 0); // 0% duty
}

uint8_t BUZZER::BUZZER_getPin() {
    return _pin;
}

void BUZZER::BUZZER_launchTest() {
    Serial.println("------------ BUZZER ------------");

    BUZZER_beep(4300, 1000);

    Serial.println("--------------------------------");
}