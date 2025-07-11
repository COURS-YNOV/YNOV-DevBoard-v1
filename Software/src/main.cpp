#include <Arduino.h>
#include "config.hpp"
#include "constants.hpp"
#include "led.hpp"
#include "buzzer.hpp"
#include "ina237.hpp"
#include "tmp126.hpp"
#include "ntc_board.hpp"
#include "i2cScanner.hpp"
#include "SPIFFS.h"
#include "FS.h"
#include "ble.hpp"

LED* _ledGreen;
LED* _ledRed;
BUZZER* _buzzer;
NTC_Board* _ntc1;
NTC_Board* _ntc2;
TMP126 _tmpsensor(PIN_TMP126_CS);
INA237 _ina237(INA237_ADDR);
I2C_SCANNER i2cScanner;
BLE* _ble;

// functions
bool initialize();
String getTimestamp();
CommandType stringToCommand(String cmd);
const char* logTypeToString(LogType type);
bool writeLogSPIFFS(LogType logType, String message);
bool readLogSPIFFS(void);

class ServerCallbacks : public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) override {
        Serial.println("✅ Client connecté");
    }

    void onDisconnect(BLEServer* pServer) override {
        Serial.println("🔌 Client déconnecté, redémarrage de l'advertising");
        BLEDevice::startAdvertising();
    }
};

class BLECallbacks : public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic *pCharacteristic) override {
        String value = pCharacteristic->getValue().c_str();
        Serial.print("Received BLE data: ");
        Serial.println(value);

        switch (stringToCommand(value)) {
            case CommandType::BUZZER:
                if (_buzzer) _buzzer->BUZZER_launchTest();
                _ble->BLE_sendAck(value);
                break;

            case CommandType::LED_R:
                if (_ledRed) _ledRed->LED_launchTest();
                _ble->BLE_sendAck(value);
                break;

            case CommandType::LED_G:
                if (_ledGreen) _ledGreen->LED_launchTest();
                _ble->BLE_sendAck(value);
                break;

            case CommandType::CTN:
                if (_ntc1) _ble->BLE_sendAck(String(_ntc1->NTC_launchTest()));
                if (_ntc2) _ble->BLE_sendAck(String(_ntc2->NTC_launchTest()));
                break;

            case CommandType::I2C:
                _ble->BLE_sendAck(i2cScanner.I2C_SCANNER_launchTest());
                break;

            case CommandType::INA:
                _ina237.INA237_launchTest();
                break;

            case CommandType::TEMP:
                _ble->BLE_sendAck(String(_tmpsensor.TMP126_launchTest()));
                break;

            case CommandType::R_LOG:
                if (!readLogSPIFFS()) {
                    Serial.println("❌ Error during test for R_LOG");
                }
                break;

            case CommandType::W_LOG:
                if (!writeLogSPIFFS(LOG_INFO, "Log from BLE !")) {
                    Serial.println("❌ Error during test for W_LOG");
                }
                break;

            case CommandType::UNKNOWN:
            default:
                Serial.println("❓ Unknown BLE command");
                break;
        }
    }
};

void setup() {
    if(initialize()) {
        Serial.println("Initialize done !");
    } else {
        Serial.println("❌ Error during intialize !");
    }
}

void loop() {   
}

// Init
bool initialize() {
    Serial.begin(SERIAL_MONITOR_SPEED_115K);
    Serial.println("Initialize ...");

    if (!SPIFFS.begin(true)) {
        Serial.println("❌ [initialize] SPIFFS Error !");
        return false;
    } else {
        Serial.println("[initialize] SPIFFS : ✅");
    }

    _ledGreen = new LED(PIN_LED_GREEN);
    _ledRed = new LED(PIN_LED_RED);
    Serial.println("[initialize] LEDs   : ✅");

    _buzzer = new BUZZER(PIN_BUZZER);
    Serial.println("[initialize] Buzzer : ✅");

    _tmpsensor.TMP126_begin();
    Serial.println("[initialize] NTC1   : ✅");

    _ntc1 = new NTC_Board(PIN_NTC1);
    Serial.println("[initialize] NTC1   : ✅");

    _ntc2 = new NTC_Board(PIN_NTC2);
    Serial.println("[initialize] NTC2   : ✅");

    analogReadResolution(12);
    if (!_ina237.INA237_begin()) {
        Serial.println("❌ [initialize] Init error for INA237 !");
        while (true);  
    } else {
        Serial.println("[initialize] INA237 : ✅");
    }
   
    // BLE
    _ble = new BLE(new ServerCallbacks(), new BLECallbacks());

    return true;
}

// Commands
CommandType stringToCommand(String cmd) {
    if (cmd == "BUZZER") return CommandType::BUZZER;
    if (cmd == "LED_R")  return CommandType::LED_R;
    if (cmd == "LED_G")  return CommandType::LED_G;
    if (cmd == "CTN")    return CommandType::CTN;
    if (cmd == "I2C")    return CommandType::I2C;
    if (cmd == "INA")    return CommandType::INA;
    if (cmd == "TEMP")   return CommandType::TEMP;
    if (cmd == "R_LOG")  return CommandType::R_LOG;
    if (cmd == "W_LOG")  return CommandType::W_LOG;
    return CommandType::UNKNOWN;
}

// Log 
// TODO create SPIFF driver into lib/SPIFFS folder
String getTimestamp() {
    unsigned long seconds = millis() / 1000;
    int hours = seconds / 3600;
    int minutes = (seconds % 3600) / 60;
    int secs = seconds % 60;

    char buffer[12];
    snprintf(buffer, sizeof(buffer), "[%02d:%02d:%02d]", hours, minutes, secs);

    return String(buffer);
}

const char* logTypeToString(LogType type) {
    switch (type) {
        case LOG_INFO: return "[INFO]";
        case LOG_WARNING: return "[WARNING]";
        case LOG_ERROR: return "[ERROR]";
        case LOG_DEBUG: return "[DEBUG]";
        case LOG_FATAL: return "[FATAL]";
        default: return "[UNKNOWN]";
    }
}

bool writeLogSPIFFS(LogType logType, String message) {
    Serial.println("------------ WRITE SPIFFS LOG ------------");
    
    File file = SPIFFS.open(LOG_FILE, FILE_APPEND);
    
    if (!file) {
        Serial.println("❌ [writeLogSPIFF] Error openning log file !");
        Serial.println("------------------------------------------");
        return false;
    }

    String log = getTimestamp() + String(logTypeToString(logType)) + " " + message;
    Serial.println("log : " + log);
    file.println(log);
    file.close();

    Serial.println("------------------------------------------");
    return true;
}

bool readLogSPIFFS(void) {
    Serial.println("------------ READ SPIFFS LOG ------------");

    File file = SPIFFS.open(LOG_FILE, FILE_READ);
    if (!file) {
        Serial.println("❌ [readLogSPIFF] Error openning log file !");
        Serial.println("-----------------------------------------");
        return false;
    }

    Serial.println("File content :");
    while (file.available()) {
        Serial.write(file.read());
    }
    file.close();

    Serial.println("-----------------------------------------");
    return true;
}