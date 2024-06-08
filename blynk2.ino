#define BLYNK_TEMPLATE_ID "TMPL38ypbCbV3"
#define BLYNK_TEMPLATE_NAME "TDS Sensor Monitoring"
#define BLYNK_AUTH_TOKEN "9SV4611PkInBdG0ZkF2jhwcHCGh77ati"
#define BLYNK_DEFAULT_DOMAIN "blynk-cloud.com"
#define BLYNK_DEFAULT_PORT 80
#define BLYNK_DEFAULT_PORT_SSL   9443

//Comment this out to disable prints and save space
#define BLYNK_PRINT Serial
#include <BlynkSimpleEsp8266.h>
#include <ESP8266WiFi.h>
 
#include <WiFiClient.h>
 
 
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
 
// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
 
// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Rrr";
char pass[] = "09815100";
 
 
 
char auth[] = BLYNK_AUTH_TOKEN;

 WiFiClient wifiClient;

// This function tries to connect to the cloud using TCP
bool connectBlynk()
{
  wifiClient.stop();
  return wifiClient.connect(BLYNK_DEFAULT_DOMAIN, BLYNK_DEFAULT_PORT);
}

// This function tries to connect to your WiFi network
void connectWiFi()
{
  if (pass && strlen(pass)) 
  {
    WiFi.begin((char*)ssid, (char*)pass);
  }
  else
  {
    WiFi.begin((char*)ssid);
  }

  while (WiFi.status() != WL_CONNECTED) 
  {
    digitalWrite(2, !digitalRead(2));
    delay(500);  
  }
}

namespace pin {
const byte tds_sensor = A0;
const byte one_wire_bus = D3; // Dallas Temperature Sensor
}
 
namespace device {
float aref = 3.3; // Vref, this is for 3.3v compatible controller boards, for arduino use 5.0v.
}
 
namespace sensor {
float ec = 0;
unsigned int tds = 0;
float waterTemp = 0;
float ecCalibration = 1;
}
 
OneWire oneWire(pin::one_wire_bus);
DallasTemperature dallasTemperature(&oneWire);
 
 
void setup() {
  Serial.begin(115200); // Dubugging on hardware Serial 0
  connectWiFi();
  Blynk.begin(auth, ssid, pass);
  dallasTemperature.begin();
 
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  delay(2000);
  display.clearDisplay();
  display.setTextColor(WHITE);
}
 
 
void loop() {
   Blynk.run();
  readTdsQuick();
   
  delay(1000);
 
}
 
void readTdsQuick() {
  dallasTemperature.requestTemperatures();
  sensor::waterTemp = dallasTemperature.getTempCByIndex(0);
  float rawEc = analogRead(pin::tds_sensor) * device::aref / 1024.0; // read the analog value more stable by the median filtering algorithm, and convert to voltage value
  float temperatureCoefficient = 1.0 + 0.02 * (sensor::waterTemp - 25.0); // temperature compensation formula: fFinalResult(25^C) = fFinalResult(current)/(1.0+0.02*(fTP-25.0));
  sensor::ec = (rawEc / temperatureCoefficient) * sensor::ecCalibration; // temperature and calibration compensation
  sensor::tds = (133.42 * pow(sensor::ec, 3) - 255.86 * sensor::ec * sensor::ec + 857.39 * sensor::ec) * 0.5; //convert voltage value to tds value
  Serial.println("--------------------------------------------------------------------");
  Serial.println("|TDS in water(measured in PPM) | Suitability for drinking water    |");
  Serial.println("--------------------------------------------------------------------");
  Serial.println("|Between 50-150                | Excellent for drinking            |");
  Serial.println("|------------------------------|-----------------------------------|");
  Serial.println("|150-200                       | Good for drinking                 |");
  Serial.println("|------------------------------|-----------------------------------|");
  Serial.println("|250-300                       | Fair for drinking                 |");
  Serial.println("|------------------------------|-----------------------------------|");
  Serial.println("|300-500                       | Poor,not good for drinking        |");
  Serial.println("|------------------------------|-----------------------------------|");
  Serial.println("|Above 1200                    | Unacceptable                      |");
  Serial.println("--------------------------------------------------------------------"); 
  Serial.print(F("TDS:")); Serial.println(sensor::tds);
  Serial.print(F("EC:")); Serial.println(sensor::ec, 2);
  Serial.print(F("Temperature:")); Serial.println(sensor::waterTemp,2);
  if(sensor::tds < 150)
  {
    Serial.println("Excellent for drinking");
  }
  else if(sensor::tds > 150 and sensor::tds<250)
  {
    Serial.println("Good for drinking");
  }
  else if(sensor::tds > 250 and sensor::tds < 300)
  {
    Serial.println("Fair for drinking");
  }
  else
  {
    Serial.println("Poor for drinking");
  }
  delay(1000);
 display.clearDisplay();
  display.setCursor(10,0);  
  display.setTextSize(2);
  display.setTextColor(WHITE);
 display.print("TDS:"+String(sensor::tds));
    display.setCursor(10,20);
  display.setTextSize(2);
 display.print("EC:"+String(sensor::ec, 2));
   display.setCursor(10,45);
  display.setTextSize(2);
 display.print("T:"+String(sensor::waterTemp,2));
  display.display();
  Blynk.virtualWrite(V0,(sensor::tds));
 
   Blynk.virtualWrite(V1,(sensor::ec));
 
     Blynk.virtualWrite(V2,(sensor::waterTemp));
}
 
