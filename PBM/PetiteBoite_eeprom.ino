// Permet d'enregistré en dur la valeur de offset_angle pour accelerer le demarage
#include <EEPROM.h>

bool init_eeprom = false;
float offset_eeprom;

void setupEeprom() {
  EEPROM.begin(512);
  Serial.print("EEPROM ");Serial.println(EEPROM.get(0, offset_eeprom));
  if (EEPROM.get(0,offset_eeprom) == 0 || isnan(EEPROM.get(0, offset_eeprom))) {
    Serial.println("NO Offset EEPROM");
    init_eeprom = true;
  }
  else {
    EEPROM.get(0, offset_angle);
    Serial.print("Offset EEPROM :");Serial.println(offset_angle);
  }
}


void updateEeprom() {
  if (f_mod((EEPROM.get(0,offset_eeprom) - offset_angle),360) > 5)
    init_eeprom = true;  
  if (init_eeprom == true) {        
    Serial.print(" (re)Write EEPROM : ");        
    EEPROM.put(0,offset_angle);
    EEPROM.commit();
    init_eeprom = false;
  }
}

