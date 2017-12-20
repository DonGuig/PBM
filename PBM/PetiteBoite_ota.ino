//Pas testé ... Pour uploader en sans fil, peux etre tres utile à la fin. Pas de debug dans ce cas la ...
#include <ArduinoOTA.h>
#include <ESP8266mDNS.h>

void setupOTA() {
  #if (MASTER == 1)
  ArduinoOTA.setHostname("master");
  #else
  ArduinoOTA.setHostname("slave");
  #endif
  ArduinoOTA.setPassword("AnriSala");
  ArduinoOTA.onStart([]() {
    Serial.println("Start");
  });
  ArduinoOTA.onEnd([]() {
    Serial.println("\nEnd");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
    else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
    else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
    else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
    else if (error == OTA_END_ERROR) Serial.println("End Failed");
  });
  ArduinoOTA.begin();
//  Serial.print("OTA_UPDATED_v0.01");
}

void ota() {
  ArduinoOTA.handle();
}

