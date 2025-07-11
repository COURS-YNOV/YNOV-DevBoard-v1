#include <Arduino.h>
#include <unity.h>
#include "led.hpp"

LED* led;

void test_led_on() {
    led->LED_on();
    TEST_ASSERT_TRUE(led->LED_getState());
}

void test_led_off() {
    led->LED_off();
    TEST_ASSERT_FALSE(led->LED_getState());
}

void test_led_builtin_output_1() {
    led->LED_on();
    TEST_ASSERT_EQUAL(HIGH, digitalRead(15));
}

void test_led_builtin_output_2() {
    led->LED_on();
    TEST_ASSERT_NOT_EQUAL(LOW, digitalRead(15));
}

void setup() {
    led = new LED(15);
    UNITY_BEGIN();
    RUN_TEST(test_led_builtin_output_1);
    RUN_TEST(test_led_builtin_output_2);
    RUN_TEST(test_led_on);
    RUN_TEST(test_led_off);
    UNITY_END();
}

void loop() {
    // vide
}