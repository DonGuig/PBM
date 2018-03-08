//// Wifi Setting
// Udp Setting
#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <WiFiUdp.h>



//----------------------------- WIFI -------------------------------------//
/**/const char *ssid = "EspHalSalaBox1", *password = "iloveesp8266";      //
/**/IPAddress gateway(192,168,1,1), subnet(255,255,255,0);                //
/**/                                                                      //
/**/#if MASTER == 1                                                       //
/**/  IPAddress local_IP(192,168,1,1), remote_IP(192,168,1,2);            //
/**/  unsigned int localUdpPort = 1234, remoteUdpPort = 1235;             //
/**/#else                                                                 //
/**/  IPAddress local_IP(192,168,1,2), remote_IP(192,168,1,1);            //
/**/  unsigned int localUdpPort = 1235, remoteUdpPort = 1234;             //
/**/#endif                                                                //
//------------------------------------------------------------------------// 



// UDP ----------------------
WiFiUDP Udp;
char incomingPacket[255];

void setupWifi() {
#if MASTER==1
  Serial.println("*** MASTER ***");

//  WiFi.setAutoConnect(false);
  WiFi.setAutoConnect(false);
  WiFi.softAPConfig(local_IP, gateway, subnet);    
  WiFi.softAP(ssid, password, 1, 1);  //SSID, PASS, CANAL, CACHÉ

/*
  if ( MDNS.begin ( host ) ) {
    Serial.println ( "MDNS responder started" );
  }
*/

#else

  Serial.println("*** SLAVE ***");
  Serial.print("Connecting to ");Serial.println(ssid);
  WiFi.config(local_IP, gateway, subnet);WiFi.mode(WIFI_STA);WiFi.begin(ssid, password);    
//  while (WiFi.status() != WL_CONNECTED) {delay(500);Serial.print(".");}WiFi.waitForConnectResult()
  int i = 0 ;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    if (i > 10) {
      Serial.println("Connection Failed! Rebooting...");
      ESP.restart();
    }
    i++;
  }
  Serial.println("");Serial.println("WiFi connected");
 
#endif
  WiFi.setOutputPower(20);
  Serial.println("WIFI SETUP INFORMATION");
  WiFi.printDiag(Serial);
  Serial.println("END WIFI SETUP INFORMATION");
}

#if MASTER == 0
void checkWifi() { // this will reboot the device if connection was lost
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("disconnected");
    while (WiFi.waitForConnectResult() != WL_CONNECTED) {Serial.println("Connection Failed! Rebooting...");delay(5000);ESP.restart();}
  }
  else {
    Serial.println("Still Connected");
  }
}
#endif

//******************************** VOID UDP ***************************************
void setupUdp() {
  Udp.begin(localUdpPort); 
}

void routeUdp() {
  char *strAddress = strtok(incomingPacket, " ");
#if MASTER == 1
  receive_master_resync(strAddress); //ptp
  receive_master_isSync(strAddress); //ptp
  receive_master_t1pt2(strAddress); //ptp
  receive_master_ready_to_begin(strAddress);
#else
  receive_slave_clock_offset(strAddress); //ptp
  receive_slave_t1(strAddress); //ptp
  receive_slave_syncPoint(strAddress); // on slave_loop
  receive_slave_freewheel_syncpoint(strAddress); // on slave_loop
  receive_slave_end_freewheel(strAddress); // on slave_loop
  receive_slave_stop_next_loop(strAddress);
  receive_slave_play(strAddress);
  receive_slave_begin(strAddress);
#endif
}

void sendUdp(String Content) {
  // NOTE : Takes around 1ms

//  Serial.print("SENDUDP : ");Serial.println(Content);
  char content_char[255];
  Content.toCharArray(content_char, 255);
  Udp.beginPacket(remote_IP, remoteUdpPort);
  Udp.write(content_char);
  Udp.endPacket(); 
}


void receiveUdp() {
  // NOTE : Takes less than 1ms
  memset(incomingPacket, 0, 255);
  int packetSize = Udp.parsePacket();
  if (packetSize) {
//    Serial.printf("Received %d bytes from %s, port %d\n", packetSize, Udp.remoteIP().toString().c_str(), Udp.remotePort());
    int len = Udp.read(incomingPacket, 255);
    if (len > 0)
      incomingPacket[len] = 0;
    routeUdp();
  }
}


