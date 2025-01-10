#ifndef TIMESYNC_H
  #define TIMESYNC_H
  #include <Arduino.h>
  #include <TFT_eSPI.h>
  #include <Adafruit_GFX.h>
  #include "otwUI/otwUI.h"
  #include "osVariables/osVariables.h"
  #include <WiFi.h>
  #include "time.h"
  extern TFT_eSPI tft;
  extern TFT_eSprite screenSprite;
  void getTime();
  void showTime(int timeX, int timeY, int dateX, int dateY, int dayX, int dayY);
#endif
