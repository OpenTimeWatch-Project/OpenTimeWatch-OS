#ifndef OTWUI_H
   #define OTWUI_H
   #include<Arduino.h>
   #include <TFT_eSPI.h>
   extern TFT_eSPI tft;
   extern int selected;
   extern TFT_eSprite screenSprite;
   void clearScreen();
   void cursorControll(int menuItemNoHolder);
   void menuScreen(String menuItemHolder[], int menuItemNoHolder);
   void clearScreenSprite();
#endif
