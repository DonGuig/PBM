#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <ESP8266HTTPUpdateServer.h>

ESP8266WebServer server (80);
ESP8266HTTPUpdateServer httpUpdater;

String webPage = "";
String rebootWebPage = "\
\
<h1> The playback mode has changed. Please restart the box. Please reconnect to wifi \"SCLASHPBM\" if you wish to reconfigure it.</h1>\
\
";

void makeWebPage() {
  webPage = "<h1>Web Server - Clash Music Box - Anri Sala </h1>";
  
#if MASTER
  webPage += "<h1> MASTER BOX </h1>";
  webPage += ("<h1>Control Interface</h1>\
  <p>Infinite loop <a href=\"InfiniteLoop\"><button>SET</button></a></p>\
  <p>1 loop and 30 secondes break <a href=\"Every10sec\"><button>SET</button></a></p>\  
  <p>1 loop and 1 minute break <a href=\"EveryMin\"><button>SET</button></a></p>\
  <p>1 loop every 5 minutes <a href=\"Every5min\"><button>SET</button></a></p>\
  <p>3 loop every 1 hour <a href=\"EveryHour\"><button>SET</button></a></p>\
  <p></p>\
  <h1> START MUSIC BOX MANUALY </h1>\
  <p> <a href=\"PlayNow\"><button>PLAY NOW</button></a></p>\
  <h1 style=\"text-align:center;\">Current mode : <strong style=\"color:rgb(191, 34, 0);\">" + playback_mode_char + "</strong></h1>");

#else
  webPage += "<h1> SLAVE BOX </h1>\
              <p> To modify the mode go to the Master : 192.168.1.1 </p>";
#endif
  webPage += "<p></p><p>Id : BOX-#" + String(SerialNumber) + " v" + Firmware + "</p>";
}

void handleWebClient() {
	server.handleClient();
}

void configWebPage() {

  makeWebPage();
  
  server.send(200, "text/html", webPage);

  server.on("/", [](){
    makeWebPage();
    server.send(200, "text/html", webPage);
  });

  server.on("/InfiniteLoop", [](){
    set_playback_mode(0);
    makeWebPage();
    server.send(200, "text/html", rebootWebPage);
    ESP.restart();
  });

  server.on("/Every5min", [](){
    set_playback_mode(1);
    makeWebPage();
    server.send(200, "text/html", rebootWebPage);
    delay(1000);
    ESP.restart();
  });

  server.on("/EveryHour", [](){
    set_playback_mode(2);
    makeWebPage();
    server.send(200, "text/html", rebootWebPage);
    delay(1000);
    ESP.restart();
  });

  server.on("/Every10sec", [](){
    set_playback_mode(3);
    makeWebPage();
    server.send(200, "text/html", rebootWebPage);
    delay(1000);
    ESP.restart();
  });

  server.on("/EveryMin", [](){
    set_playback_mode(4);
    makeWebPage();
    server.send(200, "text/html", rebootWebPage);
    delay(1000);
    ESP.restart();
  });

  server.on("/PlayNow", [](){
    makeWebPage();
    server.send(200, "text/html", webPage);
    play_now = true;
  });



  MDNS.begin("BOX-#"+SerialNumber);
  httpUpdater.setup(&server, "HAL_SAS", "HalForArt");

  server.begin();

  MDNS.addService("http", "tcp", 80);
  
  Serial.println("HTTP server started");
}
