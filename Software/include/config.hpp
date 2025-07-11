#ifndef CONFIG_HPP
#define CONFIG_HPP

// Serial monitor speed
#define SERIAL_MONITOR_SPEED_115K 115200

// INA
#define INA237_ADDR 0x40

// TMP126
#define TMP126_REG_TEMP_RESULT   0x00
#define TMP126_RESOLUTION        0.03125f

// NTC
#define PIN_NTC1 26
#define PIN_NTC2 25

// SPI
#define PIN_SPI_MOSI 23
#define PIN_SPI_MISO 19
#define PIN_SPI_SCK  18
#define PIN_TMP126_CS 5

// I2C
#define PIN_I2C_SDA 21
#define PIN_I2C_SCL 22

// BUZZER
#define PIN_BUZZER 13

// LED
#define PIN_LED_RED 15
#define PIN_LED_GREEN 14

// BLE
#define WRITE_CHARACTERISTIC "2A19"
#define NOTIFY_CHARACTERISTIC "2A20"

#endif // CONFIG_HPP
