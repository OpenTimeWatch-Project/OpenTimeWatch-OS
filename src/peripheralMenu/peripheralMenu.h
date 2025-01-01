#ifndef PERIPHERALMENU_H
   #define PERIPHERALMENU_H
   #include <Arduino.h>
   #include <Button2.h>
   #include <TFT_eSPI.h>
   #include "otwUI/otwUI.h"
   #include "osVariables/osVariables.h"
   extern TFT_eSPI tft;
   void peripheralScreen();
   void openPeripheralScreen(Button2& btn);
   void peripheralMenu(Button2& btn);
#endif