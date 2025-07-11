#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#define LOG_FILE "/log.txt"
#define BLE_DEVICE_NAME "ESP32-BLE-YNOV"

enum class CommandType {
    BUZZER,
    LED_R,
    LED_G,
    CTN,
    I2C,
    INA,
    TEMP,
    R_LOG,
    W_LOG,
    UNKNOWN
};

enum LogType {
  LOG_INFO,
  LOG_WARNING,
  LOG_ERROR,
  LOG_DEBUG,
  LOG_FATAL
};

#endif // CONSTANTS_HPP
