#ifndef WATCHFACE_H
  #define WATCHFACE_H
  #include <Arduino.h>
  #include <Button2.h>
  #include <TFT_eSPI.h>
  #include <Adafruit_GFX.h>
  #include "otwUI/otwUI.h"
  #include "osVariables/osVariables.h"
  #include "wallpaper/catalina.h"
  #include "timeSync/timeSync.h"
  extern TFT_eSPI tft;
  extern TFT_eSprite timing;
  void homeScreen();
  void watchFace0();
  void watchFace1();
#endif