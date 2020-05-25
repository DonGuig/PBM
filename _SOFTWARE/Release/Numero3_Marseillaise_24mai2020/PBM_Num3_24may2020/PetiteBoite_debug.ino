#define HOST_NAME "PBM#"+SerialNumber



void setupDEBUG() {
#ifdef DEBUG
  String hostNameWifi = HOST_NAME;
  hostNameWifi.concat(".local");
  WiFi.hostname(hostNameWifi);
  if (MDNS.begin(HOST_NAME)) {
    Serial.print("* MDNS responder started. Hostname -> ");
    Serial.println(HOST_NAME);
  }

  MDNS.addService("telnet", "tcp", 23);
  Debug.begin(HOST_NAME); // Initialize the WiFi server

  Debug.setResetCmdEnabled(true); // Enable the reset command

  Debug.showProfiler(true); // Profiler (Good to measure times, to optimize codes)
  Debug.showColors(true); // Colors
  debugI("* RESTART ESP8266 ");
#endif
}


void loopDEBUG() {
// RemoteDebug handle
#ifdef DEBUG
    Debug.handle();
    // Give a time for ESP
#endif
    yield();
}
