// CALIBRATION OF EACH MUSIC BOX

float addOffsetValue(float loc_angle) {
#if SerialNumber == 1 // Marseilleise #1
  if (loc_angle < 28)
    loc_angle += -1.5;
  else if (loc_angle < 44 )
    loc_angle += -1;
  else if (loc_angle < 80)
    loc_angle += 0;
  else if (loc_angle < 100)
    loc_angle += 1.25;
  else if (loc_angle < 144)
    loc_angle += 1.5;
  else if (loc_angle < 183)
    loc_angle += 0;
  else if (loc_angle < 246)
    loc_angle += -0.5;
  else if (loc_angle < 276)
    loc_angle += 0;
  else if (loc_angle < 310)
    loc_angle += -0.5;
  else if (loc_angle < 361)
    loc_angle += -1;
  else if (loc_angle < 392)
    loc_angle += -8.5;
  else if (loc_angle < 421)
    loc_angle += -8.25;
  else if (loc_angle < 443)
    loc_angle += -7.;
  else if (loc_angle < 482)
    loc_angle += -6;
  else if (loc_angle < 530)
    loc_angle += -7;
  else if (loc_angle < 555)
    loc_angle += -8;  
  else if (loc_angle < 566)
    loc_angle += -11.5;
  else if (loc_angle < 600)
    loc_angle += -10.5;
  else if (loc_angle < 702)
    loc_angle += -8.5;
  else if (loc_angle < 730)
    loc_angle += -10.0;
  else 
    loc_angle = loc_angle;  
  loc_angle += 1.; // SAME START
#endif

#if SerialNumber == 2 // Internationale #2
  if (loc_angle < 180)
    loc_angle += 0;
  else if (loc_angle < 305)
    loc_angle -= 0.5;
  else if (loc_angle < 361)
    loc_angle -= 1;
  else if (loc_angle < 423)
    loc_angle -= 4;
  else if (loc_angle < 445)
    loc_angle -= 3.5;
  else if (loc_angle < 510)
    loc_angle -= 3;
  else if (loc_angle < 730)
    loc_angle -= 3.5;
  else 
    loc_angle += 0;

#endif


#if SerialNumber == 3 // Marseillaise #3
// time between switch and 1st note : 1880ms
  if (loc_angle < 37)
    loc_angle += 0;
  else if (loc_angle < 92)
    loc_angle += 0.3;
  else if (loc_angle < 129)
    loc_angle += -0.0;
  else if (loc_angle < 142)
    loc_angle += -0.6;
  else if (loc_angle < 154)
    loc_angle += -0.8;
  else if (loc_angle < 176)
    loc_angle += -1.1;
  else if (loc_angle < 214)
    loc_angle += -1.4;
  else if (loc_angle < 256)
    loc_angle += -0.8;
  else if (loc_angle < 275)
    loc_angle += -0.9;
  else if (loc_angle < 305)
    loc_angle += -1.1;
  else if (loc_angle < 350)
    loc_angle += -1.5; 
  else if (loc_angle < 360)
    loc_angle += -4.8; 
  else if (loc_angle < 370)
    loc_angle += -8.2;
  else if (loc_angle < 437)
    loc_angle += -8.4;
  else if (loc_angle < 454)
    loc_angle += -8.4;
  else if (loc_angle < 477)
    loc_angle += -8.7;
  else if (loc_angle < 529)
    loc_angle += -8.9;
  else if (loc_angle < 585)
    loc_angle += -9.4;
  else if (loc_angle < 596)
    loc_angle += -9.2;
  else if (loc_angle < 666)
    loc_angle += -8.9;
  else if (loc_angle < 800)
    loc_angle += -9.2;
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

