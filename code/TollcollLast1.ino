

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <HardwareSerial.h>
#include <ESP32Servo.h>

#define RFID_RX 16  // EM-18 TX to ESP32 RX
#define RFID_TX 17  // Not used, but required for HardwareSerial
#define SERVO_PIN 26  // Servo control pin

HardwareSerial RFID(1);
Servo barrierServo;
LiquidCrystal_I2C lcd(0x27, 16, 2);  // Try 0x3F if 0x27 doesn't work

// List of exempted RFID tags
String exemptedRFIDs[] = {
  "5000DB25F856"
};

// List of non-exempted RFID tags
String nonExemptedRFIDs[] = {
  "5000DB29DC7E",
  "5000DAC3A9E0"
};

int numExempted = sizeof(exemptedRFIDs) / sizeof(exemptedRFIDs[0]);
int numNonExempted = sizeof(nonExemptedRFIDs) / sizeof(nonExemptedRFIDs[0]);

void setup() {
  Serial.begin(115200);
  RFID.begin(9600, SERIAL_8N1, RFID_RX, RFID_TX);
  
  Wire.begin(21, 22);  // Define ESP32 I2C pins: SDA = 21, SCL = 22
  lcd.init();
  lcd.backlight();
  resetLCD();  // Ensure LCD starts in a clean state

  barrierServo.attach(SERVO_PIN);
  barrierServo.write(0);  // Keep barrier in closed position
}

void loop() {
  if (RFID.available()) {
    String rfidTag = RFID.readStringUntil('\n');
    rfidTag.trim();
    Serial.println("FastTag Scanned: " + rfidTag);  // Debugging message
    displayMessage("FastTag Scanned:", rfidTag);
    delay(1000);  // Ensure message is visible

    if (isExempted(rfidTag)) {
      Serial.println("Local Vehicle - No Toll Deducted");
      displayMessage("Local Vehicle", "No Toll Deducted");
      delay(1000); //delay to open barrier after 1 sec of msg display
      openBarrier();
    } else if (isNonExempted(rfidTag)) {
      Serial.println("Toll Deducted for Global Vehicle!");
      displayMessage("Global Vehicle", "Toll Deducted!");
      delay(1000); //delay to open barrier after 1 sec of msg display
      openBarrier();
    } else {
      Serial.println("Non-Tag Vehicle!");
      displayMessage("Non-Tag Vehicle", "Access Denied");
    }

    delay(3000);  // Keep message for 3 seconds
    resetLCD();   // Reset LCD to default message
  }
}

// Function to check if the RFID tag is in the exemption list
bool isExempted(String tag) {
  for (int i = 0; i < numExempted; i++) {
    if (tag.equalsIgnoreCase(exemptedRFIDs[i])) {
      return true;
    }
  }
  return false;
}

// Function to check if the RFID tag is in the non-exempted list
bool isNonExempted(String tag) {
  for (int i = 0; i < numNonExempted; i++) {
    if (tag.equalsIgnoreCase(nonExemptedRFIDs[i])) {
      return true;
    }
  }
  return false;
}

// Function to open and close the barrier
void openBarrier() {
  barrierServo.write(90);  // Open barrier
  delay(5000);  // Keep it open for 5 seconds
  barrierServo.write(0);   // Close barrier
}

// Function to display messages on the LCD
void displayMessage(String line1, String line2) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(line1);
  lcd.setCursor(0, 1);
  lcd.print(line2);
  delay(1000);  // Ensure the message is displayed
}

// Function to reset the LCD to "Toll System Ready"
void resetLCD() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Toll Plaza: ");
}
