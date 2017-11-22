//Pas testé ... Pour uploader en sans fil, peux etre tres utile à la fin. Pas de debug dans ce cas la ...
#include <ArduinoOTA.h>

void setupOTA() {
  #if (MASTER == 1)
  ArduinoOTA.setHostname("master");
  #else
  ArduinoOTA.setHostname("slave");
  #endif
  ArduinoOTA.setPassword("AnriSala");
  ArduinoOTA.begin();
}

void ota() {
  ArduinoOTA.handle();
}

