float addOffsetValue(float loc_angle) {
#if SerialNumber == 2 // International #2
  if (loc_angle < 250)
    loc_angle += -2;
  else if (loc_angle < 131)
    loc_angle += -1.2;
  else if (loc_angle < 260)
    loc_angle += 0;
  else if (loc_angle < 364)
    loc_angle += -2.5;
  else if (loc_angle < 422)
    loc_angle += -6.5;
  else if (loc_angle < 720)
    loc_angle += -6;
  else 
    loc_angle = loc_angle;  
#endif

#if SerialNumber == 3 // Marseillaise #3
// +2 ?
  if (loc_angle < 140)
    loc_angle += 0;
  else if (loc_angle < 240)
    loc_angle += -0.8;
  else if (loc_angle < 275)
    loc_angle += -0.5;
  else if (loc_angle < 305)
    loc_angle += -0.8;
  else if (loc_angle < 350)
    loc_angle += -1.5; 
  else if (loc_angle < 432)
    loc_angle += -8.9;
  else if (loc_angle < 450)
    loc_angle += -8.2;
  else if (loc_angle < 529)
    loc_angle += -8.9;
  else if (loc_angle < 585)
    loc_angle += -9.7;
  else if (loc_angle < 666)
    loc_angle += -8.9;
  else if (loc_angle < 720)
    loc_angle += -7.6;
  else 
    loc_angle = loc_angle;  
#endif

#if SerialNumber == 4 // International #4
  if (loc_angle < 2)
    loc_angle += 0;
  else if (loc_angle < 24)
    loc_angle += -0.4;
  else if (loc_angle < 90)
    loc_angle += -0.2;
  else if (loc_angle < 260)
    loc_angle += -1.0;
  else if (loc_angle < 360)
    loc_angle += -0.8;
  else if (loc_angle < 421)
    loc_angle += -4.4;
  else if (loc_angle < 440) 
    loc_angle += -4.7;
  else if (loc_angle < 720)
    loc_angle += -5.2;
  else 
    loc_angle = loc_angle;  
#endif


  return loc_angle;
}

