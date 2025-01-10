#ifndef PERIPHERALMENU_H
   #define PERIPHERALMENU_H
   #include <Arduino.h>
   #include <Button2.h>
   #include <TFT_eSPI.h>
   #include <Adafruit_MPU6050.h>
   #include <Adafruit_Sensor.h>
   #include <Wire.h>
   #include "otwUI/otwUI.h"
   #include "osVariables/osVariables.h"
   extern TFT_eSPI tft;
   extern TFT_eSprite screenSprite;
   extern Adafruit_MPU6050 mpu;
   extern sensors_event_t adata, gdata, tdata;  
   void peripheralScreen();
   void openPeripheralScreen(Button2& btn);
   void peripheralMenu(Button2& btn);
#endif
