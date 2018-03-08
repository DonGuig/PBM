#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

ESP8266WebServer server (80);
String webPage = "";
String rebootWebPage = "\
\
<h1> The playback mode has changed. Please restart the TWO boxes. Please reconnect to wifi \"EspHalSalaBox1\" if you wish to reconfigure it.</h1>\
\
<p><i><b>Note :</b> each time the two boxes restart, they will do a few loops before going to their configured playback mode.</i></p>";

void makeWebPage() {
  webPage = "<h1>Web Server Boite a Musique";
#ifdef SLAVE
  webPage += " -- SLAVE BOX ";
#endif
#ifdef MASTER
  webPage += " -- MASTER BOX ";
#endif
  webPage += ("<h1>Petites Boite a musique - Control Interface</h1>\
  <p>Infinite loop <a href=\"InfiniteLoop\"><button>start</button></a></p>\
  <p>1 loop every 5 min <a href=\"Every5min\"><button>start</button></a></p>\
  <p>1 loop every hour <a href=\"EveryHour\"><button>start</button></a></p>\
  <p>1 loop every 10sec <a href=\"Every10sec\"><button>start</button></a></p>\
  <h1 style=\"text-align:center;\">Current mode : <strong style=\"color:rgb(191, 34, 0);\">" + playback_mode_char + "</strong></h1>" +
  "<p><i><b>Note :</b> each time the two boxes restart, they will do a few loops before going to their configured playback mode.</i></p>");
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
    ESP.restart();
  });

  server.on("/EveryHour", [](){
    set_playback_mode(2);
    makeWebPage();
    server.send(200, "text/html", rebootWebPage);
    ESP.restart();
  });

  server.on("/Every10sec", [](){
    set_playback_mode(3);
    makeWebPage();
    server.send(200, "text/html", rebootWebPage);
    ESP.restart();
  });
  
  server.begin();
  Serial.println("HTTP server started");
}