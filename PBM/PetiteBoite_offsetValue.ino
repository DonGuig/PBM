float addOffsetValue(float loc_angle) {
#if SerialNumber == 2 // International #2
  if (loc_angle < 90)
    loc_angle += 0;
  else if (loc_angle < 131)
    loc_angle -= 0.8;
  else if (loc_angle < 260)
    loc_angle += 0;
  else if (loc_angle < 364)
    loc_angle += 0.5;
  else if (loc_angle < 422)
    loc_angle += 4.5;
  else if (loc_angle < 720)
    loc_angle += 4.0;
  else 
    loc_angle = loc_angle;  
#endif

#if SerialNumber == 4 // International #4
  if (loc_angle < 2)
    loc_angle -= 0;
  else if (loc_angle < 24)
    loc_angle -= 1.6;
  else if (loc_angle < 90)
    loc_angle -= 1.8;
  else if (loc_angle < 260)
    loc_angle -= 1.0;
  else if (loc_angle < 365)
    loc_angle += 0.2;
  else if (loc_angle < 421)
    loc_angle += 2.2;
  else if (loc_angle < 440)
    loc_angle += 2.7;
  else if (loc_angle < 720)
    loc_angle += 3.2;
  else 
    loc_angle = loc_angle;  
#endif


  return loc_angle;
}

