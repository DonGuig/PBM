//Consommation : 200 mA

const int batteryPin  = A0;
float batteryVoltage;

// LE RAPPORT NE MARCHE PAS ENCORE ....
void readBattery() {
  batteryVoltage = 100.0*analogRead(batteryPin)*((220.0/1220.0)/1023.0);
}

