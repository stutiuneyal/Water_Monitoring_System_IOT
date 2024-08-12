# Water_Monitoring_System_IOT

This project demonstrates how to monitor Total Dissolved Solids (TDS) in water using an ESP8266 microcontroller. It provides real-time data on water quality by measuring the TDS, Electrical Conductivity (EC), and temperature, and displays the information on an OLED screen. The data is also sent to the Blynk IoT platform for remote monitoring.

## Features
- TDS Monitoring: Measures TDS levels in water and determines the suitability of the water for drinking.
- Temperature and EC Measurement: Measures the water temperature and electrical conductivity.
- OLED Display: Real-time display of TDS, EC, and temperature readings on a 128x64 OLED screen.
- Blynk Integration: Sends data to the Blynk cloud for remote monitoring via the Blynk mobile app.

## Hardware Requirements
- ESP8266 (e.g., NodeMCU)
- TDS Sensor
- DS18B20 Temperature Sensor
- 128x64 OLED Display
- Jumper wires and Breadboard

## Software Requirements
- Arduino IDE
- Blynk Library
- ESP8266WiFi Library
- Adafruit GFX and SSD1306 Libraries
- DallasTemperature and OneWire Libraries

## Installation
**1. Clone the repository**
   
`https://github.com/stutiuneyal/Water_Monitoring_System_IOT.git`
`cd TDS-Sensor-Monitoring`

**2. Install the required libraries**
 
- Open the Arduino IDE and go to **Sketch > Include Library > Manage Libraries**
- Search for and install the following libraries:
  - Blynk
  - ESP8266WiFi
  - Adafruit GFX
  - Adafruit SSD1306
  - DallasTemperature
  - OneWire
  
**3. Configure the project**

Replace the WiFi credentials and Blynk authorization token in the source code with your own.
Upload the code to your ESP8266 board.

## Usage

**1. Connect the hardware components**
   - Connect the TDS sensor to the analog pin (A0) of the ESP8266.
   - Connect the DS18B20 temperature sensor to digital pin D3.
   - Connect the OLED display to the I2C pins (SDA, SCL) of the ESP8266.

**2. Power up the ESP8266**
   - Once the ESP8266 is powered on, it will connect to the specified WiFi network and begin 
   - sending data to the Blynk cloud.
   - The OLED display will show the current TDS, EC, and temperature readings.

**3. Monitor the data**
   - Open the Blynk mobile app, and use the virtual pins (V0 for TDS, V1 for EC, and V2 for Temperature) to monitor the data remotely.

## Output Description
- TDS: The Total Dissolved Solids measured in parts per million (PPM).
- EC: Electrical Conductivity of the water in microsiemens per centimeter (µS/cm).
- Temperature: Water temperature in degrees Celsius.
  
The data is analyzed to determine the water quality:

- TDS between 50-150 PPM: Excellent for drinking.
- TDS between 150-200 PPM: Good for drinking.
- TDS between 250-300 PPM: Fair for drinking.
- TDS above 300 PPM: Poor, not good for drinking.
- TDS above 1200 PPM: Unacceptable.

> [!WARNING]
> You should have CP210x_Universal_Windows_Driver installed in your system.

## output in blynk app

![screenshot of output in blynk app](https://github.com/stutiuneyal/Water_Monitoring_System_IOT/blob/main/output.jpg)
