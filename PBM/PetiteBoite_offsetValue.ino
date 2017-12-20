// CALIBRATION OF EACH MUSIC BOX

float addOffsetValue(float loc_angle) {

#if SerialNumber == 1 // Marseilleise #1

  if (loc_angle < 28)
    loc_angle += -1.2;
  else if (loc_angle < 35 )
    loc_angle += -1;
  else if (loc_angle < 44 )
    loc_angle += -0.2;
  else if (loc_angle < 60)
    loc_angle += 0;
  else if (loc_angle < 66)
    loc_angle += 0.3;
  else if (loc_angle < 80)
    loc_angle += 0.9;
  else if (loc_angle < 100)
    loc_angle += 1.25;
  else if (loc_angle < 125)
    loc_angle += 2.1;
  else if (loc_angle < 137)
    loc_angle += 1.8;
  else if (loc_angle < 142)
    loc_angle += -0.2;
  else if (loc_angle < 183)
    loc_angle += 0.5;
  else if (loc_angle < 211)
    loc_angle += -0.4;
  else if (loc_angle < 229)
    loc_angle += -1.1;
  else if (loc_angle < 246)
    loc_angle += -1.1;
  else if (loc_angle < 264)
    loc_angle += 0;
  else if (loc_angle < 276)
    loc_angle += -0.5;
  else if (loc_angle < 310)
    loc_angle += -0.5;
  else if (loc_angle < 336)
    loc_angle += -1;
  else if (loc_angle < 337)
    loc_angle += -1.6;
  else if (loc_angle < 342)
    loc_angle += -1.9;
  else if (loc_angle < 354)
    loc_angle += -2.0;
  else if (loc_angle < 390)
    loc_angle += -9.7;
  else if (loc_angle < 421)
    loc_angle += -8.75;
  else if (loc_angle < 443)
    loc_angle += -7.9;
  else if (loc_angle < 457)
    loc_angle += -7.5;
  else if (loc_angle < 482)
    loc_angle += -6.8;
  else if (loc_angle < 512)
    loc_angle += -6.5;
  else if (loc_angle < 530)
    loc_angle += -7.9;
  else if (loc_angle < 552)
    loc_angle += -8;  
  else if (loc_angle < 578)
    loc_angle += -9.0;
  else if (loc_angle < 600)
    loc_angle += -9.6;
  else if (loc_angle < 695)
    loc_angle += -8.5;
  else if (loc_angle < 710)
    loc_angle += -8.7;
  else if (loc_angle < 730)
    loc_angle += -9.5;
  else 
    loc_angle = loc_angle;  
  loc_angle += 1.; // SAME START

#endif

#if SerialNumber == 2 // Internationale #2
  if (loc_angle < 22)
    loc_angle += 0.5;
  if (loc_angle < 80)
    loc_angle += -0.5;
  if (loc_angle < 141)
    loc_angle += 0.5;
  if (loc_angle < 157)
    loc_angle += 0;
  if (loc_angle < 180)
    loc_angle += -0.2;
  else if (loc_angle < 289)
    loc_angle += -0.5;
  else if (loc_angle < 307)
    loc_angle += -0.4;
  else if (loc_angle < 361)
    loc_angle += -1;
  else if (loc_angle < 405)
    loc_angle += -4.4;
  else if (loc_angle < 423)
    loc_angle += -4;
  else if (loc_angle < 445)
    loc_angle += -4.5;
  else if (loc_angle < 449)
    loc_angle += -3.8;
  else if (loc_angle < 510)
    loc_angle += -3.5;
  else if (loc_angle < 534)
    loc_angle += -3.8;
  else if (loc_angle < 597)
    loc_angle += -4.1;
  else if (loc_angle < 609)
    loc_angle += -4.4;
  else if (loc_angle < 674)
    loc_angle += -4.0;
  else if (loc_angle < 730)
    loc_angle += -4.3;
  else 
    loc_angle += 0;

  loc_angle += -4.7; // SAME START

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
  if (loc_angle < 24)
    loc_angle += -0.4;
  else if (loc_angle < 72)
    loc_angle += -0.2;
  else if (loc_angle < 90)
    loc_angle += -0.5;
  else if (loc_angle < 116)
    loc_angle += -0.7;
  else if (loc_angle < 157)
    loc_angle += -1.0;
  else if (loc_angle < 167)
    loc_angle += -0.7;
  else if (loc_angle < 184)
    loc_angle += -1.2;
  else if (loc_angle < 204)
    loc_angle += -0.8;
  else if (loc_angle < 255)
    loc_angle += -1.2;
  else if (loc_angle < 288)
    loc_angle += -1.8;
  else if (loc_angle < 310)
    loc_angle += -2.0;
  else if (loc_angle < 335)
    loc_angle += -1.8;
  else if (loc_angle < 360)
    loc_angle += -2.3;
  else if (loc_angle < 397)
    loc_angle += -4.3;
  else if (loc_angle < 421)
    loc_angle += -4.4;
  else if (loc_angle < 440) 
    loc_angle += -4.5;
  else if (loc_angle < 515)
    loc_angle += -4.8;
  else if (loc_angle < 538)
    loc_angle += -4.9;
  else if (loc_angle < 557)
    loc_angle += -4.8;
  else if (loc_angle < 584)
    loc_angle += -5.2;
  else if (loc_angle < 622)
    loc_angle += -4.9;
  else if (loc_angle < 655)
    loc_angle += -5.3;
  else if (loc_angle < 684)
    loc_angle += -5.5;
  else if (loc_angle < 720)
    loc_angle += -5.5;
  else 
    loc_angle = loc_angle;

  loc_angle += -2.8; // SAME START

#endif


  return loc_angle;
}

