#include <Arduino.h>
#include <WiFi.h>
#include <WiFiMulti.h>
#include <HTTPClient.h>
#include <WiFiClient.h>
#include <DHT.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include<Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
Adafruit_SSD1306 display(128, 64, &Wire, 4);

String mainURL =  "http://nasirkhn.com/sensor/api.php";
char wifi_name[] = "NAF Tech_WiFi";
//char wifi_name[] = "Tonmoy Mobile";
char password[] = "N@f Tech";
float p_temp, d_temp, humidity;
int httpCode;
static const unsigned char PROGMEM degree[] = {0xff, 0xff, 0xc3, 0xc3, 0xc3, 0xc3, 0xff, 0xff};
static const unsigned char PROGMEM network[] = {0xff, 0x7e, 0x3c, 0x18, 0x18, 0x18, 0x18, 0x18};
static const unsigned char PROGMEM bad[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xc0};
static const unsigned char PROGMEM medium[] = {0x00, 0x00, 0x00, 0x00, 0xc0, 0xc0, 0xc0, 0xc0};
static const unsigned char PROGMEM good[] = {0x00, 0x00, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0};
static const unsigned char PROGMEM excelent[] = {0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0};
static const unsigned char PROGMEM no_signal[] = {0x00, 0x00, 0x00, 0xcc, 0x78, 0x30, 0x78, 0xcc};

WiFiMulti wifiMulti;
OneWire oneWire(15);
DallasTemperature probe(&oneWire);
DHT dht(5, DHT11);
WiFiClient client; HTTPClient http;

void setup() {
  Serial.begin(115200);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  wifiMulti.addAP(wifi_name, password);
  probe.begin();
  dht.begin();
  display.clearDisplay();
  display.display();
  display.setRotation(2);
  display.setTextSize(3);
  display.setTextColor(WHITE);
}

void loop() {
  probe_temp_update(); disp_update();
  if ((wifiMulti.run() == WL_CONNECTED)) {
    http.begin(client, mainURL + "?temp=" + String(p_temp)); //HTTP
    httpCode = http.GET();
    http.end();
  }
  delay(5000);
}
