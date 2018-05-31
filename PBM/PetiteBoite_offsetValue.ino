// CALIBRATION OF EACH MUSIC BOX

float addOffsetValue(float loc_angle) {

#if SerialNumber == 1 // Marseilleise #1

  if (loc_angle < 33)
    loc_angle += -1.6;
  else if (loc_angle < 39 )
    loc_angle += -1.5;
  else if (loc_angle < 52 )
    loc_angle += -1.3;
  else if (loc_angle < 80 )
    loc_angle += -1.5;
  else if (loc_angle < 108 )
    loc_angle += -1.4;
  else if (loc_angle < 115 )
    loc_angle += -0.9;
  else if (loc_angle < 136 )
    loc_angle += -0.5;
  else if (loc_angle < 152 )
    loc_angle += -1;
  else if (loc_angle < 200 )
    loc_angle += -0.5;
  else if (loc_angle < 205 )
    loc_angle += -1;
  else if (loc_angle < 227 )
    loc_angle += -1.3;
  else if (loc_angle < 247 )
    loc_angle += -1.8;
  else if (loc_angle < 258 )
    loc_angle += -1.5;
  else if (loc_angle < 315 )
    loc_angle += -2;
  else if (loc_angle < 330 )
    loc_angle += -2.3;
  else if (loc_angle < 341 )
    loc_angle += -1.8;
  else if (loc_angle < 347 )
    loc_angle += -1.8;
  else if (loc_angle < 360 )
    loc_angle += -2.7;
  else if (loc_angle < 415 )
    loc_angle += -9.5;
  else if (loc_angle < 465 )
    loc_angle += -10;
  else if (loc_angle < 490 )
    loc_angle += -9.7;
  else if (loc_angle < 525 )
    loc_angle += -8.7;
  else if (loc_angle < 542 )
    loc_angle += -8.9;
  else if (loc_angle < 580 )
    loc_angle += -8.7;
  else if (loc_angle < 592 )
    loc_angle += -10;
  else if (loc_angle < 605 )
    loc_angle += -9.7;
  else if (loc_angle < 634 )
    loc_angle += -10;
  else if (loc_angle < 700 )
    loc_angle += -9.7;
  else if (loc_angle < 800 )
    loc_angle += -9.6;
  /*
  else if (loc_angle < 44 )
    loc_angle += 1.8;
  else if (loc_angle < 53)
    loc_angle += 2.3;
  else if (loc_angle < 60)
    loc_angle += 2.6;
  else if (loc_angle < 66)
    loc_angle += 2.9;
  else if (loc_angle < 71)
    loc_angle += 3.3;
  else if (loc_angle < 80)
    loc_angle += 3.5;
  else if (loc_angle < 100)
    loc_angle += 3.45;
  else if (loc_angle < 119)
    loc_angle += 2.7;
  else if (loc_angle < 125)
    loc_angle += 2.3;
  else if (loc_angle < 137)
    loc_angle += 1.5;
  else if (loc_angle < 142)
    loc_angle += -0.3;
  else if (loc_angle < 162)
    loc_angle += -0.3;
  else if (loc_angle < 183)
    loc_angle += -0.8;
  else if (loc_angle < 211)
    loc_angle += -0.1;
  else if (loc_angle < 229)
    loc_angle += 0.6;
  else if (loc_angle < 246)
    loc_angle += 1.6;
  else if (loc_angle < 254)
    loc_angle += 2.9;
  else if (loc_angle < 264)
    loc_angle += 2.6;
  else if (loc_angle < 276)
    loc_angle += 2.3;
  else if (loc_angle < 298)
    loc_angle += 1.1;
  else if (loc_angle < 310)
    loc_angle += 0.2;
  else if (loc_angle < 324)
    loc_angle += -1.0;
  else if (loc_angle < 331)
    loc_angle += -1.3;
  else if (loc_angle < 334)
    loc_angle += -1.4;
  else if (loc_angle < 342)
    loc_angle += -2.1;
  else if (loc_angle < 346)
    loc_angle += -1.9;
  else if (loc_angle < 354)
    loc_angle += -3.1;
  else if (loc_angle < 390)
    loc_angle += -8.5;
  else if (loc_angle < 417)
    loc_angle += -8.0;
  else if (loc_angle < 430)
    loc_angle += -5.7;
  else if (loc_angle < 445)
    loc_angle += -5.4;
  else if (loc_angle < 457)
    loc_angle += -5.3;
  else if (loc_angle < 482)
    loc_angle += -5.5;
  else if (loc_angle < 512)
    loc_angle += -6.7;
  else if (loc_angle < 524)
    loc_angle += -8.3;
  else if (loc_angle < 542)
    loc_angle += -8.9; 
  else if (loc_angle < 552)
    loc_angle += -8.6;  
  else if (loc_angle < 578)
    loc_angle += -8.4;
  else if (loc_angle < 591)
    loc_angle += -8.1;
  else if (loc_angle < 600)
    loc_angle += -7.3;
  else if (loc_angle < 638)
    loc_angle += -6.0;
  else if (loc_angle < 650)
    loc_angle += -5.4;
  else if (loc_angle < 656)
    loc_angle += -6.4;
  else if (loc_angle < 675)
    loc_angle += -7.0;
  else if (loc_angle < 686)
    loc_angle += -7.8;
  else if (loc_angle < 695)
    loc_angle += -8.8;
  else if (loc_angle < 709)
    loc_angle += -9.4;
  else if (loc_angle < 730)
    loc_angle += -10.2;
  else 
    loc_angle = loc_angle;  
    */
  loc_angle += 1.; // SAME START

#endif

#if SerialNumber == 2 // Internationale #2
  if (loc_angle < 30) 
    loc_angle += 1;
  else if (loc_angle < 56)
    loc_angle += 1;
  else if (loc_angle < 75)
    loc_angle += 2;
  else if (loc_angle < 103)
    loc_angle += 2.2;
  else if (loc_angle < 117)
    loc_angle += 1.7;
  else if (loc_angle < 141)
    loc_angle += 1.1;
  else if (loc_angle < 148 )
    loc_angle += 0.8;
  else if (loc_angle < 163)
    loc_angle += -0.2;
  else if (loc_angle < 168)
    loc_angle += -0.7;
  else if (loc_angle < 190)
    loc_angle += -0.3;
  else if (loc_angle < 205)
    loc_angle += -0.1;
  else if (loc_angle < 227)
    loc_angle += 1;
  else if (loc_angle < 234)
    loc_angle += 1.7;
  else if (loc_angle < 274)
    loc_angle += 2;
  else if (loc_angle < 290)
    loc_angle += 1.7;
  else if (loc_angle < 305)
    loc_angle += 1;
  else if (loc_angle < 312)
    loc_angle += 0.5;
  else if (loc_angle < 320)
    loc_angle += -0.2;
  else if (loc_angle < 329)
    loc_angle += -0.5;
  else if (loc_angle < 360)
    loc_angle += -1.3;
  else if (loc_angle < 395)
    loc_angle += -4;
  else if (loc_angle < 416)
    loc_angle += -2.8;
  else if (loc_angle < 446)
    loc_angle += -2.5;
  else if (loc_angle < 460)
    loc_angle += -1.8;
  else if (loc_angle < 473)
    loc_angle += -2.3;
  else if (loc_angle < 487)
    loc_angle += -2.2;
  else if (loc_angle < 513)
    loc_angle += -3;
  else if (loc_angle < 537)
    loc_angle += -3.6;
  else if (loc_angle < 555)
    loc_angle += -4;
  else if (loc_angle < 577)
    loc_angle += -3;
  else if (loc_angle < 600)
    loc_angle += -2.5;
  else if (loc_angle < 611)
    loc_angle += -2;
  else if (loc_angle < 646)
    loc_angle += -1.5;
  else if (loc_angle < 667)
    loc_angle += -2.5;
  else if (loc_angle < 675)
    loc_angle += -2.7;
  else if (loc_angle < 682)
    loc_angle += -3.5;
  else if (loc_angle < 800)
    loc_angle += -4;
  else if (loc_angle < 800)
    loc_angle += -4.3;
/*
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
*/
  loc_angle += -4.7; // SAME START

#endif


#if SerialNumber == 3 // Marseillaise #3
// time between switch and 1st note : 1880ms
  if (loc_angle < 30)
    loc_angle += 0;
  else if (loc_angle < 40)
    loc_angle += 0.2;
  else if (loc_angle < 45)
    loc_angle += 0.4;
  else if (loc_angle < 60)
    loc_angle += 0.3;
  else if (loc_angle < 63)
    loc_angle += 0;
  else if (loc_angle < 71)
    loc_angle += 0.4;
  else if (loc_angle < 80)
    loc_angle += 0.5;
  else if (loc_angle < 100)
    loc_angle += 0;
  else if (loc_angle < 108)
    loc_angle += -0.5;
  else if (loc_angle < 115)
    loc_angle += -0.2;
  else if (loc_angle < 137)
    loc_angle += 0.2;
  else if (loc_angle < 146)
    loc_angle += 0;
  else if (loc_angle < 152)
    loc_angle += -0.5;
  else if (loc_angle < 163)
    loc_angle += 0;
  else if (loc_angle < 169)
    loc_angle += -0.4;
  else if (loc_angle < 202)
    loc_angle += -0.2;
  else if (loc_angle < 206)
    loc_angle += -0.4;
  else if (loc_angle < 216)
    loc_angle += -0.8;  
  else if (loc_angle < 230)
    loc_angle += -0.6;
  else if (loc_angle < 280)
    loc_angle += -1;
  else if (loc_angle < 318)
    loc_angle += -1.3;
  else if (loc_angle < 360)
    loc_angle += -1;
  else if (loc_angle < 418)
    loc_angle += -7.7;
  else if (loc_angle < 425)
    loc_angle += -9.6;
  else if (loc_angle < 432)
    loc_angle += -8.2;
  else if (loc_angle < 440)
    loc_angle += -7.5;
  else if (loc_angle < 446)
    loc_angle += -8.8;
  else if (loc_angle < 465)
    loc_angle += -9.1;
  else if (loc_angle < 497)
    loc_angle += -9.2;
  else if (loc_angle < 514)
    loc_angle += -7.2;
  else if (loc_angle < 527)
    loc_angle += -8.7;
  else if (loc_angle < 545)
   loc_angle += -9;
  else if (loc_angle < 561)
   loc_angle += -8.8;
  else if (loc_angle < 568)
   loc_angle += -8.5;
  else if (loc_angle < 583)
    loc_angle += -8.7;
  else if (loc_angle < 609)
    loc_angle += -9.8;
  else if (loc_angle < 633)
    loc_angle += -8.6;
  else if (loc_angle < 680)
    loc_angle += -8.8;
  else if (loc_angle < 712)
    loc_angle += -8.6;
  else if (loc_angle < 800)
    loc_angle += -6.8;
  else
    loc_angle = loc_angle; 
    
/*
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
    loc_angle += -0.7;
  else if (loc_angle < 227)
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
  else if (loc_angle < 641)
    loc_angle += -8.9;
  else if (loc_angle < 682)
    loc_angle += -8.6;
  else if (loc_angle < 800)
    loc_angle += -9.2;
  else 
    loc_angle = loc_angle; 
    */ 
  loc_angle = loc_angle - 1,34;
#endif

#if SerialNumber == 4 // International #4
  if (loc_angle < 23)
    loc_angle += 0.2;
  if (loc_angle < 35)
    loc_angle += 0.1;
  else if (loc_angle < 55)
    loc_angle += 0.2;
  else if (loc_angle < 75)
    loc_angle += 0.3;
  else if (loc_angle < 103)
    loc_angle += -0.3;
  else if (loc_angle < 116)
    loc_angle += -1;
  else if (loc_angle < 126)
    loc_angle += -1.3;
  else if (loc_angle < 138)
    loc_angle += -2;
  else if (loc_angle < 157)
    loc_angle += -1.7;
  else if (loc_angle < 186)
    loc_angle += -1.6;
  else if (loc_angle < 225)
    loc_angle += -1.6;
  else if (loc_angle < 280)
    loc_angle += -1.7;
  else if (loc_angle < 287)
    loc_angle += -2;
  else if (loc_angle < 311)
    loc_angle += -2.5;
  else if (loc_angle < 360)
    loc_angle += -2.5;
  else if (loc_angle < 417)
    loc_angle += -4.2;
  else if (loc_angle < 447)
    loc_angle += -4.4;
  else if (loc_angle < 462)
    loc_angle += -4.7;
  else if (loc_angle < 485)
    loc_angle += -4.8;
  else if (loc_angle < 514)
    loc_angle += -5.6;
  else if (loc_angle < 539)
    loc_angle += -5.8;
  else if (loc_angle < 581)
    loc_angle += -5.7;
  else if (loc_angle < 630)
    loc_angle += -5.6;
  else if (loc_angle < 647)
    loc_angle += -5.2;
  else if (loc_angle < 682)
    loc_angle += -6;
  else if (loc_angle < 800)
    loc_angle += -5.8;
/*
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
*/
  loc_angle += -2.8; // SAME START

#endif


  return loc_angle;
}

