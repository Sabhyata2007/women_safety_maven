#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <LiquidCrystal_I2C.h>

// GPS setup
static const int RXPin = 4, TXPin = 3;
static const uint32_t GPSBaud = 9600;
TinyGPSPlus gps;
SoftwareSerial ss(RXPin, TXPin);

// I2C LCD setup
LiquidCrystal_I2C lcd(0x27, 16, 2);

// GSM setup
static const int GSM_RXPin = 7, GSM_TXPin = 8;
SoftwareSerial gsm(GSM_RXPin, GSM_TXPin);

// Buzzer setup
const int buzzerPin = 9;

void setup(){
  Serial.begin(9600);
  ss.begin(GPSBaud);
  gsm.begin(9600);
  
  lcd.clear();
  lcd.init(); // initialize the lcd
  lcd.backlight();
  
  pinMode(buzzerPin, OUTPUT);
  digitalWrite(buzzerPin, LOW);
}

void loop(){
  while (ss.available() > 0){
    gps.encode(ss.read());
    if (gps.location.isUpdated()){
      float latitude = gps.location.lat(); 
      float longitude = gps.location.lng();
      
      // Display on Serial
      Serial.print("Latitude= "); 
      Serial.print(latitude, 6);
      Serial.print(" Longitude= "); 
      Serial.println(longitude, 6);
      
      // Display on LCD
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Latitude: ");
      lcd.print(latitude, 3);
      lcd.setCursor(0, 1);
      lcd.print("Longitude: ");
      lcd.print(longitude, 3);
      
      // Send location via GSM
      sendLocation(latitude, longitude);
      
      // Activate the buzzer
      digitalWrite(buzzerPin, HIGH);
      delay(2000);
      
      // Check for message acknowledgment
      if (checkMessages()) {
        digitalWrite(buzzerPin, LOW);
      } else {
        delay(7200000); // 2 hours delay if no acknowledgment
      }
    }
  }
}

void sendLocation(float latitude, float longitude) {
  gsm.print("AT+CMGF=1\r"); // Set SMS to text mode
  delay(1000);
  
  // Send to first phone number
  gsm.print("AT+CMGS=\"+1234567890\"\r"); // Replace with actual phone number
  delay(1000);
  gsm.print("Location: Lat=");
  gsm.print(latitude, 6);
  gsm.print(", Lng=");
  gsm.print(longitude, 6);
  gsm.write(26); // ASCII code for CTRL+Z to send SMS
  delay(10000);
  
  // Send to second phone number
  gsm.print("AT+CMGS=\"+0987654321\"\r"); // Replace with actual phone number
  delay(1000);
  gsm.print("Location: Lat=");
  gsm.print(latitude, 6);
  gsm.print(", Lng=");
  gsm.print(longitude, 6);
  gsm.write(26); // ASCII code for CTRL+Z to send SMS
  delay(10000);
}

bool checkMessages() {
  gsm.print("AT+CMGL=\"ALL\"\r"); // List all messages
  delay(1000);
  while (gsm.available()) {
    String message = gsm.readString();
    if (message.indexOf("READ") != -1) {
      return true; // If any message has been read
    }
  }
  return false;
}

