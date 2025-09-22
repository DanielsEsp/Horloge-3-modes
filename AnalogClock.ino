
//____________________________________________________________________________ 

void horlogeCadran() {

     tft_ST7735.fillScreen(TFT_BLACK);  
     tft_ST7735.setTextColor(TFT_WHITE, TFT_BLACK);
     
     // Cadran horloge
     tft_ST7735.fillCircle(64, 64, 61, TFT_CYAN);
     tft_ST7735.fillCircle(64, 64, 57, TFT_BLACK);

     //  Trace 12 ligne des heures
     for (int i = 0; i<360; i+= 30) {
          sx = cos((i-90)*0.0174532925);
          sy = sin((i-90)*0.0174532925);
          x0 = sx*57+64;
          yy0 = sy*57+64;
          x1 = sx*50+64;
          yy1 = sy*50+64;
          tft_ST7735.drawLine(x0, yy0, x1, yy1, TFT_CYAN);
         }
     //  Trace 60 point des minutes
     for (int i = 0; i<360; i+= 6) {
          sx = cos((i-90)*0.0174532925);
          sy = sin((i-90)*0.0174532925);
          x0 = sx*53+64;
          yy0 = sy*53+64;
          tft_ST7735.drawPixel(x0, yy0, TFT_WHITE);    
       // Trace les quarts
          if (i==0 || i==180) tft_ST7735.fillCircle(x0, yy0, 2, TFT_WHITE);
          if (i==90 || i==270) tft_ST7735.fillCircle(x0, yy0, 2, TFT_WHITE);
         }
      tft_ST7735.fillCircle(65, 65, 3, TFT_RED);
       
} 

//____________________________________________________________________________ 

void horlogeAfficheTemps() {

     tft_ST7735.fillRect(0, 140, 125, 30, TFT_BLACK);
     if (hh<10) { hhTxt = " " + String(hh); } else { hhTxt = String(hh); }
     if (mm<10) { mmTxt = "0" + String(mm); } else { mmTxt = String(mm); }
     tft_ST7735.setCursor(23, 135);
     tft_ST7735.setTextSize (2);
     tft_ST7735.print(hhTxt + " : " + mmTxt);       
  
     if (mm > 59) { mm=0; }
     if (hh > 23) { hh=0; }
     if (mm < 10) { mmTxt = "0" + String(mm); } else { mmTxt = String(mm); }

     // Calcul de la nouvelle position des minutes et heures
     mdeg = mm*6+sdeg*0.01666667;
     hdeg = hh*30+mdeg*0.0833333;
     hx = cos((hdeg-90)*0.0174532925);    
     hy = sin((hdeg-90)*0.0174532925);
     mx = cos((mdeg-90)*0.0174532925);    
     my = sin((mdeg-90)*0.0174532925);

     // Efface la position anterieure des heures et minutes
     tft_ST7735.drawLine(ohx, ohy, 65, 65, TFT_BLACK);
     ohx = hx*33+65;    
     ohy = hy*33+65;
     tft_ST7735.drawLine(omx, omy, 65, 65, TFT_BLACK);
     omx = mx*44+65;    
     omy = my*44+65;

     // Re-dessine la nouvelle position des heures et minutes
     tft_ST7735.drawLine(ohx, ohy, 65, 65, TFT_WHITE);
     tft_ST7735.drawLine(omx, omy, 65, 65, TFT_WHITE);
     tft_ST7735.fillCircle(65, 65, 3, TFT_WHITE);
      
}
  
