// SYNCHRONISATION temporelle (de millis()) entre le slave et le master.
// inspiré de https://en.wikipedia.org/wiki/Precision_Time_Protocol

/*
 *         ||| Slave  --> RESYNC
 * RESYNC  --> Master --> T1
 * T1      --> Slave  --> T1PT2
 * T1PT2 . --> Master --> OFFSETS
 * OFFSETS  --> Slave  --> IS_SYNC
 * IS_SYNC --> Master |||
 */

 
bool slave_sync = false;
long t1, t1p, t2, t2p, slave_clock_offset, master_to_slave_delay;


// millis() avec offset !
unsigned long sync_millis() {
#if MASTER==0
  return millis() - slave_clock_offset;
#else
  return millis();
#endif
}

void slave_ask_for_resync() { // Appel du slave au master 
  Serial.println("RESYNC");
  slave_sync = false;
  sendUdp("RESYNC"); // we want to keep asking in case the first request got lost
  int i = 0;
  while (!slave_sync) {    
    receiveUdp();
    if (i > 10000) { // Timeout to send resync
      sendUdp("RESYNC");
      i = 0;
    }
    i++;
  }
  // slave_sync = false;
}

// FONCTIONS APPELÉ PAR UDP_RECEIVE DANS WIFI

void receive_master_resync(char *udpStrAddress) {
  if (strcmp(udpStrAddress,"RESYNC") == 0) {
    Serial.println("Slaved asked for a resync");
    t1 = millis();
    sendUdp("T1"); 
    // we do not need to send the value of t1, 
    // as offset calculation will be done in the master
  }
}

void receive_slave_t1(char *udpStrAddress) {
  if (strcmp(udpStrAddress,"T1") == 0) {
    t1p = millis();
    delay(5);
    t2 = millis();
    sendUdp("T1PT2 "+String(t1p)+" "+String(t2));
  }
}

void receive_master_t1pt2(char *udpStrAddress) {
  if (strcmp(udpStrAddress,"T1PT2") == 0) {
    t2p = millis();
    t1p = strtoul(strtok(NULL, " "), NULL, 0);
    t2 = strtoul(strtok(NULL, " "), NULL, 0);
    slave_clock_offset = (t1p - t1 - t2p + t2) / 2;
    master_to_slave_delay = (t1p - t1 + t2p - t2) / 2;
    sendUdp("OFFSETS " + String(slave_clock_offset) + " " + String(master_to_slave_delay));
    Serial.print(" t1 ");Serial.println(t1);
    Serial.print(" t1p ");Serial.println(t1p);
    Serial.print(" t2 ");Serial.println(t2);
    Serial.print(" t2p ");Serial.println(t2p);;
    Serial.print("slave_clock_offset : ");Serial.println(slave_clock_offset);
    Serial.print("master_to_slave_delay : ");Serial.println(master_to_slave_delay);
  }
}

void receive_slave_clock_offset(char *udpStrAddress) {
  if (strcmp(udpStrAddress,"OFFSETS") == 0) {
    slave_clock_offset = strtoul(strtok(NULL, " "), NULL, 0);
    master_to_slave_delay = strtoul(strtok(NULL, " "), NULL, 0);
    Serial.print("slave_clock_offset :");Serial.print(slave_clock_offset);
    Serial.print("master_to_slave_delay : ");Serial.println(master_to_slave_delay);
    sendUdp("IS_SYNC");
    slave_sync = true;
  }
}

void receive_master_isSync(char *udpStrAddress) {
  if (strcmp(udpStrAddress,"IS_SYNC") == 0)
    slave_sync = true;
}
