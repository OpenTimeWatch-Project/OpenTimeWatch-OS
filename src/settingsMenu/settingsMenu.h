#ifndef SETTINGSMENU_H
   #define SETTINGSMENU_H
   #include <Arduino.h>
   #include <Button2.h>
   #include <TFT_eSPI.h>
   #include "otwUI/otwUI.h"
   #include "osVariables/osVariables.h"
   #include "timeSync/timeSync.h"
   extern TFT_eSPI tft;
   void settingsScreen();
   void openSettingsScreen(Button2& btn);
   void settingsMenu(Button2& btn);
   void scrollSettings(Button2& btn);
   void infoScreen();
#endif