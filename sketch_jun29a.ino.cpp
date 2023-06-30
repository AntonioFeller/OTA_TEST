#include <Arduino.h>
#line 1 "C:\\Users\\Antonio\\OneDrive\\Documentos\\Arduino\\sketch_jun29a\\sketch_jun29a.ino"
#include <WiFi.h>
#include <HTTPClient.h>
#include <Update.h>

const char* ssid = "Antonio_plus";
const char* password = "17041994";
const char* firmwareURL = "https://github.com/AntonioFeller/OTA_TEST/blob/main/sketch_jun29a.ino.bin";

#line 9 "C:\\Users\\Antonio\\OneDrive\\Documentos\\Arduino\\sketch_jun29a\\sketch_jun29a.ino"
void setup();
#line 22 "C:\\Users\\Antonio\\OneDrive\\Documentos\\Arduino\\sketch_jun29a\\sketch_jun29a.ino"
void loop();
#line 26 "C:\\Users\\Antonio\\OneDrive\\Documentos\\Arduino\\sketch_jun29a\\sketch_jun29a.ino"
void updateFirmware();
#line 9 "C:\\Users\\Antonio\\OneDrive\\Documentos\\Arduino\\sketch_jun29a\\sketch_jun29a.ino"
void setup() {
  Serial.begin(9600);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  updateFirmware();
}

void loop() {
  // Nada a ser feito no loop
}

void updateFirmware() {
  HTTPClient http;

  Serial.print("Downloading firmware from: ");
  Serial.println(firmwareURL);

  http.begin(firmwareURL);
  int httpCode = http.GET();

  if (httpCode == HTTP_CODE_OK) {
    Serial.println("Firmware download successful");

    WiFiClient& client = http.getStream();
    bool canBegin = Update.begin(UPDATE_SIZE_UNKNOWN);

    if (canBegin) {
      size_t written = Update.writeStream(client);

      if (written == http.getSize()) {
        Serial.println("Firmware update succeeded");
      } else {
        Serial.println("Firmware update failed");
      }
    } else {
      Serial.println("Firmware update could not begin");
    }
  } else {
    Serial.print("Firmware download failed, error: ");
    Serial.println(httpCode);
  }

  http.end();
}

