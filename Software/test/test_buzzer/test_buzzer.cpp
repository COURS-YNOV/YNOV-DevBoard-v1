#include <Arduino.h>
#include <unity.h>
#include "buzzer.hpp"

BUZZER* buzzer;

void test_buzzer_on() {
    buzzer->BUZZER_beep(2000);
    TEST_ASSERT_EQUAL(HIGH, digitalRead(15));
}

void test_buzzer_off() {
    buzzer->BUZZER_stop();
    TEST_ASSERT_EQUAL(LOW, digitalRead(15));
}

void setup() {
    buzzer = new BUZZER(13);
    UNITY_BEGIN();
    RUN_TEST(test_buzzer_on);
    RUN_TEST(test_buzzer_off);
    UNITY_END();
}

void loop() {
    // vide
}