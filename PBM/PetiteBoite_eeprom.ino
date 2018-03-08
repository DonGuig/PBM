//// Permet d'enregistré en dur la valeur de offset_angle pour accelerer le demarage
#include <EEPROM.h>

bool init_eeprom = false;
float offset_eeprom;
int playback_mode_eeprom;

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
  //sizeof(offset_angle) is the adress we are reading from : we want to read AFTER the bytes used for offset_angle
  EEPROM.get(sizeof(offset_angle), playback_mode_eeprom);
  Serial.print("playback_mode EEPROM :");Serial.println(playback_mode_eeprom);
  set_playback_mode(playback_mode_eeprom);
}

void updateEeprom() {
  if (abs(EEPROM.get(0,offset_eeprom) - offset_angle) > 0.5)
    init_eeprom = true;  
  if (init_eeprom == true) {        
    Serial.println(" (re)Write EEPROM : ");        
    EEPROM.put(0,offset_angle);
    EEPROM.commit();
    init_eeprom = false;
  }
}

void updatePlaybackModeEeprom(){
  //sizeof(offset_angle) is the adress we are writing at : we want to write AFTER the bytes used for offset_angle

  if (EEPROM.get(sizeof(offset_angle),playback_mode_eeprom)!= playback_mode) {
    Serial.println("About to write playback_mode to EEPROM");
    EEPROM.put(sizeof(offset_angle), playback_mode);
    EEPROM.commit();
  }
}

