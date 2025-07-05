#  Women Safety System in Automobile

This project is an embedded safety solution aimed at enhancing the personal security of women in vehicles. It combines **GPS tracking**, **GSM-based emergency alert messaging**, **audible buzzer alerts**, and an **LCD display** for live location monitoring. Designed with low-cost microcontrollers and sensors, the system detects distress and sends the user’s real-time location to trusted contacts.
This project was made during maven silicon internship focus on embedded system 

---

##  Objective

To develop a **portable, vehicle-mounted safety device** for women that:
- Sends **real-time GPS coordinates via SMS** in emergencies.
- Activates a **buzzer** to alert nearby people.
- Waits for an acknowledgment; if none is received, it resends the location after a defined period.

---

##  Hardware Components

| Component        | Description                                |
|------------------|--------------------------------------------|
| Arduino Uno/Nano | Microcontroller platform                   |
| GPS Module       | NEO-6M or similar                          |
| GSM Module       | SIM800L or SIM900                          |
| 16x2 LCD (I2C)   | Displays latitude and longitude            |
| Buzzer           | Audible alert system                       |
| Power Supply     | 5V regulated (from vehicle or battery)     |
| Push Button (optional) | Manual emergency trigger             |

---

##  System Features

-  **Live GPS Tracking**: Captures latitude and longitude.
-  **SMS Alert System**: Sends location to predefined contacts.
-  **Buzzer Activation**: Notifies people nearby in emergencies.
-  **Smart Retry Mechanism**: Waits 2 hours and resends if no acknowledgment.
-  **LCD Display**: Real-time feedback of current GPS data.

---

##  How It Works

1. GPS fetches current location.
2. Coordinates are displayed on LCD and logged to Serial Monitor.
3. GSM sends SMS alerts to 2 emergency contacts.
4. Buzzer is turned ON for 2 seconds.
5. System waits for acknowledgment SMS.
   - If **received** → buzzer is turned OFF.
   - If **not received** → resends after 2 hours.

---

##  Pin Connections

| Module     | Arduino Pin | Notes                |
|------------|-------------|----------------------|
| GPS RX     | D4          | SoftwareSerial RX    |
| GPS TX     | D3          | SoftwareSerial TX    |
| GSM RX     | D8          | SoftwareSerial TX    |
| GSM TX     | D7          | SoftwareSerial RX    |
| LCD (I2C)  | SDA/SCL     | A4 (SDA), A5 (SCL)   |
| Buzzer     | D9          | Active buzzer        |

---

##  Code Features

- Uses `TinyGPS++` for location parsing.
- Sends two separate SMS messages.
- Reads incoming SMS messages to detect "READ" keyword for acknowledgment.
- Optional extension: Add a push-button for manual SOS triggering.

---

##  Privacy & Safety

- No data is stored in the cloud.
- Phone numbers must be hard-coded into the sketch.
- Requires an active SIM card with SMS capability (no data needed).

---

##  Future Extensions

- Google Maps link generation in SMS
- Voice alert module integration
- Panic button with interrupt-based logic
- Integration with vehicle ignition cutoff in extreme conditions
- Cloud-based backup of location trail

---

##  Use Case

This system is designed to be installed in cars, bikes, or auto-rickshaws used by women. In case of distress or forced entry, the user can trigger the system manually or automatically (based on future upgrades like door sensors), sending live coordinates to family or authorities.

