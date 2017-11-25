// SYNCHRONISATION temporelle (de millis()) entre le slave et le master.
// inspiré de https://en.wikipedia.org/wiki/Precision_Time_Protocol

/*
 *         ||| Slave  --> RESYNC
 * RESYNC  --> Master --> T1
 * T1      --> Slave  --> T1PT2
 * T1PT2 . --> Master --> OFFSET
 * OFFSET  --> Slave  --> IS_SYNC
 * IS_SYNC --> Master |||
 */

 
bool slave_sync = false;
long t1, t1p, t2, t2p, slave_offset;

// millis() avec offset !
unsigned long sync_millis() {
#if MASTER==0
  return millis() - slave_offset;
#else
  return millis();
#endif
}

void re_sync() { // Appel du slave au master 
  Serial.println("RESYNC");
  slave_sync = false;
  if (MASTER == 0) 
    sendUdp("RESYNC");
  while (!slave_sync) {receiveUdp();}
  slave_sync = false;
  Serial.print("END_SYNC :");Serial.print(slave_offset);
  Serial.print(" SYNC_MILLIS ");Serial.println(sync_millis());
}

// FONCTIONS APPELÉ PAR UDP_RECEIVE DANS WIFI

void receive_master_resync(char *udpStrAddress) {
  Serial.println("receive_resync");
  if (strcmp(udpStrAddress,"RESYNC") == 0) {
    t1 = millis();
    sendUdp("T1");
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
    slave_offset = (t1p - t1 - t2p + t2) / 2;
    sendUdp("OFFSET " + String(slave_offset));
    Serial.print("t1 ");Serial.println(t1);
    Serial.print(" t1p ");Serial.println(t1p);
    Serial.print(" t2 ");Serial.println(t2);
    Serial.print(" t2p ");Serial.println(t2p);
    Serial.print("OFFSET : ");Serial.println(slave_offset);
  }
}

void receive_slave_offset(char *udpStrAddress) {
  if (strcmp(udpStrAddress,"OFFSET") == 0) {
    slave_offset = strtoul(strtok(NULL, " "), NULL, 0);
    sendUdp("IS_SYNC");
    slave_sync = true;
  }
}

void receive_master_isSync(char *udpStrAddress) {
  if (strcmp(udpStrAddress,"IS_SYNC") == 0)
    slave_sync = true;
}
