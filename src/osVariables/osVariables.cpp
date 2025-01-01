#include "osVariables.h"

// a variable to store the battery charge voltage
float batteryVoltage;
// an array to hold the names of apps in Activitythe menu
String menuItems[] = {"Today view", "Pong", "Peripherals", "Settings", "Hacker Mode", "Back"};
// a varible to check if any item in the menu is selected
int selected = 0;
// a variable to check which screen the user is looking at
int screenMode = 0;
// a variable to store the amount of items in the menu
int menuItemsNo = 5;
// just a fake ground
const int fakeGroundPin = 34;
// torch LED pin
const int ledPin = 33;
// speaker pin
const int speakerPin = 16;
// list of menu items for the peripheral menu
String peripheralItems[] = {"Torch - off", "Speaker - off", "Accelerometer", "Gyroscope", "CPU Temperature", "Back"};
// no of items in peripheral menu
int peripheralItemsNo = 5;
// state of the led's power
boolean ledState = 0;
// state of the speaker's power
boolean speakerState = 0;
// variable to hold the value of the cpu temperature
float cpuTemp = 0.00;
// list of menu items for the settings menu
String settingsItems[] = {"Sync Time", "Sync Weather", "About", "Back"};
// no of items in peripheral menu
int settingsItemsNo = 3;
// a variable to indicate if the game is currently being played or not
boolean gameMode = 0;
//
int watchFaceMode = 1;
//
int maxWatchFaceNo = 2;
//
const char* ssid       = "Airtel_Venka999";
//
const char* password   = "VAYU@2032";
const char* ntpServer = "asia.pool.ntp.org";
const long  gmtOffset_sec = 19800;
const int   daylightOffset_sec = 0;
char dayName[4];