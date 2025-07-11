#include "i2cScanner.hpp"
#include "Wire.h"

I2C_SCANNER::I2C_SCANNER() {
}

String I2C_SCANNER::I2C_SCANNER_scanDevices() {
  Serial.println("🔍 Scanning I2C bus...");
  
  String result = "";
  byte error, address;
  int devices = 0;

  for (address = 1; address < 127; address++) {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if (error == 0) {
      Serial.print("✅ Found device at 0x");
      result = "✅ ";
      result += (devices == 1 ? "" : ", ");
      result += "0x";
      if (address < 16) {
        Serial.print("0");
        result += "0";
      }
      Serial.println(address, HEX);
      result += String(address, HEX);
      devices++;
    } else if (error == 4) {
      Serial.print("⚠️ Unknown error at 0x");
      if (address < 16)
        Serial.print("0");
      Serial.println(address, HEX);
    }
  }

  if (devices == 0) {
    Serial.println("❌ No I2C devices found.");
    return "❌ No I2C devices found.";
  } else {
    Serial.println("✅ I2C scan complete.");
    return String(devices) + " device(s) found at address " + result;
  }
}

String I2C_SCANNER::I2C_SCANNER_launchTest() {
    Serial.println("------------ I2C ------------");

    String result = I2C_SCANNER_scanDevices();

    Serial.println("-----------------------------");

    return result;
}
