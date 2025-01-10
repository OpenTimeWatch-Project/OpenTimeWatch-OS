#ifndef OSVARIABLES_H
   #define OSVARIABLES_H
   #include <Arduino.h>
   extern boolean gameMode;
   extern int settingsItemsNo;
   extern String settingsItems[];
   extern float cpuTemp;
   extern boolean speakerState;
   extern boolean ledState;
   extern int peripheralItemsNo;
   extern String peripheralItems[];
   extern const int speakerPin;
   extern const int ledPin;
   extern const int fakeGroundPin;
   extern int menuItemsNo;
   extern int screenMode;
   extern int selected;
   extern String menuItems[];
   extern float batteryVoltage;
   extern int watchFaceMode;
   extern int maxWatchFaceNo;
   extern const char* ssid;
   extern const char* password;
   extern const char* ntpServer;
   extern const long  gmtOffset_sec;
   extern const int   daylightOffset_sec; 
   extern char dayName[4];
   extern char monthName[4];
   extern int monthNo;
#endif
